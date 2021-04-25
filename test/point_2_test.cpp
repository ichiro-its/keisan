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
#include <iostream>

#define ASSERT_POINT2_EQ(point, point_x, point_y) \
  { \
    auto temp_point = (point); \
    ASSERT_DOUBLE_EQ(temp_point.x, (point_x)); \
    ASSERT_DOUBLE_EQ(temp_point.y, (point_y)); \
  }

TEST(Point2Test, EmptyValue)
{
  auto point = keisan::Point2();
  ASSERT_POINT2_EQ(point, 0.0, 0.0);
}

TEST(Point2Test, InitialValue)
{
  auto point = keisan::Point2(1.0, 3.0);
  ASSERT_POINT2_EQ(point, 1.0, 3.0);
}

TEST(Point2Test, AssignedValue)
{
  auto point_a = keisan::Point2(5.0, 4.0);
  auto point_b = keisan::Point2(point_a);

  ASSERT_POINT2_EQ(point_b, point_a.x, point_a.y);
}

TEST(Point2Test, SelfPointOperator)
{
  auto point_a = keisan::Point2(5.0, 4.0);
  auto point_b = keisan::Point2(1.0, 3.0);

  point_a = point_b;
  ASSERT_POINT2_EQ(point_a, 1.0, 3.0);

  point_a += point_b;
  ASSERT_POINT2_EQ(point_a, 2.0, 6.0);

  point_a -= point_b;
  ASSERT_POINT2_EQ(point_a, 1.0, 3.0);
}

TEST(Point2Test, SelfValueOperator)
{
  auto point = keisan::Point2(1.0, 3.0);

  point += 2.0;
  ASSERT_POINT2_EQ(point, 3.0, 5.0);

  point -= 6.0;
  ASSERT_POINT2_EQ(point, -3.0, -1.0);

  point *= 3.0;
  ASSERT_POINT2_EQ(point, -9.0, -3.0);

  point /= 2.0;
  ASSERT_POINT2_EQ(point, -4.5, -1.5);
}

TEST(Point2Test, PointOperator)
{
  auto point_a = keisan::Point2(1.0, 3.0);
  auto point_b = keisan::Point2(2.0, 5.0);

  ASSERT_POINT2_EQ(point_a + point_b, 3.0, 8.0);
  ASSERT_POINT2_EQ(point_a - point_b, -1.0, -2.0);
}

TEST(Point2Test, ValueOperator)
{
  auto point = keisan::Point2(1.0, 3.0);

  ASSERT_POINT2_EQ(point + 5.0, 6.0, 8.0);
  ASSERT_POINT2_EQ(point - 4.0, -3.0, -1.0);
  ASSERT_POINT2_EQ(point * 3.0, 3.0, 9.0);
  ASSERT_POINT2_EQ(point / 2.0, 0.5, 1.5);
}

TEST(Point2Test, DistanceBetween)
{
  auto point_a = keisan::Point2(5.0, 10.0);
  auto point_b = keisan::Point2(5.0 + 3.0, 10.0 + 4.0);

  ASSERT_DOUBLE_EQ(keisan::Point2::distance_between(point_a, point_b), 5.0);
}

TEST(Point2Test, Magnitude)
{
  auto point = keisan::Point2(3.0, 4.0);
  ASSERT_DOUBLE_EQ(point.magnitude(), 5.0);
}

TEST(Point2Test, Normalize)
{
  auto point = keisan::Point2(3.0, 4.0);
  ASSERT_POINT2_EQ(point.normalize(), 0.6, 0.8);
}

TEST(Point2Test, Direction)
{
  ASSERT_DOUBLE_EQ(keisan::Point2(0.0, 4.0).direction(), keisan::deg_to_rad(90.0));
  ASSERT_DOUBLE_EQ(keisan::Point2(-4.0, 0.0).direction(), keisan::deg_to_rad(180.0));
}

TEST(Point2Test, AngleBetween)
{
  auto point_a = keisan::Point2(4.0, 3.0);
  auto point_b = keisan::Point2(-3.0, 4.0);

  ASSERT_DOUBLE_EQ(keisan::Point2::angle_between(point_a, point_b), keisan::deg_to_rad(90.0));
}

TEST(Point2Test, DotProduct)
{
  auto point_a = keisan::Point2(4.0, 3.0);
  auto point_b = keisan::Point2(3.0, 4.0);
  ASSERT_DOUBLE_EQ(keisan::Point2::dot_product(point_a, point_b), 24.0);
}

TEST(Point2Test, CrossProduct)
{
  auto point_a = keisan::Point2(4.0, 3.0);
  auto point_b = keisan::Point2(-3.0, 4.0);
  ASSERT_DOUBLE_EQ(keisan::Point2::cross_product(point_a, point_b), 25.0);
}
