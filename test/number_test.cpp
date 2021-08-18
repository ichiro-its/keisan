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

TEST(NumberTest, SignIntegral)
{
  EXPECT_EQ(keisan::sign(0), 1) << "Sign result must be positive for zero";
  EXPECT_EQ(keisan::sign(5), 1) << "Sign result must be positive";
  EXPECT_EQ(keisan::sign(-5), -1) << "Sign result must be negative";
}

TEST(NumberTest, SignFloatingPoint)
{
  EXPECT_DOUBLE_EQ(keisan::sign(0.0), 1.0) << "Sign result must be positive for zero";
  EXPECT_DOUBLE_EQ(keisan::sign(5.0), 1.0) << "Sign result must be positive";
  EXPECT_DOUBLE_EQ(keisan::sign(-5.0), -1.0) << "Sign result must be negative";
}

TEST(NumberTest, SignAngle)
{
  EXPECT_DOUBLE_EQ(keisan::sign(0_deg), 1.0) << "Sign result must be positive for zero";
  EXPECT_DOUBLE_EQ(keisan::sign(90_deg), 1.0) << "Sign result must be positive";
  EXPECT_DOUBLE_EQ(keisan::sign(-900_deg), -1.0) << "Sign result must be negative";
}

TEST(NumberTest, ScaleIntegral)
{
  EXPECT_EQ(keisan::scale(5, 2, 3), 6) <<
    "5 / 2 = 2\n"
    "2 * 3 = 6";
}

TEST(NumberTest, ScaleFloatingPoint)
{
  EXPECT_DOUBLE_EQ(keisan::scale(3.3, 0.5, 1.5), 9.9) <<
    "3.3 / 0.5 = 6.6\n"
    "6.6 * 1.5 = 9.9";
}

TEST(NumberTest, MapIntegral)
{
  EXPECT_EQ(keisan::map(5, 2, 4, 0, 1), 1) <<
    "5 - 2 = 3\n"
    "4 - 2 = 2\n"
    "1 - 0 = 1\n"
    "scale(3, 2, 1) = 1\n"
    "1 + 0 = 1";

  EXPECT_EQ(keisan::map(0, -2, -4, 0, 1), -1) <<
    "0 - (-2) = 2\n"
    "-4 - (-2) = -2\n"
    "1 - 0 = 1\n"
    "scale(2, -2, 1) = -1\n"
    "-1 + 0 = -1";
}

TEST(NumberTest, MapFloatingPoint)
{
  EXPECT_DOUBLE_EQ(keisan::map(0.5, 0.2, 0.8, 1.0, 3.2), 2.1) <<
    "0.5 - 0.2 = 0.3\n"
    "0.8 - 0.2 = 0.6\n"
    "3.2 - 1.0 = 2.2\n"
    "scale(0.3, 0.6, 2.2) = 1.1\n"
    "1.1 + 1.0 = 2.1";

  EXPECT_DOUBLE_EQ(keisan::map(-0.1, 0.2, 0.8, -3.2, -1.0), -4.3) <<
    "-0.1 - 0.2 = -0.3\n"
    "0.8 - 0.2 = 0.6\n"
    "-1.0 - (-3.2) = 2.2\n"
    "scale(-0.3, 0.6, 2.2) = -1.1\n"
    "-1.1 + (-3.2) = -4.3";
}

TEST(NumberTest, ClampIntegral)
{
  EXPECT_EQ(keisan::clamp(5, 0, 10), 5) << "0 <= 5 <= 10";
  EXPECT_EQ(keisan::clamp(-5, 0, 10), 0) << "-5 < 0";
  EXPECT_EQ(keisan::clamp(15, 0, 10), 10) << "15 > 10";
}

TEST(NumberTest, ClampFloatingPoint)
{
  EXPECT_DOUBLE_EQ(keisan::clamp(0.5, -3.3, 2.2), 0.5) << "-3.3 <= 0.5 <= 2.2";
  EXPECT_DOUBLE_EQ(keisan::clamp(-5.5, -3.3, 2.2), -3.3) << "-5.5 < -3.3";
  EXPECT_DOUBLE_EQ(keisan::clamp(5.5, -3.3, 2.2), 2.2) << "5.5 > 2.2";
}

TEST(NumberTest, WrapIntegral)
{
  EXPECT_EQ(keisan::wrap(13, 10, 15), 13) <<
    "13 - 10 = 3\n"
    "15 - 10 = 5\n"
    "3 = 5 * 0 + 3\n"
    "3 + 10 = 13";

  EXPECT_EQ(keisan::wrap(31, 10, 15), 11) <<
    "31 - 10 = 21\n"
    "15 - 10 = 5\n"
    "21 = 5 * 4 + 1\n"
    "1 + 10 = 11";

  EXPECT_EQ(keisan::wrap(4, 10, 15), 14) <<
    "4 - 10 = -6\n"
    "15 - 10 = 5\n"
    "-6 = 5 * (-2) + 4\n"
    "4 + 10 = 14";
}

TEST(NumberTest, WrapFloatingPoint)
{
  EXPECT_DOUBLE_EQ(keisan::wrap(0.1, -0.1, 0.3), 0.1) <<
    "0.1 - (-0.1) = 0.2\n"
    "0.3 - (-0.1) = 0.4\n"
    "0.2 = 0.4 * 0 + 0.2\n"
    "0.2 + (-0.1) = 0.1";

  EXPECT_DOUBLE_EQ(keisan::wrap(1.8, -0.1, 0.3), 0.2) <<
    "1.8 - (-0.1) = 1.9\n"
    "0.3 - (-0.1) = 0.4\n"
    "1.9 = 0.4 * 4 + 0.3\n"
    "0.3 + (-0.1) = 0.2";

  EXPECT_DOUBLE_EQ(keisan::wrap(0.1, 1.1, 1.5), 1.3) <<
    "0.1 - (1.1) = -1.0\n"
    "1.5 - (1.1) = 0.4\n"
    "-1.0 = 0.4 * (-3) + 0.2\n"
    "0.2 + (1.1) = 1.3";
}
