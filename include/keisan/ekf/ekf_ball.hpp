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

  // init and core functions
  void init(double x, double y, double v, double theta);
  void predict(double dt);
  void update(const Matrix<2, 1> & z);

  // tuning parameter setter
  void setQ(double q_pos, double q_vel, double q_theta);
  void setR(double r_pos);
  void setFriction(double friction);

  // output
  Matrix<2, 1> getPosition() const;
  Matrix<2, 1> getVelocity() const;
  Matrix<4, 1> getstate() const;
  Matrix<4, 4> getcov() const;

  std::pair<Matrix<4, 1>, Matrix<4, 4>> predictFuture(double dt_future) const;

private:
  double normalizeAngle(double a) const;

  Matrix<4, 1> X_;  // state: [x, y, v, theta]
  Matrix<4, 4> P_;  // covariance
  Matrix<4, 4> Q_;  // process noise covariance
  Matrix<2, 2> R_;  // measurement noise covariance

  double friction_;  // grass friction
};

}  // namespace keisan

#endif  // KEISAN__EKF__EKF_BALL_HPP_