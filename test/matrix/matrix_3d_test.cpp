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

#define ASSERT_MATRIX3D_EQ(MATRIX, ...) \
  { \
    ksn::Matrix<4, 4> _matrix = MATRIX; \
    double _values[] = {__VA_ARGS__}; \
    for (size_t i = 0; i < 4; ++i) { \
      for (size_t j = 0; j < 4; ++j) { \
        ASSERT_DOUBLE_EQ(_values[i * 4 + j], _matrix[i][j]); \
      } \
    } \
  }

namespace ksn = keisan;

TEST(Matrix3DTest, Identity)
{
  ASSERT_MATRIX3D_EQ(
    ksn::Matrix3D::identity(),
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0);
}

#define ASSERT_MATRIX3D_NEAR(MATRIX, ...) \
  { \
    ksn::Matrix<4, 4> _matrix = MATRIX; \
    double _values[] = {__VA_ARGS__}; \
    for (size_t i = 0; i < 4; ++i) { \
      for (size_t j = 0; j < 4; ++j) { \
        ASSERT_NEAR(_values[i * 4 + j], _matrix[i][j], 1e-2); \
      } \
    } \
  }

TEST(Matrix3DTest, Transform)
{
  auto point = ksn::Point3(0.0, 0.0, 0.0);
  auto angle = ksn::Vector<3>(0.0, 0.0, 0.0);

  ASSERT_MATRIX3D_EQ(
    ksn::Matrix3D::transformation_of(point, angle),
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0);

  point.x = 1.0;
  angle[0] = ksn::pi<double>;

  ASSERT_MATRIX3D_NEAR(
    ksn::Matrix3D::transformation_of(point, angle),
    1.0, 0.0, 0.0, 1.0,
    0.0, -1.0, -1e-16, 0.0,
    0.0, 1e-16, -1.0, 0.0,
    0.0, 0.0, 0.0, 1.0);

  point.z = 1.0;
  angle[0] /= 2.0;

  ASSERT_MATRIX3D_NEAR(
    ksn::Matrix3D::transformation_of(point, angle),
    1.0, 0.0, 0.0, 1.0,
    0.0, 6e-17, -1.0, 0.0,
    0.0, 1.0, 6e-17, 1.0,
    0.0, 0.0, 0.0, 1.0);

  angle[0] = 0.0;
  angle[1] = ksn::pi<double>;

  ASSERT_MATRIX3D_NEAR(
    ksn::Matrix3D::transformation_of(point, angle),
    -1.0, 0.0, 1e-16, 1.0,
    0.0, 1.0, 0.0, 0.0,
    -1e-16, 0.0, -1.0, 1.0,
    0.0, 0.0, 0.0, 1.0);

  angle[2] = ksn::pi<double>;

  ASSERT_MATRIX3D_NEAR(
    ksn::Matrix3D::transformation_of(point, angle),
    1.0, -1e-16, 1e-16, 1.0,
    -1e-16, -1.0, 1e-32, 0.0,
    -1e-16, 0.0, -1.0, 1.0,
    0.0, 0.0, 0.0, 1.0);
}
