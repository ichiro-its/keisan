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

#include <iomanip>
#include <sstream>

#include "gtest/gtest.h"
#include "keisan/keisan.hpp"

namespace ksn = keisan;

using ksn::literals::operator""_deg;
using ksn::literals::operator""_pi;
using ksn::literals::operator""_pi_rad;

TEST(AngleTest, MakeDegree)
{
  EXPECT_FLOAT_EQ(ksn::make_degree(90.0f).degree(), 90.0f);
  EXPECT_DOUBLE_EQ(ksn::make_degree(-45.0).degree(), -45.0);
  EXPECT_DOUBLE_EQ(ksn::make_degree(15.0l).degree(), 15.0l);
}

TEST(AngleTest, MakeRadian)
{
  EXPECT_FLOAT_EQ(ksn::make_radian<float>(0.5_pi).radian(), 0.5_pi);
  EXPECT_DOUBLE_EQ(ksn::make_radian<double>(-0.25_pi).radian(), -0.25_pi);
  EXPECT_DOUBLE_EQ(ksn::make_radian<long double>(0.1_pi).radian(), 0.1_pi);
}

TEST(AngleTest, DegLiterals)
{
  EXPECT_EQ(0_deg, ksn::make_degree(0.0));
  EXPECT_EQ(90_deg, ksn::make_degree(90.0));
  EXPECT_EQ(-45_deg, ksn::make_degree(-45.0));
  EXPECT_EQ(0.0_deg, ksn::make_degree(0.0));
  EXPECT_EQ(12.5_deg, ksn::make_degree(12.5));
  EXPECT_EQ(-2.5_deg, ksn::make_degree(-2.5));
}

TEST(AngleTest, RadLiterals)
{
  EXPECT_EQ(0_pi_rad, ksn::make_radian<double>(0_pi));
  EXPECT_EQ(1_pi_rad, ksn::make_radian<double>(1_pi));
  EXPECT_EQ(-2_pi_rad, ksn::make_radian<double>(-2_pi));
  EXPECT_EQ(0.0_pi_rad, ksn::make_radian<double>(0.0_pi));
  EXPECT_EQ(0.5_pi_rad, ksn::make_radian<double>(0.5_pi));
  EXPECT_EQ(-0.25_pi_rad, ksn::make_radian<double>(-0.25_pi));
}

TEST(AngleTest, OutputStream)
{
  std::stringstream ss;
  ss << 90_deg << " " << -1_pi_rad;

  EXPECT_STREQ(ss.str().c_str(), "90 -180");
}

TEST(AngleTest, Empty)
{
  ksn::Angle<float> float_angle;
  ksn::Angle<double> double_angle;
  ksn::Angle<long double> long_double_angle;
}

TEST(AngleTest, AssignmentConstructor)
{
  #define EXPECT_CONVERSION_CONSTRUCTOR(TYPE, SOURCE) \
  { \
    ksn::Angle<TYPE> a(SOURCE), b = SOURCE, c; \
    c = SOURCE; \
    EXPECT_DOUBLE_EQ(a.degree(), SOURCE.degree()); \
    EXPECT_DOUBLE_EQ(b.degree(), SOURCE.degree()); \
    EXPECT_DOUBLE_EQ(c.degree(), SOURCE.degree()); \
  }

  auto float_angle = ksn::make_degree(90.0f);
  auto double_angle = ksn::make_degree(-45.0);
  auto long_double_angle = ksn::make_degree(15.0l);

  #define LOOP_EXPECT_CONVERSION_CONSTRUCTOR(TYPE) \
  { \
    EXPECT_CONVERSION_CONSTRUCTOR(TYPE, float_angle) \
    EXPECT_CONVERSION_CONSTRUCTOR(TYPE, double_angle) \
    EXPECT_CONVERSION_CONSTRUCTOR(TYPE, long_double_angle) \
  }

  LOOP_EXPECT_CONVERSION_CONSTRUCTOR(float)
  LOOP_EXPECT_CONVERSION_CONSTRUCTOR(double)
  LOOP_EXPECT_CONVERSION_CONSTRUCTOR(long double)
}

TEST(AngleTest, ComparisonOperator)
{
  auto a = 90_deg;
  auto b = -180_deg;
  auto c = -1_pi_rad;

  EXPECT_TRUE(b == c && a != c) <<
    "-180 == -1pi\n"
    "90 != -1pi";

  EXPECT_TRUE(a > b && a >= b && a >= a) << "90 > -180";
  EXPECT_TRUE(b < a && b <= a && b <= b) << "-180 < 90";
}

TEST(AngleTest, SelfMathOperator)
{
  auto angle = 1_pi_rad;

  angle += 90_deg;
  ASSERT_EQ(angle, 270_deg) << "1pi + 90 = 270";

  angle -= 1_pi_rad;
  ASSERT_EQ(angle, 90_deg) << "270 - 1pi = 90";

  angle *= 2;
  ASSERT_EQ(angle, 180_deg) << "90 * 2 = 180";

  angle /= 3;
  ASSERT_EQ(angle, 60_deg) << "180 / 3 = 60";
}

TEST(AngleTest, MathOperator)
{
  EXPECT_EQ(1_pi_rad + 90_deg, 270_deg) << "1pi + 90 = 270";
  EXPECT_EQ(270_deg - 1_pi_rad, 90_deg) << "270 - 1pi = 90";
  EXPECT_EQ(90_deg * 2, 180_deg) << "90 * 2 = 180";
  EXPECT_EQ(2 * 90_deg, 180_deg) << "2 * 90 = 180";
  EXPECT_EQ(180_deg / 3, 60_deg) << "180 / 3 = 60";
}

TEST(AngleTest, NegationOperator)
{
  auto angle = -90.0_deg;
  EXPECT_DOUBLE_EQ(angle.degree(), -90.0);
}

TEST(AngleTest, Conversion)
{
  auto a = 270_deg;
  auto b = -0.5_pi_rad;

  EXPECT_DOUBLE_EQ(a.degree(), 270.0);
  EXPECT_DOUBLE_EQ(a.radian(), 1.5_pi) << "270 == 1.5pi";
  EXPECT_DOUBLE_EQ(b.degree(), -90.0) << "-0.5pi == -90";
  EXPECT_DOUBLE_EQ(b.radian(), -0.5_pi);
}

TEST(AngleTest, Normalize)
{
  EXPECT_EQ((270_deg).normalize(), -90_deg) << "270 = 1 * 360 + (-90)";
  EXPECT_EQ((-0.5_pi_rad).normalize(), -0.5_pi_rad) << "-0.5pi = 0 * 2pi + (-0.5pi)";
}
