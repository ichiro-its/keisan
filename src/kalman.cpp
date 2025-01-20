#include "keisan/kalman.hpp"

namespace keisan {

Kalman::Kalman(double dt, double std_dev_aceleration,
               Matrix<2, 1> std_measurement, Matrix<2, 1> acceleration)
    : U(acceleration) {
  Xk = Matrix<4, 1>::zero();
  Q = Matrix<4, 4>::zero();
  Q[0][0] = pow(dt, 4) / 4;
  Q[0][2] = pow(dt, 3) / 2;
  Q[1][1] = pow(dt, 4) / 4;
  Q[1][3] = pow(dt, 3) / 2;
  Q[2][0] = pow(dt, 3) / 2;
  Q[2][2] = pow(dt, 2);
  Q[3][1] = pow(dt, 3) / 2;
  Q[3][3] = pow(dt, 2);
  Q = Q * pow(std_dev_aceleration, 2);

  R = Matrix<2, 2>::zero();
  R[0][0] = pow(std_dev_aceleration, 2);
  R[1][1] = pow(std_dev_aceleration, 2);

  A = Matrix<4, 4>::zero();
  A[0][0] = 1;
  A[0][2] = dt;
  A[1][1] = 1;
  A[1][3] = dt;
  A[2][2] = 1;
  A[3][3] = 1;

  B = Matrix<4, 2>::zero();
  B[0][0] = pow(dt, 2) / 2;
  B[1][1] = pow(dt, 2) / 2;
  B[2][0] = dt;
  B[3][1] = dt;

  H = Matrix<2, 4>::zero();
  H[0][0] = 1;
  H[1][1] = 1;

  P = Matrix<4, 4>::zero();
    P[0][0] = 1;
    P[1][1] = 1;
}

Matrix<4, 1> Kalman::predict() {
  Xk = A*Xk + B*U;
  P = A*P*A.transpose() + Q;

  return Xk;
}
 
Matrix<4, 1> Kalman::update(Matrix<2, 1> measurement) {
  Matrix<4, 2> K = (P*(H.transpose()))*(H*P*H.transpose() + R).inverse();
  Xk = (Xk + K*(measurement - H*Xk)).round(1e-9);
  Matrix<4, 4> I = Matrix<4, 4>::identity();
  P = (I - K*H)*P;

  return Xk;
}

}
