#include "keisan/ekf/ekf_landmark.hpp"
#include <cmath>

namespace keisan
{

ekf_landmark::ekf_landmark()
{
    X[0][0] = 0.0;
    X[1][0] = 0.0;

    P = Matrix<2,2>::identity();
    Q = Matrix<2,2>::identity() * 1e-4;
    R = Matrix<2,2>::identity() * 0.0025;
}

void ekf_landmark::predict()
{
    P = P + Q;
}

void ekf_landmark::update(
    const Matrix<2,1> & z,
    double xr, double yr, double theta)
{
    double dx = X[0][0] - xr;
    double dy = X[1][0] - yr;

    double q = dx*dx + dy*dy;
    double sqrt_q = std::sqrt(q);

    Matrix<2,1> z_pred;
    z_pred[0][0] = sqrt_q;
    z_pred[1][0] = std::atan2(dy, dx) - theta;

    Matrix<2,2> H;
    H[0][0] =  dx / sqrt_q;
    H[0][1] =  dy / sqrt_q;
    H[1][0] = -dy / q;
    H[1][1] =  dx / q;

    Matrix<2,1> y = z - z_pred;

    while (y[1][0] > M_PI)  y[1][0] -= 2*M_PI;
    while (y[1][0] < -M_PI) y[1][0] += 2*M_PI;

    Matrix<2,2> S = H * P * H.transpose() + R;

    double det = S[0][0]*S[1][1] - S[0][1]*S[1][0];

    Matrix<2,2> S_inv;
    S_inv[0][0] =  S[1][1] / det;
    S_inv[0][1] = -S[0][1] / det;
    S_inv[1][0] = -S[1][0] / det;
    S_inv[1][1] =  S[0][0] / det;

    Matrix<2,2> K = P * H.transpose() * S_inv;

    X = X + K * y;
    P = (Matrix<2,2>::identity() - K * H) * P;
}

Matrix<2,1> ekf_landmark::getstate() const
{
    return X;
}

Matrix<2,2> ekf_landmark::getcov() const
{
    return P;
}

} // namespace keisan
