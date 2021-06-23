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

TEST(QuaternionTest, Empty) {
  keisan::Quaternion quaternion;
}

TEST(QuaternionTest, AssignValue) {
  auto a = keisan::Quaternion(1.0, 0.5, 0.0, -0.5);

  ASSERT_DOUBLE_EQ(a.x, 1.0);
  ASSERT_DOUBLE_EQ(a.y, 0.5);
  ASSERT_DOUBLE_EQ(a.z, 0.0);
  ASSERT_DOUBLE_EQ(a.w, -0.5);
}

TEST(QuaternionTest, ComparisonOperator) {
  auto a = keisan::Quaternion(1.0, 0.5, 0.0, -0.5);
  auto b = a;

  ASSERT_TRUE(a == b);

  a.x = 0.0;
  ASSERT_TRUE(a != b);
}
