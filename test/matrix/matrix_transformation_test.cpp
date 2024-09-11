// Copyright (c) 2021 ICHIRO ITS
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

#include "gtest/gtest.h"
#include "keisan/keisan.hpp"

#define ASSERT_MATRIX_M_N_NEAR(M, N, MATRIX, ...)             \
  {                                                           \
    ksn::Matrix<M, N> _matrix = MATRIX;                       \
    double _values[] = {__VA_ARGS__};                         \
    for (size_t i = 0; i < M; ++i) {                          \
      for (size_t j = 0; j < N; ++j) {                        \
        ASSERT_NEAR(_values[i * N + j], _matrix[i][j], 1e-2); \
      }                                                       \
    }                                                         \
  }

namespace ksn = keisan;

TEST(MatrixTransformationTest, Translation)
{
  auto point2 = ksn::Point2(0.0, 0.0);

  ASSERT_MATRIX_M_N_NEAR(
    3, 3, ksn::translation_matrix(point2), 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

  point2.x = 1.0;

  ASSERT_MATRIX_M_N_NEAR(
    3, 3, ksn::translation_matrix(point2), 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

  auto point3 = ksn::Point3(0.0, 0.0, 0.0);

  ASSERT_MATRIX_M_N_NEAR(
    4, 4, ksn::translation_matrix(point3), 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0);

  point3.y = 2.0;

  ASSERT_MATRIX_M_N_NEAR(
    4, 4, ksn::translation_matrix(point3), 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 2.0, 0.0, 0.0, 1.0,
    0.0, 0.0, 0.0, 0.0, 1.0);
}

TEST(MatrixTransformationTest, Rotation)
{
  auto angle = ksn::make_radian(0.0);

  ASSERT_MATRIX_M_N_NEAR(
    3, 3, ksn::rotation_matrix(angle), 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);

  angle = ksn::make_radian(ksn::pi<double>);

  ASSERT_MATRIX_M_N_NEAR(
    3, 3, ksn::rotation_matrix(angle), -1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0);

  angle /= 2;

  ASSERT_MATRIX_M_N_NEAR(
    3, 3, ksn::rotation_matrix(angle), 0.0, -1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);

  angle /= 2;

  ASSERT_MATRIX_M_N_NEAR(
    3, 3, ksn::rotation_matrix(angle), 0.7, -0.7, 0.0, 0.7, 0.7, 0.0, 0.0, 0.0, 1.0);

  auto euler =
    ksn::Euler<double>(ksn::make_radian(0.0), ksn::make_radian(0.0), ksn::make_radian(0.0));

  ASSERT_MATRIX_M_N_NEAR(
    4, 4, ksn::rotation_matrix(euler), 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0);

  euler.roll = ksn::make_radian(ksn::pi<double>);

  ASSERT_MATRIX_M_N_NEAR(
    4, 4, ksn::rotation_matrix(euler), 1.0, 0.0, 0.0, 0.0, 0.0, -1.0, -1e-16, 0.0, 0.0, 1e-16, -1.0,
    0.0, 0.0, 0.0, 0.0, 1.0);

  euler.roll /= 2;

  ASSERT_MATRIX_M_N_NEAR(
    4, 4, ksn::rotation_matrix(euler), 1.0, 0.0, 0.0, 0.0, 0.0, 6e-17, -1.0, 0.0, 0.0, 1.0, 6e-17,
    0.0, 0.0, 0.0, 0.0, 1.0);

  euler.roll = ksn::make_radian(0.0);
  euler.pitch = ksn::make_radian(ksn::pi<double>);

  ASSERT_MATRIX_M_N_NEAR(
    4, 4, ksn::rotation_matrix(euler), -1.0, 0.0, 1e-16, 0.0, 0.0, 1.0, 0.0, 0.0, -1e-16, 0.0, -1.0,
    0.0, 0.0, 0.0, 0.0, 1.0);

  euler.yaw = ksn::make_radian(ksn::pi<double>);

  ASSERT_MATRIX_M_N_NEAR(
    4, 4, ksn::rotation_matrix(euler), 1.0, -1e-16, 1e-16, 0.0, -1e-16, -1.0, 1e-32, 0.0, -1e-16,
    0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

TEST(MatrixTransformationTest, Transformation)
{
  auto point2 = ksn::Point2(1.0, 0.0);
  auto angle = ksn::make_radian(ksn::pi<double>);

  ASSERT_MATRIX_M_N_NEAR(
    3, 3, ksn::translation_matrix(point2) * ksn::rotation_matrix(angle), -1.0, 0.0, 1.0, 0.0, -1.0,
    0.0, 0.0, 0.0, 1.0);

  point2.y = 2.0;
  angle /= 4;

  ASSERT_MATRIX_M_N_NEAR(
    3, 3, ksn::translation_matrix(point2) * ksn::rotation_matrix(angle), 0.7, -0.7, 1.0, 0.7, 0.7,
    2.0, 0.0, 0.0, 1.0);

  auto point3 = ksn::Point3(0.0, 2.0, 0.0);
  auto euler = ksn::Euler<double>(
    ksn::make_radian(ksn::pi<double>), ksn::make_radian(0.0), ksn::make_radian(0.0));

  ASSERT_MATRIX_M_N_NEAR(
    4, 4, ksn::translation_matrix(point3) * ksn::rotation_matrix(euler), 1.0, 0.0, 0.0, 0.0, 0.0,
    -1.0, -1e-16, 2.0, 0.0, 1e-16, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0);

  point3.z = 3.0;
  euler.roll = ksn::make_radian(0.0);
  euler.pitch = ksn::make_radian(ksn::pi<double>);

  ASSERT_MATRIX_M_N_NEAR(
    4, 4, ksn::translation_matrix(point3) * ksn::rotation_matrix(euler), -1.0, 0.0, 1e-16, 0.0, 0.0,
    1.0, 0.0, 2.0, -1e-16, 0.0, -1.0, 3.0, 0.0, 0.0, 0.0, 1.0);

  point3.z = 1.0;
  euler.yaw = ksn::make_radian(ksn::pi<double>);

  ASSERT_MATRIX_M_N_NEAR(
    4, 4, ksn::translation_matrix(point3) * ksn::rotation_matrix(euler), 1.0, -1e-16, 1e-16, 0.0,
    -1e-16, -1.0, 1e-32, 2.0, -1e-16, 0.0, -1.0, 1.0, 0.0, 0.0, 0.0, 1.0);
}
