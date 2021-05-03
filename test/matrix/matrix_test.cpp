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

#define ASSERT_MATRIX_M_N_EQ(M, N, MATRIX, ...) \
  { \
    keisan::Matrix<M, N> _matrix = MATRIX; \
    double _values[] = {__VA_ARGS__}; \
    for (size_t i = 0; i < M; ++i) { \
      for (size_t j = 0; j < N; ++j) { \
        ASSERT_DOUBLE_EQ(_values[i * N + j], _matrix[i][j]); \
      } \
    } \
  }

TEST(MatrixTest, InitialValue)
{
  ASSERT_MATRIX_M_N_EQ(2, 1, (keisan::Matrix<2, 1>(1.0, 2.0)), 1.0, 2.0);

  ASSERT_MATRIX_M_N_EQ(
    3, 4,
    (keisan::Matrix<3, 4>(
      1.0, 1.0, 1.0, 1.0,
      2.0, 2.0, 2.0, 2.0,
      3.0, 3.0, 3.0, 3.0)),
    1.0, 1.0, 1.0, 1.0,
    2.0, 2.0, 2.0, 2.0,
    3.0, 3.0, 3.0, 3.0);
}

TEST(MatrixTest, ZeroValue)
{
  ASSERT_MATRIX_M_N_EQ(2, 1, (keisan::Matrix<2, 1>::zero()), 0.0, 0.0);

  ASSERT_MATRIX_M_N_EQ(
    3, 4, (keisan::Matrix<3, 4>::zero()),
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0);
}
