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

#include "keisan/problem/integrator.hpp"

#include "keisan/problem/expression.hpp"
#include "keisan/problem/problem.hpp"

#include <unsupported/Eigen/MatrixFunctions>

#include <algorithm>
#include <stdexcept>

namespace keisan
{

double Integrator::Trajectory::value(double t, int diff)
{
  t -= t_start;

  Integrator::check_diff(order, diff);

  int k = std::floor(t / dt);

  if (k < 0) {
    k = 0;
  }

  if (k >= variable_value.size()) {
    k = variable_value.size() - 1;
  }

  double remaining_dt = fmax(0, fmin(dt, t - k * dt));

  if (diff == order) {
    return variable_value[k];
  } else {
    auto AB = get_AB_matrices(M, order, remaining_dt);
    Eigen::MatrixXd Ar = AB.first;
    Eigen::MatrixXd Br = AB.second;

    Eigen::VectorXd result = Ar * keyframes[k] + Br * variable_value[k];

    return result[diff];
  }
}

double Integrator::Trajectory::duration() { return keyframes.size() * dt; }

Integrator::Integrator() {}

Integrator::Integrator(
  Variable & variable_, Expression x0_, Eigen::MatrixXd system_matrix, double dt)
: variable(&variable_), M(system_matrix), x0(x0_), dt(dt)
{
  order = system_matrix.rows() - 1;

  N = variable->size();

  auto AB = get_AB_matrices(M, order, dt);
  A = AB.first;
  B = AB.second;

  final_transition_matrix = Eigen::MatrixXd(order, N);
  final_transition_matrix.setZero();

  Eigen::MatrixXd Ak(order, order);
  Ak.setIdentity();
  a_powers[0] = Ak;

  for (int step = 0; step < N; ++step) {
    final_transition_matrix.block(0, N - step - 1, order, 1) = Ak * B;
    Ak = A * Ak;
    a_powers[step + 1] = Ak;
  }
}

Integrator::Integrator(Variable & variable_, Expression x0_, int order, double dt)
: Integrator(variable_, x0_, upper_shift_matrix(order), dt)
{
  if (x0_.rows() != order) {
    throw std::runtime_error(
      "Integrator: X0 should have " + std::to_string(order) + " rows (same as order)");
  }
}

std::pair<Eigen::MatrixXd, Eigen::VectorXd> Integrator::get_AB_matrices(
  Eigen::MatrixXd & M, int order, double dt)
{
  Eigen::MatrixXd Me = (M * dt).exp();
  Eigen::MatrixXd A = Me.block(0, 0, order, order);
  Eigen::MatrixXd B = Me.block(0, order, order, 1);

  return std::pair<Eigen::MatrixXd, Eigen::VectorXd>(A, B);
}

Eigen::MatrixXd Integrator::upper_shift_matrix(int order)
{
  Eigen::MatrixXd M(order + 1, order + 1);
  M.setZero();

  for (int k = 0; k < order; ++k) {
    M(k, k + 1) = 1.0;
  }

  return M;
}

void Integrator::check_diff(int order, int diff, bool allow_all)
{
  int diff_min = allow_all ? -1 : 0;

  if (diff < diff_min || diff > order) {
    std::ostringstream oss;
    oss << "Asked differentiation order of " << diff << " for an integrator of order " << order;
    throw std::runtime_error(oss.str());
  }
}

Expression Integrator::expr(int step, int diff)
{
  check_diff(order, diff, true);

  step = (step == -1) ? variable->size() : step;

  if (step < 0 || step > variable->size()) {
    std::ostringstream oss;
    oss << "Asking an expression for step " << step << ", should be between " << 0 << " and "
        << variable->size();
    throw std::runtime_error(oss.str());
  }

  if (diff == order) {
    return variable->expr(step, 1);
  }

  Expression e;
  int rows = (diff == -1) ? order : 1;

  e.A = Eigen::MatrixXd(rows, variable->offset_end);
  e.A.setZero();

  e.b = Eigen::VectorXd(rows);
  e.b.setZero();

  if (diff == -1) {
    e.A.block(0, variable->offset_start, rows, step) =
      final_transition_matrix.block(0, N - step, rows, step);
    e = e + a_powers[step] * x0;
  } else {
    e.A.block(0, variable->offset_start, 1, step) =
      final_transition_matrix.block(diff, N - step, 1, step);
    e = e + (a_powers[step] * x0).slice(diff, 1);
  }

  return e;
}

Expression Integrator::expr_t(double t, int diff)
{
  t -= t_start;

  if (t < 0 || t > variable->size() * dt) {
    throw std::runtime_error("expr_t called with t out of the scope of integrator.");
  }

  int step = std::max<int>(std::min<int>(variable->size() - 1, t / dt), 0);

  if (diff == order) {
    return variable->expr(step, 1);
  }

  double remaining_dt = t - step * dt;

  auto AB = get_AB_matrices(M, order, remaining_dt);
  Eigen::MatrixXd Ar = AB.first;
  Eigen::MatrixXd Br = AB.second;

  Expression e = (Ar * expr(step)) + Br * variable->expr(step);

  if (diff > -1) {
    e.A = Eigen::MatrixXd(e.A.block(diff, 0, 1, e.A.cols()));
    e.b = Eigen::MatrixXd(e.b.block(diff, 0, 1, e.b.cols()));
  }

  return e;
}

double Integrator::value(double t, int diff)
{
  update_trajectory();

  return trajectory.value(t, diff);
}

Integrator::Trajectory Integrator::get_trajectory()
{
  update_trajectory();

  return trajectory;
}

void Integrator::update_trajectory()
{
  if (variable->version == 0) {
    throw std::runtime_error("Trying to get the trajectory with a variable that was not solved");
  }

  if (version != variable->version) {
    trajectory.M = M;
    trajectory.dt = dt;
    trajectory.order = order;
    trajectory.t_start = t_start;
    trajectory.variable_value = variable->value;

    Eigen::VectorXd X = x0.value(variable->problem->x);
    trajectory.keyframes[0] = X;

    for (int k = 1; k <= variable->size(); k++) {
      X = A * X + B * variable->value[k - 1];
      trajectory.keyframes[k] = X;
    }

    version = variable->version;
  }
}

}  // namespace keisan
