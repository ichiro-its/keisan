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

namespace ksn = keisan;

TEST(QuaternionTest, Empty)
{
  ksn::Quaternion<float> float_quaternion;
  ksn::Quaternion<double> double_quaternion;
  ksn::Quaternion<long double> long_double_quaternion;
}

TEST(QuaternionTest, XyzwConstructor){
#define EXPECT_XYZW_CONSTRUCTOR(TYPE)                      \
  {                                                        \
    ksn::Quaternion<TYPE> quaternion(1.0, 0.5, 0.0, -0.5); \
    EXPECT_DOUBLE_EQ(quaternion.x, 1.0);                   \
    EXPECT_DOUBLE_EQ(quaternion.y, 0.5);                   \
    EXPECT_DOUBLE_EQ(quaternion.z, 0.0);                   \
    EXPECT_DOUBLE_EQ(quaternion.w, -0.5);                  \
  }

  EXPECT_XYZW_CONSTRUCTOR(float) EXPECT_XYZW_CONSTRUCTOR(double)
    EXPECT_XYZW_CONSTRUCTOR(long double)}

TEST(QuaternionTest, AssignmentConstructor)
{
#define EXPECT_CONVERSION_CONSTRUCTOR(TYPE, SOURCE) \
  {                                                 \
    ksn::Quaternion<TYPE> a(SOURCE), b = SOURCE, c; \
    c = SOURCE;                                     \
    EXPECT_TRUE(a == SOURCE);                       \
    EXPECT_TRUE(b == SOURCE);                       \
    EXPECT_TRUE(c == SOURCE);                       \
  }

  ksn::Quaternion<float> float_quaternion(1.0f, 1.0f, 1.0f, 1.0f);
  ksn::Quaternion<double> double_quaternion(0.5, 0.5, 0.5, 0.5);
  ksn::Quaternion<long double> long_double_quaternion(-0.5l, -0.5l, -0.5l, -0.5l);

#define LOOP_EXPECT_CONVERSION_CONSTRUCTOR(TYPE)                                        \
  {EXPECT_CONVERSION_CONSTRUCTOR(TYPE, float_quaternion) EXPECT_CONVERSION_CONSTRUCTOR( \
    TYPE, double_quaternion) EXPECT_CONVERSION_CONSTRUCTOR(TYPE, long_double_quaternion)}

  LOOP_EXPECT_CONVERSION_CONSTRUCTOR(float)
  LOOP_EXPECT_CONVERSION_CONSTRUCTOR(double)
  LOOP_EXPECT_CONVERSION_CONSTRUCTOR(long double)
}

TEST(QuaternionTest, ComparisonOperator)
{
  ksn::Quaternion<double> a(1.0, 0.5, 0.0, -0.5);

  auto b = a;

  ASSERT_TRUE(a == b);
  ASSERT_FALSE(a != b);

  a.x = 0.0;

  ASSERT_FALSE(a == b);
  ASSERT_TRUE(a != b);
}
