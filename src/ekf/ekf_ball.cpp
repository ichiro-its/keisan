#include "keisan/ekf/ekf_ball.hpp"

#include <cmath>

namespace keisan
{

ekf_ball::ekf_ball()
{
  X_ = Matrix<4, 1>::zero();
  P_ = Matrix<4, 4>::identity();  // Need tuning (but optional)
  Q_ = Matrix<4, 4>::identity();
  Q_ *= 1e-3;  // Need tuning: process noise, start : 1e-3
  R_ = Matrix<2, 2>::identity();
  R_ *= 0.01;  // Need tuning: measurement noise (Tuning R dulu baru Q), start : 0.01
}

void ekf_ball::setQ(double q_pos, double q_vel, double q_theta)
{
  Q_ = Matrix<4, 4>::zero();
  Q_[0][0] = q_pos;    // Uncertainty posisi X
  Q_[1][1] = q_pos;    // Uncertainty posisi Y
  Q_[2][2] = q_vel;    // Uncertainty kecepatan (v)
  Q_[3][3] = q_theta;  // Uncertainty heading (theta)
}

void ekf_ball::setR(double r_pos)
{
  R_ = Matrix<2, 2>::zero();
  R_[0][0] = r_pos;  // Noise kamera sumbu X
  R_[1][1] = r_pos;  // Noise kamera sumbu Y
}

// Fungsi Prediksi Masa Depan (3 detik) dengan looping EKF
Matrix<4, 1> ekf_ball::predictFuture(double dt_future) const
{
  Matrix<4, 1> X_temp = X_;
  Matrix<4, 4> P_temp = P_;
  double step = 0.1;
  double remaining = dt_future;

  while (remaining > 0) {
    double dt = (remaining > step) ? step : remaining;
    double x = X_temp[0][0], y = X_temp[1][0], v = X_temp[2][0], th = X_temp[3][0];

    // Predict State
    X_temp[0][0] = x + v * std::cos(th) * dt;
    X_temp[1][0] = y + v * std::sin(th) * dt;
    X_temp[2][0] = v;
    X_temp[3][0] = normalizeAngle(th);

    // Predict Covariance (Jacobian F)
    Matrix<4, 4> F = Matrix<4, 4>::identity();
    F[0][2] = std::cos(th) * dt;
    F[0][3] = -v * std::sin(th) * dt;
    F[1][2] = std::sin(th) * dt;
    F[1][3] = v * std::cos(th) * dt;

    Matrix<4, 4> Q_step = Q_;
    Q_step[0][0] *= dt * dt;
    Q_step[1][1] *= dt * dt;
    Q_step[2][2] *= dt;
    Q_step[3][3] *= dt;

    P_temp = F * P_temp * F.transpose() + Q_step;
    remaining -= dt;
  }
  return X_temp;
}

void ekf_ball::init(double x, double y, double v, double theta)
{
  X_[0][0] = x;
  X_[1][0] = y;
  X_[2][0] = v;
  X_[3][0] = theta;
  P_ = Matrix<4, 4>::identity();
}

void ekf_ball::predict(double dt)
{
  double x = X_[0][0];
  double y = X_[1][0];
  double v = X_[2][0];
  double th = X_[3][0];

  X_[0][0] = x + v * std::cos(th) * dt;
  X_[1][0] = y + v * std::sin(th) * dt;
  X_[2][0] = v;
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