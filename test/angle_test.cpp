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

TEST(WrapRadTest, OverflowTest) {
  ASSERT_DOUBLE_EQ(
    keisan::wrap_rad<double>(keisan::pi<double> * 6 + 1.5),
    1.5);

  ASSERT_DOUBLE_EQ(
    keisan::wrap_rad<double>((-keisan::pi<double>) * 6 - 1.5),
    -1.5);

  ASSERT_DOUBLE_EQ(
    keisan::wrap_rad<int>(keisan::pi<int> * 6 + 1),
    1);

  ASSERT_DOUBLE_EQ(
    keisan::wrap_rad<int>(keisan::pi<int> * 6 + -1),
    -1);
}

TEST(WrapDegTest, OverflowTest) {
  ASSERT_DOUBLE_EQ(
    keisan::wrap_deg<double>(180.0 * 6 + 100.0),
    100.0);

  ASSERT_DOUBLE_EQ(
    keisan::wrap_deg<double>((-180.0) * 6 - 100.0),
    -100.0);

  ASSERT_DOUBLE_EQ(
    keisan::wrap_deg<int>(180 * 6 + 50),
    50);

  ASSERT_DOUBLE_EQ(
    keisan::wrap_deg<int>(180 * 6 - 50),
    -50);
}

TEST(RadToDegTest, ConversionTest) {
  ASSERT_DOUBLE_EQ(
    keisan::rad_to_deg<double>(keisan::pi<double> * 0.2),
    180.0 * 0.2);

  ASSERT_DOUBLE_EQ(
    keisan::rad_to_deg<double>(keisan::pi<double> * 6.2),
    180.0 * 0.2);

  ASSERT_DOUBLE_EQ(
    keisan::rad_to_deg<int>(keisan::pi<int> * 2),
    180 * 0);

  ASSERT_DOUBLE_EQ(
    keisan::rad_to_deg<int>(keisan::pi<int> * -1),
    180 * -1);
}

TEST(DegToRadTest, ConversionTest) {
  ASSERT_DOUBLE_EQ(
    keisan::deg_to_rad<double>(180.0 * 0.2),
    keisan::pi<double> * 0.2);

  ASSERT_DOUBLE_EQ(
    keisan::deg_to_rad<double>(180.0 * 6.2),
    keisan::pi<double> * 0.2);

  ASSERT_DOUBLE_EQ(
    keisan::deg_to_rad<int>(180.0 * 2),
    keisan::pi<int> * 0);
}

TEST(DeltaDegTest, OverflowTest) {
  ASSERT_DOUBLE_EQ(
    keisan::delta_deg<double>(-30.0, 40.0),
    70.0);

  ASSERT_DOUBLE_EQ(
    keisan::delta_deg<double>(30.0, -40.0),
    -70.0);

  ASSERT_DOUBLE_EQ(
    keisan::delta_deg<double>(100.0, -150.0),
    110.0);

  ASSERT_DOUBLE_EQ(
    keisan::delta_deg<double>(-100.0, 150.0),
    -110.0);

  ASSERT_DOUBLE_EQ(
    keisan::delta_deg<int>(30, -40),
    -70);

  ASSERT_DOUBLE_EQ(
    keisan::delta_deg<int>(-30, 40),
    70);
}

TEST(DeltaRadTest, OverflowTest)
{
  ASSERT_DOUBLE_EQ(
    keisan::delta_rad<double>(keisan::pi<double> * -0.1, keisan::pi<double> * 0.3),
    keisan::pi<double> * 0.4);

  ASSERT_DOUBLE_EQ(
    keisan::delta_rad<double>(keisan::pi<double> * 0.1, keisan::pi<double> * -0.3),
    keisan::pi<double> * -0.4);

  ASSERT_DOUBLE_EQ(
    keisan::delta_rad<double>(keisan::pi<double> * 0.6, keisan::pi<double> * -0.7),
    keisan::pi<double> * 0.7);

  ASSERT_DOUBLE_EQ(
    keisan::delta_rad<double>(keisan::pi<double> * -0.6, keisan::pi<double> * 0.7),
    keisan::pi<double> * -0.7);

  ASSERT_DOUBLE_EQ(
    keisan::delta_rad<int>(keisan::pi<int> * 1, keisan::pi<int> * -2),
    -3);
}
