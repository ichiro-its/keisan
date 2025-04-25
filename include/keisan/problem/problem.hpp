// Copyright (c) 2025 ICHIRO ITS
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

#ifndef KEISAN__PROBLEM__PROBLEM_HPP_
#define KEISAN__PROBLEM__PROBLEM_HPP_

#include "keisan/problem/constraint.hpp"
#include "keisan/problem/expression.hpp"
#include "keisan/problem/variable.hpp"

#include <memory>

namespace keisan
{

class Problem
{
public:
  Problem();

  Variable & add_variable(int size = -1);
  Constraint & add_limit(Expression expression, Eigen::VectorXd target);
  Constraint & add_constraint(const Constraint & constraint);

  void clear_constraints();
  void clear_variables();

  void solve();

  // Jumlah variabel yang perlu disolve
  int n_variables = 0;

  int n_inequalities = 0;
  int n_equalities = 0;

  int free_variables = 0;
  int slack_variables = 0;
  int determined_variables = 0;

  double regularization = 1e-8;

  Eigen::VectorXd x;
  Eigen::VectorXd slacks;

protected:
  /**
  Eigen::ColPivHouseholderQR<Eigen::Matrix<double, -1, -1, 1, -1, -1>> QR;

  /**
   * Vector berisikan determined values, berbentuk P^T * b
   * P = Matrix permutasi
   * b = Berasal dari Ax + b
   */
  Eigen::MatrixXd y;

  std::vector<std::shared_ptr<Variable>> variables;
  std::vector<std::shared_ptr<Constraint>> constraints;

  void get_constraint_expressions(
    std::shared_ptr<Constraint> constraint, Eigen::MatrixXd & A, Eigen::MatrixXd & b);
};

}  // namespace keisan

#endif  // KEISAN__PROBLEM__PROBLEM_HPP_
