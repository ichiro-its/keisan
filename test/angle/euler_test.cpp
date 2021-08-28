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

using ksn::literals::operator""_deg;
using ksn::literals::operator""_pi_rad;

TEST(EulerTest, Empty)
{
  ksn::Euler<float> float_euler;
  ksn::Euler<double> double_euler;
  ksn::Euler<long double> long_double_euler;
}

TEST(EulerTest, RpyConstructor)
{
  #define EXPECT_RPY_CONSTRUCTOR(TYPE) \
  { \
    ksn::Euler<TYPE> euler(0_deg, 90_deg, 180_deg); \
    EXPECT_DOUBLE_EQ(euler.roll.degree(), 0.0); \
    EXPECT_DOUBLE_EQ(euler.pitch.degree(), 90.0); \
    EXPECT_DOUBLE_EQ(euler.yaw.degree(), 180.0); \
  }

  EXPECT_RPY_CONSTRUCTOR(float);
  EXPECT_RPY_CONSTRUCTOR(double);
  EXPECT_RPY_CONSTRUCTOR(long double);
}

TEST(EulerTest, AssignmentConstructor)
{
  #define EXPECT_CONVERSION_CONSTRUCTOR(TYPE, SOURCE) \
  { \
    ksn::Euler<TYPE> a(SOURCE), b = SOURCE, c; \
    c = SOURCE; \
    EXPECT_EQ(a, SOURCE); \
    EXPECT_EQ(b, SOURCE); \
    EXPECT_EQ(c, SOURCE); \
  }

  ksn::Euler<float> float_euler(90_deg, 90_deg, 90_deg);
  ksn::Euler<double> double_euler(-45_deg, -45_deg, -45_deg);
  ksn::Euler<long double> long_double_euler(15_deg, 15_deg, 15_deg);

  #define LOOP_EXPECT_CONVERSION_CONSTRUCTOR(TYPE) \
  { \
    EXPECT_CONVERSION_CONSTRUCTOR(TYPE, float_euler) \
    EXPECT_CONVERSION_CONSTRUCTOR(TYPE, double_euler) \
    EXPECT_CONVERSION_CONSTRUCTOR(TYPE, long_double_euler) \
  }

  LOOP_EXPECT_CONVERSION_CONSTRUCTOR(float)
  LOOP_EXPECT_CONVERSION_CONSTRUCTOR(double)
  LOOP_EXPECT_CONVERSION_CONSTRUCTOR(long double)
}

TEST(EulerTest, ComparisonOperator)
{
  ksn::Euler<double> a(0.0_deg, 90.0_deg, 180.0_deg);

  auto b = a;

  ASSERT_TRUE(a == b);
  ASSERT_FALSE(a != b);

  a.roll = 1_pi_rad;

  ASSERT_FALSE(a == b);
  ASSERT_TRUE(a != b);
}

TEST(EulerTest, QuaternionConversion)
{
  ksn::Euler<double> euler(0.0_deg, 0.0_deg, 90.0_deg);

  auto quaternion = euler.quaternion();

  ASSERT_EQ(quaternion.euler(), euler);
}
