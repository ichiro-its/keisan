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

TEST(NumberTest, Sign)
{
  ASSERT_DOUBLE_EQ(keisan::sign(5.0), 1.0);
  ASSERT_DOUBLE_EQ(keisan::sign(-5.0), -1.0);
}

TEST(NumberTest, Scale)
{
  ASSERT_DOUBLE_EQ(keisan::scale(3.5, 6.5, 6.5 * 5.0), 3.5 * 5.0);
  ASSERT_DOUBLE_EQ(keisan::scale(-3.5, 6.5, 6.5 * 5.0), -3.5 * 5.0);
  ASSERT_DOUBLE_EQ(keisan::scale(3.5, 6.5, -6.5 * 5.0), -3.5 * 5.0);
  ASSERT_DOUBLE_EQ(keisan::scale(-3.5, 6.5, -6.5 * 5.0), 3.5 * 5.0);
}

TEST(NumberTest, Map) {
  ASSERT_DOUBLE_EQ(keisan::map(3.5, -6.5, 4.75, -6.5 * 5.0, 4.75 * 5.0), 3.5 * 5.0);
  ASSERT_DOUBLE_EQ(keisan::map(8.75, -6.5, 4.75, -6.5 * 5.0, 4.75 * 5.0), 8.75 * 5.0);
  ASSERT_DOUBLE_EQ(keisan::map(-9.3, -6.5, 4.75, -6.5 * 5.0, 4.75 * 5.0), -9.3 * 5.0);
}

TEST(NumberTest, Clamp)
{
  ASSERT_DOUBLE_EQ(keisan::clamp(5.0, 1.0, 10.0), 5.0);
  ASSERT_DOUBLE_EQ(keisan::clamp(0.0, 1.0, 10.0), 1.0);
  ASSERT_DOUBLE_EQ(keisan::clamp(15.0, 1.0, 10.0), 10.0);
}

TEST(NumberTest, WrapInside)
{
  ASSERT_DOUBLE_EQ(keisan::wrap(3.5, 1.2, 4.75), 3.5);
  ASSERT_DOUBLE_EQ(keisan::wrap(-2.3, -5.6, -0.9), -2.3);
  ASSERT_DOUBLE_EQ(keisan::wrap(0.56, -3.7, 7.89), 0.56);
}

TEST(NumberTest, WrapOutsideMax)
{
  ASSERT_DOUBLE_EQ(keisan::wrap(5.5, 1.2, 4.75), 1.2 + (5.5 - 4.75));
  ASSERT_DOUBLE_EQ(keisan::wrap(-0.1, -5.6, -0.9), -5.6 + (-0.1 + 0.9));
  ASSERT_DOUBLE_EQ(keisan::wrap(9.34, -3.7, 7.89), -3.7 + (9.34 - 7.89));
}

TEST(NumberTest, WrapOutsideMin) {
  ASSERT_DOUBLE_EQ(keisan::wrap(0.43, 1.2, 4.75), 4.75 - (1.2 - 0.43));
  ASSERT_DOUBLE_EQ(keisan::wrap(-8.9, -5.6, -0.9), -0.9 - (-5.6 + 8.9));
  ASSERT_DOUBLE_EQ(keisan::wrap(-6.5, -3.7, 7.89), 7.89 - (-3.7 + 6.5));
}
