// Copyright (c) 2025-2026 ICHIRO ITS
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

#ifndef KEISAN__EKF__EKF_BALL_HPP_
#define KEISAN__EKF__EKF_BALL_HPP_

#include <utility>

#include "keisan/matrix/matrix.hpp"

namespace keisan
{

class ekf_ball
{
public:
  ekf_ball();

  void init(double x, double y, double vx, double vy);
  void predict(double dt);
  void update(const Matrix<2, 1> & z);

  void set_Q(double q_pos, double q_vel);
  void set_R(double r_pos);
  void set_friction(double friction);

  Matrix<2, 1> get_position() const;
  Matrix<2, 1> get_velocity() const;
  Matrix<4, 1> get_state() const;
  Matrix<4, 4> get_cov() const;

  std::vector<Matrix<4, 1>> predict_future(double dt_future) const;

private:
  Matrix<4, 1> X;  // state: [x, y, vx, vy]
  Matrix<4, 4> P;  // covariance
  Matrix<4, 4> Q;  // process noise covariance
  Matrix<2, 2> R;  // measurement noise covariance

  double friction;  // grass friction
};

}  // namespace keisan

#endif  // KEISAN__EKF__EKF_BALL_HPP_
