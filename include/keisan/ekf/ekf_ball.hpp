// Copyright (c) 2026 ICHIRO ITS
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

#ifndef EKF_BALL_HPP
#define EKF_BALL_HPP

#include "keisan/matrix/matrix.hpp"

namespace keisan
{

class ekf_ball
{
public:
  ekf_ball();

  void init(double x, double y, double v, double theta);
  void predict(double dt);
  void update(const Matrix<2, 1> & z);

  void set_q_noise(double q)
  {
    for (int i = 0; i < 4; i++) Q_[i][i] = q;
  }
  void set_r_noise(double r)
  {
    for (int i = 0; i < 2; i++) R_[i][i] = r;
  }

  Matrix<2, 1> getPosition() const;
  Matrix<2, 1> getVelocity() const;

  Matrix<4, 1> getstate() const;
  Matrix<4, 4> getcov() const;

private:
  Matrix<4, 1> X_;  //state
  Matrix<4, 4> P_;  //covarience
  Matrix<4, 4> Q_;  //covarience noise
  Matrix<2, 2> R_;  //measurement noise

  double normalizeAngle(double a) const;  // a = angle in radians
};

}  // namespace keisan

#endif  // EKF_BALL_HPP
