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

TEST(TrigonometryTest, SinCosTan) {
  ASSERT_DOUBLE_EQ(keisan::sin(keisan::make_degree(30.0)), 0.5);
  ASSERT_DOUBLE_EQ(keisan::cos(keisan::make_degree(60.0)), 0.5);
  ASSERT_DOUBLE_EQ(keisan::tan(keisan::make_degree(45.0)), 1.0);
}

TEST(TrigonometryTest, ArcSinCosTan) {
  ASSERT_DOUBLE_EQ(keisan::arcsin(0.5).degree(), 30.0);
  ASSERT_DOUBLE_EQ(keisan::arccos(0.5).degree(), 60.0);
  ASSERT_DOUBLE_EQ(keisan::arctan(1.0).degree(), 45.0);
  ASSERT_DOUBLE_EQ(keisan::signed_arctan(-1.0, 1.0).degree(), -45.0);
}
