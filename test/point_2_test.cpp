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
#include <iostream>

keisan::Point2 point2;
keisan::Point2 point2_with_value(1.0, 3.0);
keisan::Point2 point2_assigned_value(keisan::Point2(5.0, 4.0));

TEST(Point2Test, EmptyValue)
{
  ASSERT_DOUBLE_EQ(point2.x, 0);
  ASSERT_DOUBLE_EQ(point2.y, 0);
}

TEST(Point2Test, InitialValue)
{
  ASSERT_DOUBLE_EQ(point2_with_value.x, 1.0);
  ASSERT_DOUBLE_EQ(point2_with_value.y, 3.0);
}

TEST(Point2Test, AssignedValue)
{
  ASSERT_DOUBLE_EQ(point2_assigned_value.x, 5.0);
  ASSERT_DOUBLE_EQ(point2_assigned_value.y, 4.0);
}

TEST(Point2Test, SelfPointOperator)
{
  point2 = point2_with_value;
  ASSERT_DOUBLE_EQ(point2.x, 1.0);
  ASSERT_DOUBLE_EQ(point2.y, 3.0);

  point2 += point2_with_value;
  ASSERT_DOUBLE_EQ(point2.x, 2.0);
  ASSERT_DOUBLE_EQ(point2.y, 6.0);

  point2 -= point2_with_value;
  ASSERT_DOUBLE_EQ(point2.x, 1.0);
  ASSERT_DOUBLE_EQ(point2.y, 3.0);
}

TEST(Point2Test, SelfValueOperator)
{
  point2_with_value += 2.0;
  ASSERT_DOUBLE_EQ(point2_with_value.x, 3.0);
  ASSERT_DOUBLE_EQ(point2_with_value.y, 5.0);

  point2_with_value -= 6.0;
  ASSERT_DOUBLE_EQ(point2_with_value.x, -3.0);
  ASSERT_DOUBLE_EQ(point2_with_value.y, -1.0);

  point2_with_value *= 3.0;
  ASSERT_DOUBLE_EQ(point2_with_value.x, -9.0);
  ASSERT_DOUBLE_EQ(point2_with_value.y, -3.0);

  point2_with_value /= 2.0;
  ASSERT_DOUBLE_EQ(point2_with_value.x, -4.5);
  ASSERT_DOUBLE_EQ(point2_with_value.y, -1.5);
}

TEST(Point2Test, PointOperator)
{
  auto result1 = point2_with_value + point2_assigned_value;
  ASSERT_DOUBLE_EQ(result1.x, 0.5);
  ASSERT_DOUBLE_EQ(result1.y, 2.5);

  auto result2 = point2_with_value - point2_assigned_value;
  ASSERT_DOUBLE_EQ(result2.x, -9.5);
  ASSERT_DOUBLE_EQ(result2.y, -5.5);
}

TEST(Point2Test, ValueOperator)
{
  auto result1 = point2_assigned_value + 6.0;
  ASSERT_DOUBLE_EQ(result1.x, 11.0);
  ASSERT_DOUBLE_EQ(result1.y, 10.0);

  auto result2 = point2_assigned_value - 4.5;
  ASSERT_DOUBLE_EQ(result2.x, 0.5);
  ASSERT_DOUBLE_EQ(result2.y, -0.5);

  auto result3 = point2_assigned_value * 2.0;
  ASSERT_DOUBLE_EQ(result3.x, 10.0);
  ASSERT_DOUBLE_EQ(result3.y, 8.0);

  auto result4 = point2_assigned_value / -2.0;
  ASSERT_DOUBLE_EQ(result4.x, -2.5);
  ASSERT_DOUBLE_EQ(result4.y, -2.0);
}

TEST(Point2Test, DistanceEquation)
{
  {
    keisan::Point2 a(5.0, 10.0);
    keisan::Point2 b(5.0 + 3.0, 10.0 + 4.0);
    ASSERT_DOUBLE_EQ(keisan::Point2::distance_between(a, b), 5.0);
  }

  {
    keisan::Point2 point(3.0, 4.0);
    ASSERT_DOUBLE_EQ(point.magnitude(), 5.0);
  }

  {
    keisan::Point2 point(3.0, 4.0);
    ASSERT_DOUBLE_EQ(point.normalize().x, 0.6);
    ASSERT_DOUBLE_EQ(point.normalize().y, 0.8);
  }
}
