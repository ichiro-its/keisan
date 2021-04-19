// Copyright (c) 2021 Ichiro ITS
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

TEST(WrapRadTest, OverflowTest) {
  ASSERT_DOUBLE_EQ(
    keisan::wrap_rad(keisan::pi * 6 + 1.5),
    1.5);

  ASSERT_DOUBLE_EQ(
    keisan::wrap_rad((-keisan::pi) * 6 - 1.5),
    -1.5);
}

TEST(WrapDegTest, OverflowTest) {
  ASSERT_DOUBLE_EQ(
    keisan::wrap_deg(180.0 * 6 + 100.0),
    100.0);

  ASSERT_DOUBLE_EQ(
    keisan::wrap_deg((-180.0) * 6 - 100.0),
    -100.0);
}

TEST(RadToDegTest, ConversionTest) {
  ASSERT_DOUBLE_EQ(
    keisan::rad_to_deg(keisan::pi * 0.2),
    180.0 * 0.2);

  ASSERT_DOUBLE_EQ(
    keisan::rad_to_deg(keisan::pi * 6.2),
    180.0 * 0.2);
}

TEST(DegToRadTest, ConversionTest) {
  ASSERT_DOUBLE_EQ(
    keisan::deg_to_rad(180.0 * 0.2),
    keisan::pi * 0.2);

  ASSERT_DOUBLE_EQ(
    keisan::deg_to_rad(180.0 * 6.2),
    keisan::pi * 0.2);
}

TEST(DeltaDegTest, OverflowTest) {
  ASSERT_DOUBLE_EQ(
    keisan::delta_deg(-30.0, 40.0),
    70.0);

  ASSERT_DOUBLE_EQ(
    keisan::delta_deg(30.0, -40.0),
    -70.0);

  ASSERT_DOUBLE_EQ(
    keisan::delta_deg(100.0, -150.0),
    110.0);

  ASSERT_DOUBLE_EQ(
    keisan::delta_deg(-100.0, 150.0),
    -110.0);
}

TEST(DeltaRadTest, OverflowTest)
{
  ASSERT_DOUBLE_EQ(
    keisan::delta_rad(keisan::pi * -0.1, keisan::pi * 0.3),
    keisan::pi * 0.4);

  ASSERT_DOUBLE_EQ(
    keisan::delta_rad(keisan::pi * 0.1, keisan::pi * -0.3),
    keisan::pi * -0.4);

  ASSERT_DOUBLE_EQ(
    keisan::delta_rad(keisan::pi * 0.6, keisan::pi * -0.7),
    keisan::pi * 0.7);

  ASSERT_DOUBLE_EQ(
    keisan::delta_rad(keisan::pi * -0.6, keisan::pi * 0.7),
    keisan::pi * -0.7);
}
