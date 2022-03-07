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

#define FOREACH_ANGLE_TYPE_DO(MACRO, ...) \
  MACRO(ksn::AngleType::Degree, __VA_ARGS__) \
  MACRO(ksn::AngleType::Radian, __VA_ARGS__)

#define FOREACH_TYPE_DO(MACRO, ...) \
  MACRO(float, __VA_ARGS__) \
  MACRO(double, __VA_ARGS__) \
  MACRO(long double, __VA_ARGS__) \
  MACRO(int, __VA_ARGS__) \
  MACRO(int32_t, __VA_ARGS__) \
  MACRO(int64_t, __VA_ARGS__)

#define FOREACH_TYPE_DO2(MACRO, ...) \
  MACRO(float, __VA_ARGS__) \
  MACRO(double, __VA_ARGS__) \
  MACRO(long double, __VA_ARGS__) \
  MACRO(int, __VA_ARGS__) \
  MACRO(int32_t, __VA_ARGS__) \
  MACRO(int64_t, __VA_ARGS__)

#define PASS_RANDOM_ANGLES(MACRO, TYPE, ANGLE_TYPE, ...) \
  { \
    ksn::Angle<ANGLE_TYPE, TYPE> angles[3]; \
    for (size_t i = 0; i < 3; ++i) { \
      angles[i] = ksn::Angle<ANGLE_TYPE, TYPE>(std::rand() % 200 - 100); \
    } \
    MACRO(angles, TYPE, ANGLE_TYPE, __VA_ARGS__) \
  }

using ksn::literals::operator""_deg;
using ksn::literals::operator""_pi_rad;

// This one will test whether ksn::Euler could be declared without initial value
TEST(EulerTest, Empty)
{
#define EXPECT_COMPILED(TYPE, ANGLE_TYPE) { ksn::Euler<ANGLE_TYPE, TYPE> euler; }
#define ITERATE_TYPE(ANGLE_TYPE, ...) FOREACH_TYPE_DO(EXPECT_COMPILED, ANGLE_TYPE)

  FOREACH_ANGLE_TYPE_DO(ITERATE_TYPE)
}

// This one will test whether ksn::Euler could be declared with roll pitch yaw value
TEST(EulerTest, RpyConstructor)
{
#define EXPECT_CORRECT(ANGLES, TYPE, ANGLE_TYPE, ...) \
  { \
    ksn::Euler<ANGLE_TYPE, TYPE> euler(ANGLES[0], ANGLES[1], ANGLES[2]); \
    EXPECT_EQ(euler.roll, ANGLES[0]); \
    EXPECT_EQ(euler.pitch, ANGLES[1]); \
    ASSERT_EQ(euler.yaw, ANGLES[2]); \
  }
#define PASS_ANGLES(TYPE, ANGLE_TYPE) PASS_RANDOM_ANGLES(EXPECT_CORRECT, TYPE, ANGLE_TYPE)

#undef ITERATE_TYPE
#define ITERATE_TYPE(ANGLE_TYPE, ...) FOREACH_TYPE_DO(PASS_ANGLES, ANGLE_TYPE)

  FOREACH_ANGLE_TYPE_DO(ITERATE_TYPE)
}

// This one will test whether ksn::Euler could be assigned to other ksn::Euler
// with the same angle type but different value type
TEST(EulerTest, AssignmentConstructor)
{
#undef EXPECT_CORRECT
#define EXPECT_CORRECT(TYPE, ANGLE_TYPE, SOURCE) \
  { \
    ksn::Euler<ANGLE_TYPE, TYPE> a(SOURCE), b = SOURCE, c; \
    c = SOURCE; \
    EXPECT_EQ(a, SOURCE); \
    EXPECT_EQ(b, SOURCE); \
    ASSERT_EQ(c, SOURCE); \
  }

#undef ITERATE_TYPE
#define ITERATE_TYPE(ANGLES, SOURCE_TYPE, ANGLE_TYPE, ...) \
  { \
    auto source = ksn::Euler<ANGLE_TYPE, SOURCE_TYPE>(ANGLES[0], ANGLES[1], ANGLES[2]); \
    FOREACH_TYPE_DO(EXPECT_CORRECT, ANGLE_TYPE, source) \
  }

#undef PASS_ANGLES
#define PASS_ANGLES(SOURCE_TYPE, ANGLE_TYPE) \
  PASS_RANDOM_ANGLES(ITERATE_TYPE, SOURCE_TYPE, ANGLE_TYPE)

#define ITERATE_SOURCE_TYPE(ANGLE_TYPE, ...) FOREACH_TYPE_DO2(PASS_ANGLES, ANGLE_TYPE)

  FOREACH_ANGLE_TYPE_DO(ITERATE_SOURCE_TYPE)
}

TEST(EulerTest, ComparisonOperator)
{
  ksn::DegEuler<double> a(0.0_deg, 90.0_deg, 180.0_deg);

  auto b = a;

  ASSERT_TRUE(a == b);
  ASSERT_FALSE(a != b);

  a.roll = 1_pi_rad;

  ASSERT_FALSE(a == b);
  ASSERT_TRUE(a != b);
}

TEST(EulerTest, QuaternionConversion)
{
  ksn::DegEuler<double> euler(0.0_deg, 0.0_deg, 90.0_deg);

  auto quaternion = euler.to_quaternion();

  ASSERT_EQ(quaternion.to_rad_euler(), euler);
}
