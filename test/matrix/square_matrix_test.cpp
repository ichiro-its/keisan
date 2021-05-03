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

#include <gtest/gtest.h>
#include <keisan/keisan.hpp>

#define ASSERT_SQUARE_MATRIX_N_EQ(N, SQUARE_MATRIX, ...) \
  { \
    keisan::SquareMatrix<N> _square_matrix = SQUARE_MATRIX; \
    double _values[] = {__VA_ARGS__}; \
    for (size_t i = 0; i < N; ++i) { \
      for (size_t j = 0; j < N; ++j) { \
        ASSERT_DOUBLE_EQ(_values[i * N + j], _square_matrix[i][j]); \
      } \
    } \
  }

TEST(SquareMatrixTest, InitialValue)
{
  auto a = keisan::SquareMatrix<2>(
    1.0, 1.0,
    2.0, 2.0);

  ASSERT_SQUARE_MATRIX_N_EQ(
    2, a,
    1.0, 1.0,
    2.0, 2.0);

  auto b = keisan::SquareMatrix<4>(
    1.0, 1.0, 1.0, 1.0,
    2.0, 2.0, 2.0, 2.0,
    3.0, 3.0, 3.0, 3.0,
    4.0, 4.0, 4.0, 4.0);

  ASSERT_SQUARE_MATRIX_N_EQ(
    4, b,
    1.0, 1.0, 1.0, 1.0,
    2.0, 2.0, 2.0, 2.0,
    3.0, 3.0, 3.0, 3.0,
    4.0, 4.0, 4.0, 4.0);
}

TEST(SquareMatrixTest, ZeroValue)
{
  auto a = keisan::SquareMatrix<2>::zero();
  ASSERT_SQUARE_MATRIX_N_EQ(
    2, a,
    0.0, 0.0,
    0.0, 0.0);

  auto b = keisan::SquareMatrix<4>::zero();
  ASSERT_SQUARE_MATRIX_N_EQ(
    4, b,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0);
}

TEST(SquareMatrixTest, IdentityValue)
{
  auto a = keisan::SquareMatrix<2>::identity();
  ASSERT_SQUARE_MATRIX_N_EQ(
    2, a,
    1.0, 0.0,
    0.0, 1.0);

  auto b = keisan::SquareMatrix<4>::identity();
  ASSERT_SQUARE_MATRIX_N_EQ(
    4, b,
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0);
}

TEST(SquareMatrixTest, SquareMatrixMultiplication)
{
  auto a = keisan::SquareMatrix<2>(
    1.0, 1.0,
    2.0, 2.0);

  auto b = keisan::SquareMatrix<2>(
    3.0, 3.0,
    4.0, 4.0);

  ASSERT_SQUARE_MATRIX_N_EQ(
    2, a * b,
    7.0, 7.0,
    14.0, 14.0);
}

TEST(SquareMatrixTest, MatrixOperation)
{
  auto a = keisan::SquareMatrix<3>(
    1.0, 1.0, 1.0,
    2.0, 2.0, 2.0,
    3.0, 3.0, 3.0);

  auto b = keisan::SquareMatrix<3>(
    1.0, 2.0, 3.0,
    1.0, 2.0, 3.0,
    1.0, 2.0, 3.0);

  ASSERT_SQUARE_MATRIX_N_EQ(
    3, a + b,
    2.0, 3.0, 4.0,
    3.0, 4.0, 5.0,
    4.0, 5.0, 6.0);

  ASSERT_SQUARE_MATRIX_N_EQ(
    3, a - b,
    0.0, -1.0, -2.0,
    1.0, 0.0, -1.0,
    2.0, 1.0, 0.0);

  a += b;
  ASSERT_SQUARE_MATRIX_N_EQ(
    3, a,
    2.0, 3.0, 4.0,
    3.0, 4.0, 5.0,
    4.0, 5.0, 6.0);

  a -= b;
  ASSERT_SQUARE_MATRIX_N_EQ(
    3, a,
    1.0, 1.0, 1.0,
    2.0, 2.0, 2.0,
    3.0, 3.0, 3.0);
}

TEST(SquareMatrixTest, ScalarOperation)
{
  auto a = keisan::SquareMatrix<3>(
    1.0, 1.0, 1.0,
    2.0, 2.0, 2.0,
    3.0, 3.0, 3.0);

  ASSERT_SQUARE_MATRIX_N_EQ(
    3, a + 2.0,
    3.0, 3.0, 3.0,
    4.0, 4.0, 4.0,
    5.0, 5.0, 5.0);

  ASSERT_SQUARE_MATRIX_N_EQ(
    3, a - 2.0,
    -1.0, -1.0, -1.0,
    0.0, 0.0, 0.0,
    1.0, 1.0, 1.0);

  ASSERT_SQUARE_MATRIX_N_EQ(
    3, a * 2.0,
    2.0, 2.0, 2.0,
    4.0, 4.0, 4.0,
    6.0, 6.0, 6.0);

  ASSERT_SQUARE_MATRIX_N_EQ(
    3, a / 2.0,
    0.5, 0.5, 0.5,
    1.0, 1.0, 1.0,
    1.5, 1.5, 1.5);

  a += 2.0;
  ASSERT_SQUARE_MATRIX_N_EQ(
    3, a,
    3.0, 3.0, 3.0,
    4.0, 4.0, 4.0,
    5.0, 5.0, 5.0);

  a -= 2.0;
  ASSERT_SQUARE_MATRIX_N_EQ(
    3, a,
    1.0, 1.0, 1.0,
    2.0, 2.0, 2.0,
    3.0, 3.0, 3.0);

  a *= 2.0;
  ASSERT_SQUARE_MATRIX_N_EQ(
    3, a,
    2.0, 2.0, 2.0,
    4.0, 4.0, 4.0,
    6.0, 6.0, 6.0);

  a /= 2.0;
  ASSERT_SQUARE_MATRIX_N_EQ(
    3, a,
    1.0, 1.0, 1.0,
    2.0, 2.0, 2.0,
    3.0, 3.0, 3.0);
}
