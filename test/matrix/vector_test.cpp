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

#include <sstream>

#define ASSERT_VECTOR_N_EQ(N, VECTOR, ...) \
  { \
    ksn::Vector<N> _vector = VECTOR; \
    double _values[] = {__VA_ARGS__}; \
    for (size_t i = 0; i < N; ++i) { \
      ASSERT_DOUBLE_EQ(_values[i], _vector[i]); \
    } \
  }

namespace ksn = keisan;

TEST(VectorTest, OutStream)
{
  auto a = ksn::Vector<2>(1.0, 2.0);

  std::stringstream ss;
  ss << a;

  ASSERT_STREQ(ss.str().c_str(), "[1,2]");
}

TEST(VectorTest, InitialValue)
{
  auto a = ksn::Vector<2>(1.0, 2.0);
  ASSERT_VECTOR_N_EQ(2, a, 1.0, 2.0);

  auto b = ksn::Vector<5>(1.0, 2.0, 3.0, 4.0, 5.0);
  ASSERT_VECTOR_N_EQ(5, b, 1.0, 2.0, 3.0, 4.0, 5.0);
}

TEST(VectorTest, ZeroValue)
{
  auto a = ksn::Vector<2>::zero();
  ASSERT_VECTOR_N_EQ(2, a, 0.0, 0.0);

  auto b = ksn::Vector<5>::zero();
  ASSERT_VECTOR_N_EQ(5, b, 0.0, 0.0, 0.0, 0.0, 0.0);
}

TEST(VectorTest, ComparisonOperation)
{
  auto a = ksn::Vector<5>(1.0, 2.0, 3.0, 4.0, 5.0);
  auto b = a;

  ASSERT_TRUE(a == b);
  ASSERT_FALSE(a != b);

  b[1] = 5.0;

  ASSERT_FALSE(a == b);
  ASSERT_TRUE(a != b);
}

TEST(VectorTest, MatrixMultiplication)
{
  auto a = ksn::Matrix<3, 2>(
    1.0, 1.0,
    2.0, 2.0,
    3.0, 3.0);

  auto b = ksn::Vector<2>(1.0, 2.0);

  ASSERT_VECTOR_N_EQ(3, a * b, 3.0, 6.0, 9.0);
}

TEST(VectorTest, VectorOperation)
{
  auto a = ksn::Vector<5>(1.0, 2.0, 3.0, 4.0, 5.0);
  auto b = ksn::Vector<5>(6.0, 7.0, 8.0, 9.0, 10.0);

  ASSERT_VECTOR_N_EQ(5, a + b, 7.0, 9.0, 11.0, 13.0, 15.0);
  ASSERT_VECTOR_N_EQ(5, a - b, -5.0, -5.0, -5.0, -5.0, -5.0);

  a += b;
  ASSERT_VECTOR_N_EQ(5, a, 7.0, 9.0, 11.0, 13.0, 15.0);

  a -= b;
  ASSERT_VECTOR_N_EQ(5, a, 1.0, 2.0, 3.0, 4.0, 5.0);
}

TEST(VectorTest, ScalarOperation)
{
  auto a = ksn::Vector<5>(1.0, 2.0, 3.0, 4.0, 5.0);

  ASSERT_VECTOR_N_EQ(5, a + 2.0, 3.0, 4.0, 5.0, 6.0, 7.0);
  ASSERT_VECTOR_N_EQ(5, a - 2.0, -1.0, 0.0, 1.0, 2.0, 3.0);
  ASSERT_VECTOR_N_EQ(5, a * 2.0, 2.0, 4.0, 6.0, 8.0, 10.0);
  ASSERT_VECTOR_N_EQ(5, a / 2.0, 0.5, 1.0, 1.5, 2.0, 2.5);

  a += 2.0;
  ASSERT_VECTOR_N_EQ(5, a, 3.0, 4.0, 5.0, 6.0, 7.0);

  a -= 2.0;
  ASSERT_VECTOR_N_EQ(5, a, 1.0, 2.0, 3.0, 4.0, 5.0);

  a *= 2.0;
  ASSERT_VECTOR_N_EQ(5, a, 2.0, 4.0, 6.0, 8.0, 10.0);

  a /= 2.0;
  ASSERT_VECTOR_N_EQ(5, a, 1.0, 2.0, 3.0, 4.0, 5.0);
}

TEST(VectorTest, NegationOperation)
{
  auto a = ksn::Vector<5>(1.0, 2.0, 3.0, 4.0, 5.0);
  ASSERT_VECTOR_N_EQ(5, -a, -1.0, -2.0, -3.0, -4.0, -5.0);
}
