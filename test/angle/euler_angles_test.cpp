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

using keisan::literals::operator""_pi;

TEST(EulerAnglesTest, Empty) {
  keisan::EulerAngles euler;
}

TEST(EulerAnglesTest, AssignValue) {
  keisan::EulerAngles a(
    keisan::make_degree(0.0), keisan::make_degree(90.0), keisan::make_degree(180.0));

  ASSERT_DOUBLE_EQ(a.roll.degree(), 0.0);
  ASSERT_DOUBLE_EQ(a.pitch.degree(), 90.0);
  ASSERT_DOUBLE_EQ(a.yaw.degree(), 180.0);

  keisan::EulerAngles b;
  b = a;

  ASSERT_EQ(a.roll, b.roll);
  ASSERT_EQ(a.pitch, b.pitch);
  ASSERT_EQ(a.yaw, b.yaw);
}

TEST(EulerAnglesTest, ComparisonOperator) {
  keisan::EulerAngles a(
    keisan::make_degree(0.0), keisan::make_degree(90.0), keisan::make_degree(180.0));

  keisan::EulerAngles b = a;

  ASSERT_TRUE(a == b);
  ASSERT_FALSE(a != b);

  a.roll = keisan::make_radian(1_pi);

  ASSERT_FALSE(a == b);
  ASSERT_TRUE(a != b);
}

TEST(EulerAnglesTest, QuaternionConversion) {
  keisan::EulerAngles euler(
    keisan::make_degree(0.0), keisan::make_degree(0.0), keisan::make_degree(90.0));

  auto quaternion = euler.quaternion();

  ASSERT_EQ(quaternion.euler(), euler);
}
