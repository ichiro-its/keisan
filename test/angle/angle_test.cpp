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

using namespace keisan::literals;  // NOLINT

TEST(AngleTest, Empty) {
  keisan::Angle<float> angle;
}

TEST(AngleTest, Conversion) {
  auto a = 270.0_deg;
  auto b = -0.5_pi_rad;

  ASSERT_DOUBLE_EQ(a.degree(), 270.0);
  ASSERT_DOUBLE_EQ(a.radian(), 1.5_pi);
  ASSERT_DOUBLE_EQ(b.degree(), -90.0);
  ASSERT_DOUBLE_EQ(b.radian(), -0.5_pi);
}

TEST(AngleTest, ComparisonOperator) {
  auto a = 90.0_deg;
  auto b = -180.0_deg;
  auto c = -1_pi_rad;

  ASSERT_TRUE(b == c && a != c);
  ASSERT_TRUE(a > b && a >= b && a >= a);
  ASSERT_TRUE(b < a && b <= a && b <= b);
}

TEST(AngleTest, SelfAngleOperator) {
  auto a = 1_pi_rad;
  auto b = 270.0_deg;

  a = b;
  ASSERT_DOUBLE_EQ(a.degree(), 270.0);

  a += b;
  ASSERT_DOUBLE_EQ(a.degree(), 540.0);

  a -= b;
  ASSERT_DOUBLE_EQ(a.degree(), 270.0);
}

TEST(AngleTest, SelfValueOperator) {
  auto angle = 270.0_deg;

  angle *= 2.0;
  ASSERT_DOUBLE_EQ(angle.degree(), 540.0);

  angle /= 3.0;
  ASSERT_DOUBLE_EQ(angle.degree(), 180.0);
}

TEST(AngleTest, AngleOperator) {
  auto a = 1_pi_rad;
  auto b = 270.0_deg;

  ASSERT_DOUBLE_EQ((a + b).degree(), 450.0);
  ASSERT_DOUBLE_EQ((a - b).degree(), -90.0);
}

TEST(AngleTest, ValueOperator) {
  auto angle = 270.0_deg;

  ASSERT_DOUBLE_EQ((angle * 2.0).degree(), 540.0);
  ASSERT_DOUBLE_EQ((2.0 * angle).degree(), 540.0);
  ASSERT_DOUBLE_EQ((angle / 3.0).degree(), 90.0);
}

TEST(AngleTest, NegationOperator) {
  auto angle = -90.0_deg;

  ASSERT_DOUBLE_EQ(angle.degree(), -90.0);
}

TEST(AngleTest, NormalizeTest) {
  auto a = 270.0_deg;
  auto b = -4.5_pi_rad;

  ASSERT_DOUBLE_EQ(a.normalize().degree(), -90.0);
  ASSERT_DOUBLE_EQ(b.normalize().degree(), -90.0);
}

TEST(AngleTest, Difference) {
  auto a = -1_pi_rad;
  auto b = 270.0_deg;

  ASSERT_DOUBLE_EQ(a.difference_to(b).degree(), 90.0);
  ASSERT_DOUBLE_EQ(keisan::difference_between(b, a).radian(), -0.5_pi);
}
