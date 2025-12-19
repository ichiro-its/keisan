#include "keisan/ekf/ekf_ball.hpp"
#include <cmath>

namespace keisan
{

ekf_ball::ekf_ball()
{
    X_(0,0) = 0.0;
    X_(1,0) = 0.0;
    X_(2,0) = 0.0;
    X_(3,0) = 0.0;

    P_.setIdentity();

    Q_.setIdentity();
    Q_ *= 1e-3;

    R_.setIdentity();
    R_ *= 0.01;
}

void ekf_ball::init(double x, double y)
{
    X_(0,0) = x;
    X_(1,0) = y;
    X_(2,0) = 0.0;
    X_(3,0) = 0.0;

    P_.setIdentity();
}

void ekf_ball::predict(double dt)
{
    Matrix<4,4> F;
    F.setIdentity();
    F(0,2) = dt;
    F(1,3) = dt;

    X_ = F * X_;

    Matrix<4,4> Q = Q_;
    Q(0,0) *= dt * dt;
    Q(1,1) *= dt * dt;
    Q(2,2) *= dt;
    Q(3,3) *= dt;

    P_ = F * P_ * F.transpose() + Q;
}

void ekf_ball::update(const Matrix<2, 1> & z)
{
    Matrix<2,4> H;
    H.setZero();
    H(0,0) = 1.0;
    H(1,1) = 1.0;

    Matrix<2,1> z_pred;
    z_pred(0,0) = X_(0,0);
    z_pred(1,0) = X_(1,0);

    Matrix<2,1> y = z - z_pred;

    Matrix<2,2> S = H * P_ * H.transpose() + R_;

    Matrix<4,2> K = P_ * H.transpose() * S.inverse();

    X_ = X_ + K * y;

    Matrix<4,4> I;
    I.setIdentity();
    P_ = (I - K * H) * P_ * (I - K * H).transpose()
         + K * R_ * K.transpose();
}

Matrix<2,1> ekf_ball::getPosition() const
{
    Matrix<2,1> pos;
    pos(0,0) = X_(0,0);
    pos(1,0) = X_(1,0);
    return pos;
}

Matrix<2,1> ekf_ball::getVelocity() const
{
    Matrix<2,1> vel;
    vel(0,0) = X_(2,0);
    vel(1,0) = X_(3,0);
    return vel;
}

Matrix<4,1> ekf_ball::getstate() const
{
    return X_;
}
Matrix<4,4> ekf_ball::getcov() const
{
    return P_;
}

} // namespace keisan
