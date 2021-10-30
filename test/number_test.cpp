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

using ksn::literals::operator""_deg;

TEST(NumberTest, SignIntegral)
{
  EXPECT_EQ(ksn::sign(0), 1) << "Sign result must be positive for zero";
  EXPECT_EQ(ksn::sign(5), 1) << "Sign result must be positive";
  EXPECT_EQ(ksn::sign(-5), -1) << "Sign result must be negative";
}

TEST(NumberTest, SignFloatingPoint)
{
  EXPECT_DOUBLE_EQ(ksn::sign(0.0), 1.0) << "Sign result must be positive for zero";
  EXPECT_DOUBLE_EQ(ksn::sign(5.0), 1.0) << "Sign result must be positive";
  EXPECT_DOUBLE_EQ(ksn::sign(-5.0), -1.0) << "Sign result must be negative";
}

TEST(NumberTest, SignAngle)
{
  EXPECT_DOUBLE_EQ(ksn::sign(ksn::make_degree(0)), 1.0) << "Sign result must be positive for zero";
  EXPECT_DOUBLE_EQ(ksn::sign(ksn::make_degree(90)), 1.0) << "Sign result must be positive";
  EXPECT_DOUBLE_EQ(ksn::sign(ksn::make_degree(-900)), -1.0) << "Sign result must be negative";
}

TEST(NumberTest, ScaleIntegral)
{
  EXPECT_EQ(ksn::scale(5, 2, 3), 6) <<
    "5 / 2 = 2\n"
    "2 * 3 = 6";
}

TEST(NumberTest, ScaleFloatingPoint)
{
  EXPECT_DOUBLE_EQ(ksn::scale(3.3, 0.5, 1.5), 9.9) <<
    "3.3 / 0.5 = 6.6\n"
    "6.6 * 1.5 = 9.9";
}

TEST(NumberTest, MapIntegral)
{
  EXPECT_EQ(ksn::map(5, 2, 4, 0, 1), 1) <<
    "5 - 2 = 3\n"
    "4 - 2 = 2\n"
    "1 - 0 = 1\n"
    "scale(3, 2, 1) = 1\n"
    "1 + 0 = 1";

  EXPECT_EQ(ksn::map(0, -2, -4, 0, 1), -1) <<
    "0 - (-2) = 2\n"
    "-4 - (-2) = -2\n"
    "1 - 0 = 1\n"
    "scale(2, -2, 1) = -1\n"
    "-1 + 0 = -1";
}

TEST(NumberTest, MapFloatingPoint)
{
  EXPECT_DOUBLE_EQ(ksn::map(0.5, 0.2, 0.8, 1.0, 3.2), 2.1) <<
    "0.5 - 0.2 = 0.3\n"
    "0.8 - 0.2 = 0.6\n"
    "3.2 - 1.0 = 2.2\n"
    "scale(0.3, 0.6, 2.2) = 1.1\n"
    "1.1 + 1.0 = 2.1";

  EXPECT_DOUBLE_EQ(ksn::map(-0.1, 0.2, 0.8, -3.2, -1.0), -4.3) <<
    "-0.1 - 0.2 = -0.3\n"
    "0.8 - 0.2 = 0.6\n"
    "-1.0 - (-3.2) = 2.2\n"
    "scale(-0.3, 0.6, 2.2) = -1.1\n"
    "-1.1 + (-3.2) = -4.3";
}

TEST(NumberTest, ClampIntegral)
{
  EXPECT_EQ(ksn::clamp(5, 0, 10), 5) << "0 <= 5 <= 10";
  EXPECT_EQ(ksn::clamp(-5, 0, 10), 0) << "-5 < 0";
  EXPECT_EQ(ksn::clamp(15, 0, 10), 10) << "15 > 10";
}

TEST(NumberTest, ClampFloatingPoint)
{
  EXPECT_DOUBLE_EQ(ksn::clamp(0.5, -3.3, 2.2), 0.5) << "-3.3 <= 0.5 <= 2.2";
  EXPECT_DOUBLE_EQ(ksn::clamp(-5.5, -3.3, 2.2), -3.3) << "-5.5 < -3.3";
  EXPECT_DOUBLE_EQ(ksn::clamp(5.5, -3.3, 2.2), 2.2) << "5.5 > 2.2";
}

TEST(NumberTest, ClampAngle)
{
  EXPECT_EQ(ksn::clamp(0_deg, -90_deg, 45_deg), 0_deg) << "-90 <= 0 <= 45";
  EXPECT_EQ(ksn::clamp(-180_deg, -90_deg, 45_deg), -90_deg) << "-180 < -90";
  EXPECT_EQ(ksn::clamp(90_deg, -90_deg, 45_deg), 45_deg) << "90 > 45";
}

TEST(NumberTest, WrapIntegral)
{
  EXPECT_EQ(ksn::wrap(13, 10, 15), 13) <<
    "13 - 10 = 3\n"
    "15 - 10 = 5\n"
    "3 = 5 * 0 + 3\n"
    "3 + 10 = 13";

  EXPECT_EQ(ksn::wrap(31, 10, 15), 11) <<
    "31 - 10 = 21\n"
    "15 - 10 = 5\n"
    "21 = 5 * 4 + 1\n"
    "1 + 10 = 11";

  EXPECT_EQ(ksn::wrap(4, 10, 15), 14) <<
    "4 - 10 = -6\n"
    "15 - 10 = 5\n"
    "-6 = 5 * (-2) + 4\n"
    "4 + 10 = 14";
}

TEST(NumberTest, WrapFloatingPoint)
{
  EXPECT_DOUBLE_EQ(ksn::wrap(0.1, -0.1, 0.3), 0.1) <<
    "0.1 - (-0.1) = 0.2\n"
    "0.3 - (-0.1) = 0.4\n"
    "0.2 = 0.4 * 0 + 0.2\n"
    "0.2 + (-0.1) = 0.1";

  EXPECT_DOUBLE_EQ(ksn::wrap(1.8, -0.1, 0.3), 0.2) <<
    "1.8 - (-0.1) = 1.9\n"
    "0.3 - (-0.1) = 0.4\n"
    "1.9 = 0.4 * 4 + 0.3\n"
    "0.3 + (-0.1) = 0.2";

  EXPECT_DOUBLE_EQ(ksn::wrap(0.1, 1.1, 1.5), 1.3) <<
    "0.1 - (1.1) = -1.0\n"
    "1.5 - (1.1) = 0.4\n"
    "-1.0 = 0.4 * (-3) + 0.2\n"
    "0.2 + (1.1) = 1.3";
}
