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

#include <cstdlib>

#include "../comparison/angle.hpp"

namespace ksn = keisan;

#define FOREACH_ANGLE_TYPE_DO(MACRO, ...) \
  MACRO(ksn::AngleType::Degree, __VA_ARGS__) \
  MACRO(ksn::AngleType::Radian, __VA_ARGS__)

#define FOREACH_FLOAT_TYPE_DO(MACRO, ...) \
  MACRO(float, __VA_ARGS__) \
  MACRO(double, __VA_ARGS__) \
  MACRO(long double, __VA_ARGS__)

#define FOREACH_FLOAT_TYPE_DO2(MACRO, ...) \
  MACRO(float, __VA_ARGS__) \
  MACRO(double, __VA_ARGS__) \
  MACRO(long double, __VA_ARGS__)

#define FOREACH_TYPE_DO(MACRO, ...) \
  FOREACH_FLOAT_TYPE_DO(MACRO, __VA_ARGS__) \
  MACRO(int, __VA_ARGS__) \
  MACRO(int32_t, __VA_ARGS__) \
  MACRO(int64_t, __VA_ARGS__)

using ksn::literals::operator""_deg;
using ksn::literals::operator""_pi;
using ksn::literals::operator""_pi_rad;

TEST(AngleTest, MakeDegree)
{
  EXPECT_FLOAT_EQ(ksn::angle::from_degree(90.0f).degree(), 90.0f);
  EXPECT_DOUBLE_EQ(ksn::angle::from_degree(-45.0).degree(), -45.0);
  EXPECT_DOUBLE_EQ(ksn::angle::from_degree(15.0l).degree(), 15.0l);
}

TEST(AngleTest, MakeRadian)
{
  EXPECT_FLOAT_EQ(ksn::angle::from_radian<float>(0.5_pi).radian(), 0.5_pi);
  EXPECT_DOUBLE_EQ(ksn::angle::from_radian<double>(-0.25_pi).radian(), -0.25_pi);
  EXPECT_DOUBLE_EQ(ksn::angle::from_radian<long double>(0.1_pi).radian(), 0.1_pi);
}

TEST(AngleTest, DegLiterals)
{
  EXPECT_ANGLE_EQ(0_deg, ksn::angle::from_degree(0.0));
  EXPECT_ANGLE_EQ(90_deg, ksn::angle::from_degree(90.0));
  EXPECT_ANGLE_EQ(-45_deg, ksn::angle::from_degree(-45.0));
  EXPECT_ANGLE_EQ(0.0_deg, ksn::angle::from_degree(0.0));
  EXPECT_ANGLE_EQ(12.5_deg, ksn::angle::from_degree(12.5));
  EXPECT_ANGLE_EQ(-2.5_deg, ksn::angle::from_degree(-2.5));
}

TEST(AngleTest, RadLiterals)
{
  EXPECT_ANGLE_EQ(0_pi_rad, ksn::angle::from_radian<double>(0_pi));
  EXPECT_ANGLE_EQ(1_pi_rad, ksn::angle::from_radian<double>(1_pi));
  EXPECT_ANGLE_EQ(-2_pi_rad, ksn::angle::from_radian<double>(-2_pi));
  EXPECT_ANGLE_EQ(0.0_pi_rad, ksn::angle::from_radian<double>(0.0_pi));
  EXPECT_ANGLE_EQ(0.5_pi_rad, ksn::angle::from_radian<double>(0.5_pi));
  EXPECT_ANGLE_EQ(-0.25_pi_rad, ksn::angle::from_radian<double>(-0.25_pi));
}

// This one will test whether ksn::Angle could be declared without initial value
TEST(AngleTest, Empty)
{
  #define EXPECT_COMPILED(TYPE, ANGLE_TYPE) {ksn::Angle<ANGLE_TYPE, TYPE> angle;}
  #define ITERATE_TYPE(ANGLE_TYPE, ...) FOREACH_TYPE_DO(EXPECT_COMPILED, ANGLE_TYPE)
  FOREACH_ANGLE_TYPE_DO(ITERATE_TYPE)
}

// This one will test whether ksn::Angle could be declared with initial value
TEST(AngleTest, ValueConstructor)
{
  #define EXPECT_CORRECT(TYPE, ANGLE_TYPE) \
    { \
      auto val = std::rand() % 200 - 100; \
      ksn::Angle<ANGLE_TYPE, TYPE> angle(val); \
      ASSERT_DOUBLE_EQ(angle.value_in<ANGLE_TYPE>(), val); \
    }
  #undef ITERATE_TYPE
  #define ITERATE_TYPE(ANGLE_TYPE, ...) FOREACH_TYPE_DO(EXPECT_CORRECT, ANGLE_TYPE)
  FOREACH_ANGLE_TYPE_DO(ITERATE_TYPE)
}

// This one will test whether ksn::Angle could be assigned to other ksn::Angle
// with the same angle type but different value type
TEST(AngleTest, SameAngleTypeDifferentTypeAssignment)
{
  #undef EXPECT_CORRECT
  #define EXPECT_CORRECT(TYPE, ANGLE_TYPE, SOURCE) \
    { \
      ksn::Angle<ANGLE_TYPE, TYPE> a(SOURCE), b = SOURCE, c; \
      c = SOURCE; \
      EXPECT_ANGLE_EQ(a, SOURCE); \
      EXPECT_ANGLE_EQ(b, SOURCE); \
      ASSERT_ANGLE_EQ(c, SOURCE); \
    }
  #undef ITERATE_TYPE
  #define ITERATE_TYPE(SOURCE_TYPE, ANGLE_TYPE) \
    { \
      auto val = std::rand() % 200 - 100; \
      auto source = ksn::Angle<ANGLE_TYPE, SOURCE_TYPE>(val); \
      FOREACH_FLOAT_TYPE_DO(EXPECT_CORRECT, ANGLE_TYPE, source) \
    }
  #define ITERATE_SOURCE_TYPE(ANGLE_TYPE, ...) FOREACH_FLOAT_TYPE_DO2(ITERATE_TYPE, ANGLE_TYPE)
  FOREACH_ANGLE_TYPE_DO(ITERATE_SOURCE_TYPE)
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
  EXPECT_ANGLE_EQ(1_pi_rad + 90_deg, 270_deg) << "1pi + 90 = 270";
  EXPECT_ANGLE_EQ(270_deg - 1_pi_rad, 90_deg) << "270 - 1pi = 90";
  EXPECT_ANGLE_EQ(90_deg * 2, 180_deg) << "90 * 2 = 180";
  EXPECT_ANGLE_EQ(2 * 90_deg, 180_deg) << "2 * 90 = 180";
  EXPECT_ANGLE_EQ(180_deg / 3, 60_deg) << "180 / 3 = 60";
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
  EXPECT_ANGLE_EQ((270_deg).normalize(), -90_deg) << "270 = 1 * 360 + (-90)";
  EXPECT_ANGLE_EQ((-0.5_pi_rad).normalize(), -0.5_pi_rad) << "-0.5pi = 0 * 2pi + (-0.5pi)";
}
