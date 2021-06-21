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

#include <vector>

TEST(AngleTest, Conversion) {
  std::vector<keisan::Angle> angles = {
    keisan::make_degree(270.0), keisan::make_radian(keisan::pi * 1.5)
  };

  for (const auto & angle : angles) {
    ASSERT_DOUBLE_EQ(angle.degree(), 270.0);
    ASSERT_DOUBLE_EQ(angle.radian(), keisan::pi * 1.5);
    ASSERT_DOUBLE_EQ(angle.normalized_degree(), -90.0);
    ASSERT_DOUBLE_EQ(angle.normalized_radian(), -keisan::pi * 0.5);
  }
}

TEST(AngleTest, SelfAngleOperator) {
  auto a = keisan::make_radian(keisan::pi);
  auto b = keisan::make_degree(270.0);

  a = b;
  ASSERT_DOUBLE_EQ(a.degree(), 270.0);

  a += b;
  ASSERT_DOUBLE_EQ(a.degree(), 540.0);

  a -= b;
  ASSERT_DOUBLE_EQ(a.degree(), 270.0);
}

TEST(AngleTest, SelfValueOperator) {
  auto angle = keisan::make_degree(270.0);

  angle *= 2.0;
  ASSERT_DOUBLE_EQ(angle.degree(), 540.0);

  angle /= 3.0;
  ASSERT_DOUBLE_EQ(angle.degree(), 180.0);
}

TEST(AngleTest, AngleOperator) {
  auto a = keisan::make_radian(keisan::pi);
  auto b = keisan::make_degree(270.0);

  ASSERT_DOUBLE_EQ((a + b).degree(), 450.0);
  ASSERT_DOUBLE_EQ((a - b).degree(), -90.0);
}

TEST(AngleTest, ValueOperator) {
  auto angle = keisan::make_degree(270.0);

  ASSERT_DOUBLE_EQ((angle * 2.0).degree(), 540.0);
  ASSERT_DOUBLE_EQ((angle / 3.0).degree(), 90.0);
}

TEST(AngleTest, Difference) {
  auto a = keisan::make_radian(-keisan::pi);
  auto b = keisan::make_degree(270.0);

  ASSERT_DOUBLE_EQ(a.difference_to(b).degree(), 90.0);
  ASSERT_DOUBLE_EQ(keisan::difference_between(b, a).radian(), -keisan::pi * 0.5);
}
