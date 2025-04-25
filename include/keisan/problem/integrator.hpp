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

#ifndef KEISAN__PROBLEM__INTEGRATOR_HPP_
#define KEISAN__PROBLEM__INTEGRATOR_HPP_

#include <Eigen/Dense>

#include "keisan/problem/expression.hpp"
#include "keisan/problem/variable.hpp"

#include <map>

namespace keisan
{

class Integrator
{
public:
  struct Trajectory
  {
    double value(double t, int diff);

    Eigen::VectorXd variable_value;

    Eigen::MatrixXd M;  // Continuous system matrix
    int order;          // Size dari system matrix

    std::map<int, Eigen::VectorXd> keyframes;

    double duration();

    double dt;
    double t_start = 0.;
  };

  Integrator();
  Integrator(Variable & variable, Expression x0, int order, double dt);
  Integrator(Variable & variable, Expression X0, Eigen::MatrixXd system_matrix, double dt);

  static Eigen::MatrixXd upper_shift_matrix(int order);

  // Referensi ke X_{k+1} = A X_k + B u_k
  static std::pair<Eigen::MatrixXd, Eigen::VectorXd> get_AB_matrices(
    Eigen::MatrixXd & M, int order, double dt);

  Expression expr(int step, int diff = -1);
  Expression expr_t(double t, int diff = -1);

  double value(double t, int diff);

  // Decision variable
  std::shared_ptr<Variable> variable;

  // Continuous system matrix
  Eigen::MatrixXd M;
  int order;

  // Referensi ke X_{k+1} = A X_k + B u_k
  Eigen::MatrixXd A;
  Eigen::MatrixXd B;

  // Initial state dari integrator
  Expression x0;

  Eigen::MatrixXd final_transition_matrix;

  std::map<int, Eigen::MatrixXd> a_powers;

  Trajectory get_trajectory();

  double dt;
  double t_start = 0.;

protected:
  // Cek jika diff yang diberikan valid
  void check_diff(int diff, bool allow_all = false);

  int version = 0;

  Trajectory trajectory;

  void update_trajectory();
};

}  // namespace keisan

#endif  //  KEISAN__PROBLEM__INTEGRATOR_HPP_
