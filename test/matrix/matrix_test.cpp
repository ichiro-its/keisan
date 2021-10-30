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

#include <sstream>

#include "gtest/gtest.h"
#include "keisan/keisan.hpp"

#define ASSERT_MATRIX_M_N_EQ(M, N, MATRIX, ...) \
  { \
    ksn::Matrix<M, N> _matrix = MATRIX; \
    double _values[] = {__VA_ARGS__}; \
    for (size_t i = 0; i < M; ++i) { \
      for (size_t j = 0; j < N; ++j) { \
        ASSERT_DOUBLE_EQ(_values[i * N + j], _matrix[i][j]); \
      } \
    } \
  }

namespace ksn = keisan;

TEST(MatrixTest, OutStream)
{
  auto a = ksn::Matrix<3, 4>(
    1.0, 1.0, 1.0, 1.0,
    2.0, 2.0, 2.0, 2.0,
    3.0, 3.0, 3.0, 3.0);

  std::stringstream ss;
  ss << a;

  ASSERT_STREQ(ss.str().c_str(), "[[1,1,1,1],[2,2,2,2],[3,3,3,3]]");
}

TEST(MatrixTest, InitialValue)
{
  auto a = ksn::Matrix<2, 1>(1.0, 2.0);
  ASSERT_MATRIX_M_N_EQ(2, 1, a, 1.0, 2.0);

  auto b = ksn::Matrix<3, 4>(
    1.0, 1.0, 1.0, 1.0,
    2.0, 2.0, 2.0, 2.0,
    3.0, 3.0, 3.0, 3.0);

  ASSERT_MATRIX_M_N_EQ(
    3, 4, b,
    1.0, 1.0, 1.0, 1.0,
    2.0, 2.0, 2.0, 2.0,
    3.0, 3.0, 3.0, 3.0);
}

TEST(MatrixTest, ZeroValue)
{
  auto a = ksn::Matrix<2, 1>::zero();
  ASSERT_MATRIX_M_N_EQ(2, 1, a, 0.0, 0.0);

  auto b = ksn::Matrix<3, 4>::zero();
  ASSERT_MATRIX_M_N_EQ(
    3, 4, b,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0);
}

TEST(MatrixTest, ComparisonOperation)
{
  auto a = ksn::Matrix<3, 4>(
    1.0, 1.0, 1.0, 1.0,
    2.0, 2.0, 2.0, 2.0,
    3.0, 3.0, 3.0, 3.0);

  auto b = a;

  ASSERT_TRUE(a == b);
  ASSERT_FALSE(a != b);

  b[1][1] = 5.0;

  ASSERT_FALSE(a == b);
  ASSERT_TRUE(a != b);
}

TEST(MatrixTest, MatrixMultiplication)
{
  auto a = ksn::Matrix<3, 2>(
    1.0, 1.0,
    2.0, 2.0,
    3.0, 3.0);

  auto b = ksn::Matrix<2, 2>(
    1.0, 1.0,
    2.0, 2.0);

  ASSERT_MATRIX_M_N_EQ(
    3, 2, a * b,
    3.0, 3.0,
    6.0, 6.0,
    9.0, 9.0);
}

TEST(MatrixTest, MatrixOperation)
{
  auto a = ksn::Matrix<3, 4>(
    1.0, 1.0, 1.0, 1.0,
    2.0, 2.0, 2.0, 2.0,
    3.0, 3.0, 3.0, 3.0);

  auto b = ksn::Matrix<3, 4>(
    1.0, 2.0, 3.0, 4.0,
    1.0, 2.0, 3.0, 4.0,
    1.0, 2.0, 3.0, 4.0);

  ASSERT_MATRIX_M_N_EQ(
    3, 4, a + b,
    2.0, 3.0, 4.0, 5.0,
    3.0, 4.0, 5.0, 6.0,
    4.0, 5.0, 6.0, 7.0);

  ASSERT_MATRIX_M_N_EQ(
    3, 4, a - b,
    0.0, -1.0, -2.0, -3.0,
    1.0, 0.0, -1.0, -2.0,
    2.0, 1.0, 0.0, -1.0);

  a += b;
  ASSERT_MATRIX_M_N_EQ(
    3, 4, a,
    2.0, 3.0, 4.0, 5.0,
    3.0, 4.0, 5.0, 6.0,
    4.0, 5.0, 6.0, 7.0);

  a -= b;
  ASSERT_MATRIX_M_N_EQ(
    3, 4, a,
    1.0, 1.0, 1.0, 1.0,
    2.0, 2.0, 2.0, 2.0,
    3.0, 3.0, 3.0, 3.0);
}

TEST(MatrixTest, ScalarOperation)
{
  auto a = ksn::Matrix<3, 4>(
    1.0, 1.0, 1.0, 1.0,
    2.0, 2.0, 2.0, 2.0,
    3.0, 3.0, 3.0, 3.0);

  ASSERT_MATRIX_M_N_EQ(
    3, 4, a + 2.0,
    3.0, 3.0, 3.0, 3.0,
    4.0, 4.0, 4.0, 4.0,
    5.0, 5.0, 5.0, 5.0);

  ASSERT_MATRIX_M_N_EQ(
    3, 4, a - 2.0,
    -1.0, -1.0, -1.0, -1.0,
    0.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 1.0);

  ASSERT_MATRIX_M_N_EQ(
    3, 4, a * 2.0,
    2.0, 2.0, 2.0, 2.0,
    4.0, 4.0, 4.0, 4.0,
    6.0, 6.0, 6.0, 6.0);

  ASSERT_MATRIX_M_N_EQ(
    3, 4, 2.0 * a,
    2.0, 2.0, 2.0, 2.0,
    4.0, 4.0, 4.0, 4.0,
    6.0, 6.0, 6.0, 6.0);

  ASSERT_MATRIX_M_N_EQ(
    3, 4, a / 2.0,
    0.5, 0.5, 0.5, 0.5,
    1.0, 1.0, 1.0, 1.0,
    1.5, 1.5, 1.5, 1.5);

  a += 2.0;
  ASSERT_MATRIX_M_N_EQ(
    3, 4, a,
    3.0, 3.0, 3.0, 3.0,
    4.0, 4.0, 4.0, 4.0,
    5.0, 5.0, 5.0, 5.0);

  a -= 2.0;
  ASSERT_MATRIX_M_N_EQ(
    3, 4, a,
    1.0, 1.0, 1.0, 1.0,
    2.0, 2.0, 2.0, 2.0,
    3.0, 3.0, 3.0, 3.0);

  a *= 2.0;
  ASSERT_MATRIX_M_N_EQ(
    3, 4, a,
    2.0, 2.0, 2.0, 2.0,
    4.0, 4.0, 4.0, 4.0,
    6.0, 6.0, 6.0, 6.0);

  a /= 2.0;
  ASSERT_MATRIX_M_N_EQ(
    3, 4, a,
    1.0, 1.0, 1.0, 1.0,
    2.0, 2.0, 2.0, 2.0,
    3.0, 3.0, 3.0, 3.0);
}

TEST(MatrixTest, NegationOperation)
{
  auto a = ksn::Matrix<3, 4>(
    1.0, 1.0, 1.0, 1.0,
    2.0, 2.0, 2.0, 2.0,
    3.0, 3.0, 3.0, 3.0);

  ASSERT_MATRIX_M_N_EQ(
    3, 4, -a,
    -1.0, -1.0, -1.0, -1.0,
    -2.0, -2.0, -2.0, -2.0,
    -3.0, -3.0, -3.0, -3.0);
}
