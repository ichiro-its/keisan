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
using ksn::literals::operator""_pi;

TEST(ConstantTest, PiValue)
{
  EXPECT_FLOAT_EQ(std::cos(ksn::pi<float>), -1.0f) << "cos(pi) = -1";
  EXPECT_DOUBLE_EQ(std::cos(ksn::pi<double>), -1.0) << "cos(pi) = -1";
}

TEST(ConstantTest, PiIntegerLiterals)
{
  EXPECT_DOUBLE_EQ(0_pi, 0.0);
  EXPECT_DOUBLE_EQ(1_pi, 1.0 * ksn::pi<double>);
  EXPECT_DOUBLE_EQ(-2_pi, -2.0 * ksn::pi<double>);
}

TEST(ConstantTest, PiFloatingPointLiterals)
{
  EXPECT_DOUBLE_EQ(0.0_pi, 0.0);
  EXPECT_DOUBLE_EQ(1.5_pi, 1.5 * ksn::pi<double>);
  EXPECT_DOUBLE_EQ(-0.25_pi, -0.25 * ksn::pi<double>);
}
