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

#include <sstream>
#include <cmath>

TEST(Point3Test, OutStream)
{
  auto point = keisan::Point3(1.0, 3.0, 5.0);

  std::stringstream ss;
  ss << point;

  ASSERT_STREQ(ss.str().c_str(), "{1,3,5}");
}

TEST(Point3Test, InitialValue)
{
  auto point = keisan::Point3(1.0, 3.0, 5.0);

  ASSERT_DOUBLE_EQ(point.x, 1.0);
  ASSERT_DOUBLE_EQ(point.y, 3.0);
  ASSERT_DOUBLE_EQ(point.z, 5.0);
}

TEST(Point3Test, EmptyValue)
{
  auto point = keisan::Point3::zero();

  ASSERT_DOUBLE_EQ(point.x, 0.0);
  ASSERT_DOUBLE_EQ(point.y, 0.0);
  ASSERT_DOUBLE_EQ(point.z, 0.0);
}

TEST(Point3Test, ComparisonOperation)
{
  auto a = keisan::Point3(5.0, 4.0, 3.0);
  auto b = a;

  ASSERT_TRUE(a == b);
  ASSERT_FALSE(a != b);

  a.x = 10.0;

  ASSERT_FALSE(a == b);
  ASSERT_TRUE(a != b);
}

TEST(Point3Test, SelfPointOperator)
{
  auto a = keisan::Point3(5.0, 4.0, 3.0);
  auto b = keisan::Point3(1.0, 3.0, 5.0);

  a = b;
  ASSERT_EQ(a, keisan::Point3(1.0, 3.0, 5.0));

  a += b;
  ASSERT_EQ(a, keisan::Point3(2.0, 6.0, 10.0));

  a -= b;
  ASSERT_EQ(a, keisan::Point3(1.0, 3.0, 5.0));
}

TEST(Point3Test, SelfValueOperator)
{
  auto point = keisan::Point3(1.0, 3.0, 5.0);

  point += 2.0;
  ASSERT_EQ(point, keisan::Point3(3.0, 5.0, 7.0));

  point -= 6.0;
  ASSERT_EQ(point, keisan::Point3(-3.0, -1.0, 1.0));

  point *= 3.0;
  ASSERT_EQ(point, keisan::Point3(-9.0, -3.0, 3.0));

  point /= 2.0;
  ASSERT_EQ(point, keisan::Point3(-4.5, -1.5, 1.5));
}

TEST(Point3Test, PointOperator)
{
  auto a = keisan::Point3(1.0, 3.0, 5.0);
  auto b = keisan::Point3(2.0, 5.0, 10.0);

  ASSERT_EQ(a + b, keisan::Point3(3.0, 8.0, 15.0));
  ASSERT_EQ(a - b, keisan::Point3(-1.0, -2.0, -5.0));
}

TEST(Point3Test, ValueOperator)
{
  auto point = keisan::Point3(1.0, 3.0, 5.0);

  ASSERT_EQ(point + 5.0, keisan::Point3(6.0, 8.0, 10.0));
  ASSERT_EQ(point - 4.0, keisan::Point3(-3.0, -1.0, 1.0));
  ASSERT_EQ(point * 3.0, keisan::Point3(3.0, 9.0, 15.0));
  ASSERT_EQ(point / 2.0, keisan::Point3(0.5, 1.5, 2.5));
}

TEST(Point3Test, NegationOperator)
{
  auto point = keisan::Point3(1.0, 3.0, 5.0);
  ASSERT_EQ(-point, keisan::Point3(-1.0, -3.0, -5.0));
}

TEST(Point3Test, Magnitude)
{
  auto point = keisan::Point3(3.0, 0.0, 4.0);
  ASSERT_DOUBLE_EQ(point.magnitude(), 5.0);
}

TEST(Point3Test, Normalize)
{
  auto point = keisan::Point3(3.0, 0.0, 4.0);
  ASSERT_EQ(point.normalize(), keisan::Point3(0.6, 0.0, 0.8));
}

TEST(Point3Test, DistanceBetween)
{
  auto a = keisan::Point3(1.0, 3.0, 5.0);
  auto b = keisan::Point3(1.0 + 3.0, 3.0, 5.0 + 4.0);

  ASSERT_DOUBLE_EQ(a.distance_to(b), 5.0);
  ASSERT_DOUBLE_EQ(keisan::distance_between(a, b), 5.0);
}

TEST(Point3Test, AngleBetween)
{
  auto a = keisan::Point3(2.0, -1.0, 7.0);
  auto b = keisan::Point3(1.0, 2.0, 0.0);

  ASSERT_DOUBLE_EQ(keisan::angle_between(a, b).degree(), 90.0);
}

TEST(Point3Test, DotProduct)
{
  auto a = keisan::Point3(4.0, 3.0, 2.0);
  auto b = keisan::Point3(3.0, 4.0, 5.0);

  ASSERT_DOUBLE_EQ(keisan::dot_product(a, b), 34.0);
}

TEST(Point3Test, CrossProduct)
{
  auto a = keisan::Point3(3.0, 6.0, -3.0);
  auto b = keisan::Point3(0.0, 2.0, 4.0);

  ASSERT_DOUBLE_EQ(keisan::cross_product(a, b), sqrt(54.0) * sqrt(20.0));
}
