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

#define ASSERT_POINT3_EQ(point, point_x, point_y, point_z) \
  { \
    auto temp_point = (point); \
    ASSERT_DOUBLE_EQ(temp_point.x, (point_x)); \
    ASSERT_DOUBLE_EQ(temp_point.y, (point_y)); \
    ASSERT_DOUBLE_EQ(temp_point.z, (point_z)); \
  }

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
  ASSERT_POINT3_EQ(point, 1.0, 3.0, 5.0);
}

TEST(Point3Test, EmptyValue)
{
  auto point = keisan::Point3::zero();
  ASSERT_POINT3_EQ(point, 0.0, 0.0, 0.0);
}

TEST(Point3Test, AssignedValue)
{
  auto point_a = keisan::Point3(5.0, 4.0, 3.0);
  auto point_b = keisan::Point3(point_a);

  ASSERT_POINT3_EQ(point_b, point_a.x, point_a.y, point_a.z);
}

TEST(Point3Test, SelfPointOperator)
{
  auto point_a = keisan::Point3(5.0, 4.0, 3.0);
  auto point_b = keisan::Point3(1.0, 3.0, 5.0);

  point_a = point_b;
  ASSERT_POINT3_EQ(point_a, 1.0, 3.0, 5.0);

  point_a += point_b;
  ASSERT_POINT3_EQ(point_a, 2.0, 6.0, 10.0);

  point_a -= point_b;
  ASSERT_POINT3_EQ(point_a, 1.0, 3.0, 5.0);
}

TEST(Point3Test, SelfValueOperator)
{
  auto point = keisan::Point3(1.0, 3.0, 5.0);

  point += 2.0;
  ASSERT_POINT3_EQ(point, 3.0, 5.0, 7.0);

  point -= 6.0;
  ASSERT_POINT3_EQ(point, -3.0, -1.0, 1.0);

  point *= 3.0;
  ASSERT_POINT3_EQ(point, -9.0, -3.0, 3.0);

  point /= 2.0;
  ASSERT_POINT3_EQ(point, -4.5, -1.5, 1.5);
}

TEST(Point3Test, PointOperator)
{
  auto point_a = keisan::Point3(1.0, 3.0, 5.0);
  auto point_b = keisan::Point3(2.0, 5.0, 10.0);

  ASSERT_POINT3_EQ(point_a + point_b, 3.0, 8.0, 15.0);
  ASSERT_POINT3_EQ(point_a - point_b, -1.0, -2.0, -5.0);
}

TEST(Point3Test, ValueOperator)
{
  auto point = keisan::Point3(1.0, 3.0, 5.0);

  ASSERT_POINT3_EQ(point + 5.0, 6.0, 8.0, 10.0);
  ASSERT_POINT3_EQ(point - 4.0, -3.0, -1.0, 1.0);
  ASSERT_POINT3_EQ(point * 3.0, 3.0, 9.0, 15.0);
  ASSERT_POINT3_EQ(point / 2.0, 0.5, 1.5, 2.5);
}

TEST(Point3Test, NegationOperator)
{
  auto point = keisan::Point3(1.0, 3.0, 5.0);
  ASSERT_POINT3_EQ(-point, -1.0, -3.0, -5.0);
}

TEST(Point3Test, DistanceBetween)
{
  auto point_a = keisan::Point3(1.0, 3.0, 5.0);
  auto point_b = keisan::Point3(1.0 + 3.0, 3.0, 5.0 + 4.0);

  ASSERT_DOUBLE_EQ(keisan::Point3::distance_between(point_a, point_b), 5.0);
}

TEST(Point3Test, Magnitude)
{
  auto point = keisan::Point3(3.0, 0.0, 4.0);
  ASSERT_DOUBLE_EQ(point.magnitude(), 5.0);
}

TEST(Point3Test, Normalize)
{
  auto point = keisan::Point3(3.0, 0.0, 4.0);
  ASSERT_POINT3_EQ(point.normalize(), 0.6, 0.0, 0.8);
}

TEST(Point3Test, Direction)
{
  auto point = keisan::Point3(3.0, 4.0, 0.0);
  ASSERT_DOUBLE_EQ(point.direction().degree(), 0.0);
}

TEST(Point3Test, AngleBetween)
{
  auto point_a = keisan::Point3(2.0, -1.0, 7.0);
  auto point_b = keisan::Point3(1.0, 2.0, 0.0);

  ASSERT_DOUBLE_EQ(keisan::Point3::angle_between(point_a, point_b).degree(), 90.0);
}

TEST(Point3Test, DotProduct)
{
  auto point_a = keisan::Point3(4.0, 3.0, 2.0);
  auto point_b = keisan::Point3(3.0, 4.0, 5.0);
  ASSERT_DOUBLE_EQ(keisan::Point3::dot_product(point_a, point_b), 34.0);
}

TEST(Point3Test, CrossProduct)
{
  auto point_a = keisan::Point3(3.0, 6.0, -3.0);
  auto point_b = keisan::Point3(0.0, 2.0, 4.0);
  ASSERT_DOUBLE_EQ(keisan::Point3::cross_product(point_a, point_b), sqrt(54.0) * sqrt(20.0));
}
