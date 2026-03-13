// File: src/ekf/ekf_ball.cpp
#include "keisan/ekf/ekf_ball.hpp"

#include <cmath>
#include <vector>

namespace keisan
{

ekf_ball::ekf_ball()
{
  X_ = Matrix<4, 1>::zero();
  P_ = Matrix<4, 4>::identity();
  P_ *= 10.0;
  Q_ = Matrix<4, 4>::identity();
  Q_ *= 1e-3;
  R_ = Matrix<2, 2>::identity();
  R_ *= 0.01;
  friction_ = 0.0;
}

void ekf_ball::setQ(double q_pos, double q_vel, double q_theta)
{
  Q_ = Matrix<4, 4>::zero();
  Q_[0][0] = q_pos;
  Q_[1][1] = q_pos;
  Q_[2][2] = q_vel;
  Q_[3][3] = q_theta;
}

void ekf_ball::setR(double r_pos)
{
  R_ = Matrix<2, 2>::zero();
  R_[0][0] = r_pos;
  R_[1][1] = r_pos;
}

std::vector<Matrix<4, 1>> ekf_ball::predictFuture(double dt_future) const
{
  Matrix<4, 1> X_pred = X_;
  Matrix<4, 4> P_pred = P_;

  std::vector<Matrix<4, 1>> result;

  double current_dt = 0.0;
  double step = 0.2;
  double remaining = dt_future;

  while (current_dt < dt_future) {
    // double dt = (remaining > step) ? step : remaining;
    current_dt += step;
    double dt = current_dt;

    double x = X_pred[0][0];
    double y = X_pred[1][0];
    double v = X_pred[2][0];
    double th = X_pred[3][0];

    if (v <= 0.00001) {
      break;
    }

    // State Prediction
    X_pred[0][0] = x + v * std::cos(th) * dt;
    X_pred[1][0] = y + v * std::sin(th) * dt;

    double v_new = v - (friction_ * 9.81 * dt);
    X_pred[2][0] = (v_new > 0.0) ? v_new : 0.0;
    X_pred[3][0] = normalizeAngle(th);

    Matrix<4, 4> F = Matrix<4, 4>::identity();
    F[0][2] = std::cos(th) * dt;
    F[0][3] = -v * std::sin(th) * dt;
    F[1][2] = std::sin(th) * dt;
    F[1][3] = v * std::cos(th) * dt;

    Matrix<4, 4> Q = Q_;
    Q[0][0] *= dt * dt;
    Q[1][1] *= dt * dt;
    Q[2][2] *= dt;
    Q[3][3] *= dt;

    P_pred = F * P_pred * F.transpose() + Q;

    result.push_back(X_pred);
  }

  return result;
}

void ekf_ball::setFriction(double friction) { friction_ = friction; }

void ekf_ball::init(double x, double y, double v, double theta)
{
  X_[0][0] = x;
  X_[1][0] = y;
  X_[2][0] = v;
  X_[3][0] = theta;
  P_ = Matrix<4, 4>::identity();
  P_ *= 10.0;
}

void ekf_ball::predict(double dt)
{
  double x = X_[0][0];
  double y = X_[1][0];
  double v = X_[2][0];
  double th = X_[3][0];

  X_[0][0] = x + v * std::cos(th) * dt;
  X_[1][0] = y + v * std::sin(th) * dt;

  double v_new = v - (friction_ * 9.81 * dt);
  X_[2][0] = (v_new > 0.0) ? v_new : 0.0;

  X_[3][0] = normalizeAngle(th);

  Matrix<4, 4> F = Matrix<4, 4>::identity();

  F[0][2] = std::cos(th) * dt;
  F[0][3] = -v * std::sin(th) * dt;
  F[1][2] = std::sin(th) * dt;
  F[1][3] = v * std::cos(th) * dt;

  Matrix<4, 4> Q = Q_;
  Q[0][0] *= dt * dt;
  Q[1][1] *= dt * dt;
  Q[2][2] *= dt;
  Q[3][3] *= dt;

  P_ = F * P_ * F.transpose() + Q;
}

void ekf_ball::update(const Matrix<2, 1> & z)
{
  Matrix<2, 4> H = Matrix<2, 4>::zero();
  H[0][0] = 1.0;
  H[1][1] = 1.0;

  Matrix<2, 1> z_pred;
  z_pred[0][0] = X_[0][0];
  z_pred[1][0] = X_[1][0];

  Matrix<2, 1> y;
  y[0][0] = z[0][0] - z_pred[0][0];
  y[1][0] = z[1][0] - z_pred[1][0];

  Matrix<2, 2> S = H * P_ * H.transpose() + R_;

  Matrix<2, 2> S_inv = S;
  if (!S_inv.inverse2()) {
    return;
  }

  Matrix<4, 2> K = P_ * H.transpose() * S_inv;

  Matrix<4, 1> K_y = K * y;
  X_[0][0] += K_y[0][0];
  X_[1][0] += K_y[1][0];
  X_[2][0] += K_y[2][0];
  X_[3][0] += K_y[3][0];

  Matrix<4, 4> I = Matrix<4, 4>::identity();
  P_ = (I - K * H) * P_ * (I - K * H).transpose() + K * R_ * K.transpose();

  if (X_[2][0] < 0.0) {
    X_[2][0] = std::abs(X_[2][0]);
    X_[3][0] += M_PI;
    X_[3][0] = normalizeAngle(X_[3][0]);
  }
}

Matrix<2, 1> ekf_ball::getPosition() const
{
  Matrix<2, 1> pos;
  pos[0][0] = X_[0][0];
  pos[1][0] = X_[1][0];
  return pos;
}

Matrix<2, 1> ekf_ball::getVelocity() const
{
  double v = X_[2][0];
  double th = X_[3][0];
  Matrix<2, 1> vel;
  vel[0][0] = v * std::cos(th);
  vel[1][0] = v * std::sin(th);
  return vel;
}

Matrix<4, 1> ekf_ball::getstate() const { return X_; }

Matrix<4, 4> ekf_ball::getcov() const { return P_; }

double ekf_ball::normalizeAngle(double a) const
{
  while (a > M_PI) a -= 2.0 * M_PI;
  while (a < -M_PI) a += 2.0 * M_PI;
  return a;
}

}  // namespace keisan