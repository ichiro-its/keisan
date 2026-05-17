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

#include "keisan/ekf/ekf_ball.hpp"

#include <cmath>
#include <vector>

namespace keisan
{

const double epsilon = 1e-5;

EKFBall::EKFBall()
{
  X = Matrix<4, 1>::zero();
  P = Matrix<4, 4>::identity();
  P *= 10.0;
  Q = Matrix<4, 4>::identity();
  Q *= 1e-3;
  R = Matrix<2, 2>::identity();
  R *= 0.01;
  friction = 0.0;
}

void EKFBall::set_Q(double q_pos, double q_vel)
{
  Q = Matrix<4, 4>::zero();
  Q[0][0] = q_pos;
  Q[1][1] = q_pos;
  Q[2][2] = q_vel;
  Q[3][3] = q_vel;
}

void EKFBall::set_R(double r_pos)
{
  R = Matrix<2, 2>::zero();
  R[0][0] = r_pos;
  R[1][1] = r_pos;
}

std::vector<Matrix<4, 1>> EKFBall::predict_future(double dt_future) const
{
  Matrix<4, 1> X_pred = X;
  Matrix<4, 4> P_pred = P;

  std::vector<Matrix<4, 1>> result;
  result.push_back(X_pred);

  double current_dt = 0.0;
  double step = 0.2;

  while (current_dt < dt_future) {
    current_dt += step;
    double dt = step;

    double x = X_pred[0][0];
    double y = X_pred[1][0];
    double vx = X_pred[2][0];
    double vy = X_pred[3][0];

    double v_mag = sqrt(vx * vx + vy * vy);

    if (v_mag < epsilon) {
      break;
    }

    // State Prediction
    X_pred[0][0] = x + vx * dt;
    X_pred[1][0] = y + vy * dt;

    double delta_v = friction * 981.0 * dt;

      X_pred[2][0] = 0.0;
      X_pred[3][0] = 0.0;

    if (v_mag > epsilon && delta_v <= v_mag) {
      double scale = 1.0 - delta_v / v_mag;
      X_pred[2][0] = vx * scale;
      X_pred[3][0] = vy * scale;
    }

    Matrix<4, 4> F = Matrix<4, 4>::identity();
    F[0][2] = dt;
    F[1][3] = dt;

    Matrix<4, 4> Q_step = Q;
    Q_step[0][0] *= dt * dt;
    Q_step[1][1] *= dt * dt;
    Q_step[2][2] *= dt;
    Q_step[3][3] *= dt;

    P_pred = F * P_pred * F.transpose() + Q_step;

    result.push_back(X_pred);
  }

  return result;
}

void EKFBall::set_friction(double friction) { this->friction = friction; }

void EKFBall::init(double x, double y, double vx, double vy)
{
  X[0][0] = x;
  X[1][0] = y;
  X[2][0] = vx;
  X[3][0] = vy;
  P = Matrix<4, 4>::identity();
  P *= 10.0;
}

void EKFBall::predict(double dt)
{
  double x = X[0][0];
  double y = X[1][0];
  double vx = X[2][0];
  double vy = X[3][0];

  X[0][0] = x + vx * dt;
  X[1][0] = y + vy * dt;

  double v_mag = sqrt(vx * vx + vy * vy);
  double delta_v = friction * 981.0 * dt;

  X[2][0] = 0.0;
  X[3][0] = 0.0;

  if (v_mag > epsilon && delta_v <= v_mag) {
    double scale = 1.0 - delta_v / v_mag;
    X[2][0] = vx * scale;
    X[3][0] = vy * scale;
  }

  Matrix<4, 4> F = Matrix<4, 4>::identity();
  F[0][2] = dt;
  F[1][3] = dt;

  Matrix<4, 4> Q_step = Q;
  Q_step[0][0] *= dt * dt;
  Q_step[1][1] *= dt * dt;
  Q_step[2][2] *= dt;
  Q_step[3][3] *= dt;

  P = F * P * F.transpose() + Q_step;
}

void EKFBall::update(const Matrix<2, 1> & z)
{
  Matrix<2, 4> H = Matrix<2, 4>::zero();
  H[0][0] = 1.0;
  H[1][1] = 1.0;

  Matrix<2, 1> z_pred;
  z_pred[0][0] = X[0][0];
  z_pred[1][0] = X[1][0];

  Matrix<2, 1> y;
  y[0][0] = z[0][0] - z_pred[0][0];
  y[1][0] = z[1][0] - z_pred[1][0];

  Matrix<2, 2> S = H * P * H.transpose() + R;

  Matrix<2, 2> S_inv = S;
  if (!S_inv.inverse()) {
    return;
  }

  Matrix<4, 2> K = P * H.transpose() * S_inv;

  Matrix<4, 1> K_y = K * y;
  X[0][0] += K_y[0][0];
  X[1][0] += K_y[1][0];
  X[2][0] += K_y[2][0];
  X[3][0] += K_y[3][0];

  Matrix<4, 4> I = Matrix<4, 4>::identity();
  Matrix<4, 4> IKH = I - K * H;
  P = IKH * P * IKH.transpose() + K * R * K.transpose();
}

Matrix<2, 1> EKFBall::get_position() const
{
  Matrix<2, 1> pos;
  pos[0][0] = X[0][0];
  pos[1][0] = X[1][0];
  return pos;
}

Matrix<2, 1> EKFBall::get_velocity() const
{
  Matrix<2, 1> vel;
  vel[0][0] = X[2][0];
  vel[1][0] = X[3][0];
  return vel;
}

Matrix<4, 1> EKFBall::get_state() const { return X; }

Matrix<4, 4> EKFBall::get_cov() const { return P; }

}  // namespace keisan
