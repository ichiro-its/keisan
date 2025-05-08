// Copyright (c) 2025 Rhoban
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "keisan/problem/problem.hpp"

#include "keisan/problem/constraint.hpp"
#include "keisan/problem/expression.hpp"
#include "keisan/problem/sparsity.hpp"
#include "keisan/problem/variable.hpp"

#include <Eigen/Dense>
#include "eiquadprog/eiquadprog.hpp"

#include <cmath>
#include <limits>
#include <map>
#include <stdexcept>

namespace keisan
{

Problem::Problem() {}

Problem::~Problem()
{
  clear_constraints();
  clear_variables();
}

Variable & Problem::add_variable(int size)
{
  Variable * variable = new Variable;
  variable->problem = this;
  variable->offset_start = n_variables;
  variable->offset_end = n_variables + size;
  n_variables += size;

  variables.push_back(variable);

  return *variable;
}

Constraint & Problem::add_limit(Expression expression, Eigen::VectorXd target)
{
  Eigen::VectorXd targets(target.rows() * 2);

  // -target <= expression <= target
  Expression e;
  e.A.resize(expression.A.rows() * 2, expression.A.cols());
  e.b.resize(expression.b.rows() * 2, expression.b.cols());

  // Ax + b <= target
  e.A.block(0, 0, expression.A.rows(), expression.A.cols()) = expression.A;
  e.b.block(0, 0, expression.b.rows(), expression.b.cols()) = expression.b;

  // Ax + b >= -target => -Ax - b <= target
  e.A.block(expression.A.rows(), 0, expression.A.rows(), expression.A.cols()) = -expression.A;
  e.b.block(expression.b.rows(), 0, expression.b.rows(), expression.b.cols()) = -expression.b;

  targets.block(0, 0, target.rows(), 1) = target;
  targets.block(target.rows(), 0, target.rows(), 1) = target;

  return add_constraint(e <= targets);
}

Constraint & Problem::add_constraint(const Constraint & constraint_)
{
  Constraint * constraint = new Constraint;
  *constraint = constraint_;
  constraints.push_back(constraint);

  return *constraint;
}

void Problem::clear_constraints()
{
  for (auto constraint : constraints) {
    delete constraint;
  }

  constraints.clear();
}

void Problem::clear_variables()
{
  for (auto variable : variables) {
    delete variable;
  }

  variables.clear();
  n_variables = 0;
}

void Problem::get_constraint_expressions(
  Constraint * constraint, Eigen::MatrixXd & A, Eigen::MatrixXd & b)
{
  if (determined_variables) {
    Eigen::MatrixXd full_A(constraint->expression.A.rows(), n_variables);
    full_A.setZero();
    full_A.block(0, 0, constraint->expression.A.rows(), constraint->expression.A.cols()) =
      constraint->expression.A;
    QR.matrixQ().applyThisOnTheRight(full_A);

    A = full_A.rightCols(free_variables);
    b = constraint->expression.b + full_A.leftCols(determined_variables) * y;
  } else {
    A = constraint->expression.A;
    b = constraint->expression.b;
  }
}

void Problem::solve()
{
  n_equalities = 0;
  n_inequalities = 0;
  slack_variables = 0;

  for (auto constraint : constraints) {
    if (constraint->type == Constraint::Inequality) {
      constraint->is_active = false;
      if (constraint->priority == Constraint::Soft) {
        slack_variables += constraint->expression.rows();
      }
    } else {
      constraint->is_active = true;
      if (constraint->priority == Constraint::Hard) {
        n_equalities += constraint->expression.rows();
      }
    }
  }

  Eigen::MatrixXd A(n_equalities, n_variables);
  A.setZero();

  Eigen::VectorXd b(n_equalities);
  b.setZero();

  int k_equality = 0;
  for (auto constraint : constraints) {
    if (constraint->type == Constraint::Equality && constraint->priority == Constraint::Hard) {
      // Ax + b = 0
      A.block(k_equality, 0, constraint->expression.rows(), constraint->expression.cols()) =
        constraint->expression.A;
      b.block(k_equality, 0, constraint->expression.rows(), 1) = constraint->expression.b;

      k_equality += constraint->expression.rows();
    }
  }

  free_variables = n_variables;
  determined_variables = 0;

  if (rewrite_equalities && A.rows() > 0) {
    QR = A.transpose().colPivHouseholderQr();

    determined_variables = QR.rank();

    if (determined_variables != A.rows()) {
      throw std::runtime_error(
        "QR decomposition failed to find full rank matrix for equality constraints");
    }

    Eigen::MatrixXd R =
      QR.matrixR().transpose().block(0, 0, determined_variables, determined_variables);
    Eigen::MatrixXd b2 = b.transpose();
    QR.colsPermutation().applyThisOnTheRight(b2);

    y = R.triangularView<Eigen::Lower>().solve(-b2);

    free_variables = n_variables - determined_variables;

    n_equalities = 0;
    A.resize(0, 0);
    b.resize(0);
  }

  Eigen::MatrixXd P(free_variables + slack_variables, free_variables + slack_variables);
  P.setZero();

  Eigen::VectorXd q(free_variables + slack_variables);
  q.setZero();

  // Regularization
  P.block(0, 0, free_variables, free_variables).setIdentity();
  P.block(0, 0, free_variables, free_variables) *= regularization;

  for (auto constraint : constraints) {
    if (constraint->expression.cols() > n_variables) {
      throw std::runtime_error("Inconsistent problem size");
    }

    if (constraint->expression.A.rows() == 0 || constraint->expression.b.rows() == 0) {
      throw std::runtime_error("A or b is empty");
    }

    if (constraint->expression.A.rows() != constraint->expression.b.rows()) {
      throw std::runtime_error("A and b variable size is not equal");
    }

    if (constraint->type == Constraint::Inequality) {
      n_inequalities += constraint->expression.rows();
    } else if (constraint->priority == Constraint::Soft) {
      Eigen::MatrixXd expression_A;
      Eigen::MatrixXd expression_b;
      get_constraint_expressions(constraint, expression_A, expression_b);

      if (use_sparsity_optimization) {
        Sparsity sparsity = Sparsity::detect_columns_sparsity(expression_A);

        int constraints = expression_A.rows();

        for (auto interval : sparsity.intervals) {
          int size = 1 + interval.end - interval.start;

          Eigen::MatrixXd block = expression_A.block(0, interval.start, constraints, size);

          P.block(interval.start, interval.start, size, size).noalias() +=
            constraint->weight * block.transpose() * block;
        }

        q.block(0, 0, expression_A.cols(), 1).noalias() +=
          constraint->weight * (expression_A.transpose() * expression_b);
      } else {
        P.block(0, 0, expression_A.cols(), expression_A.cols()).noalias() +=
          constraint->weight * (expression_A.transpose() * expression_A);
        q.block(0, 0, expression_A.cols(), 1).noalias() +=
          constraint->weight * (expression_A.transpose() * expression_b);
      }
    }
  }

  Eigen::MatrixXd G(n_inequalities, free_variables + slack_variables);
  G.setZero();

  Eigen::VectorXd h(n_inequalities);
  h.setZero();

  std::map<int, Constraint*> hard_inequalities;
  std::map<int, Constraint*> soft_inequalities;

  int k_inequality = 0;
  int k_slack = 0;

  for (int slack = 0; slack < slack_variables; ++slack) {
    G(k_inequality, free_variables + slack) = 1;
    ++k_inequality;
  }

  for (auto constraint : constraints) {
    if (constraint->type == Constraint::Inequality) {
      Eigen::MatrixXd expression_A;
      Eigen::MatrixXd expression_b;
      get_constraint_expressions(constraint, expression_A, expression_b);

      if (constraint->priority == Constraint::Hard) {
        // Ax + b >= 0
        G.block(k_inequality, 0, expression_A.rows(), expression_A.cols()) = expression_A;
        h.block(k_inequality, 0, expression_b.rows(), 1) = expression_b;

        for (int k = k_inequality; k < k_inequality + expression_A.rows(); ++k) {
          hard_inequalities[k] = constraint;
        }

        k_inequality += expression_A.rows();
      } else {
        // min(Ax + b - s)
        Eigen::MatrixXd As(expression_A.rows(), free_variables + slack_variables);
        As.setZero();
        As.block(0, 0, expression_A.rows(), expression_A.cols()) = expression_A;

        for (int k = 0; k < expression_A.rows(); ++k) {
          soft_inequalities[k_slack] = constraint;
          As(k, free_variables + k_slack) = -1;
          ++k_slack;
        }

        P.noalias() += constraint->weight * (As.transpose() * As);
        q.noalias() += constraint->weight * (As.transpose() * expression_b);
      }
    }
  }

  Eigen::VectorXi active_set;
  size_t active_set_size;

  Eigen::VectorXd qp_x(free_variables + slack_variables);
  qp_x.setZero();
  double result = eiquadprog::solvers::solve_quadprog(
    P, q, A.transpose(), b, G.transpose(), h, qp_x, active_set, active_set_size);

  if (determined_variables) {
    Eigen::VectorXd u(n_variables, 1);
    u.setZero();
    u.topRows(determined_variables) = y;
    u.bottomRows(free_variables) = qp_x.topRows(free_variables);
    QR.matrixQ().applyThisOnTheLeft(u);

    x = u;
  } else {
    x = qp_x;
  }

  if (result == std::numeric_limits<double>::infinity()) {
    throw std::runtime_error("Infeasible QP (check your hard inequality constraints)");
  }

  if (A.rows() > 0) {
    Eigen::VectorXd equality_constraints = A * x.topRows(A.cols()) + b;
    for (int k = 0; k < A.rows(); ++k) {
      throw std::runtime_error("Infeasible QP (equality constraints were not enforced)");
    }
  }

  if (x.hasNaN()) {
    throw std::runtime_error("NaN in the QP solution");
  }

  for (int k = 0; k < static_cast<int>(active_set_size); ++k) {
    int active_constraint = active_set[k];

    if (active_constraint >= 0 && hard_inequalities.count(active_constraint)) {
      hard_inequalities[active_constraint]->is_active = true;
    }
  }

  slacks = qp_x.block(free_variables, 0, slack_variables, 1);
  for (int k = 0; k < slacks.rows(); ++k) {
    if (slacks[k] <= 1e-6 && soft_inequalities.count(k)) {
      soft_inequalities[k]->is_active = true;
    }
  }

  for (auto variable : variables) {
    variable->version++;
    variable->value = Eigen::VectorXd(variable->size());
    variable->value = x.block(variable->offset_start, 0, variable->size(), 1);
  }
}

}  // namespace keisan
