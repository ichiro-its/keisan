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

keisan::Point3 point3;
keisan::Point3 point3_with_value(1.0, 3.0, 5.0);
keisan::Point3 point3_assigned_value(keisan::Point3(5.0, -4.0, 3.0));

TEST(Point3Test, EmptyValue)
{
  ASSERT_DOUBLE_EQ(point3.x, 0);
  ASSERT_DOUBLE_EQ(point3.y, 0);
  ASSERT_DOUBLE_EQ(point3.z, 0);
}

TEST(Point3Test, InitialValue)
{
  ASSERT_DOUBLE_EQ(point3_with_value.x, 1.0);
  ASSERT_DOUBLE_EQ(point3_with_value.y, 3.0);
  ASSERT_DOUBLE_EQ(point3_with_value.z, 5.0);
}

TEST(Point3Test, AssignedValue)
{
  ASSERT_DOUBLE_EQ(point3_assigned_value.x, 5.0);
  ASSERT_DOUBLE_EQ(point3_assigned_value.y, -4.0);
  ASSERT_DOUBLE_EQ(point3_assigned_value.z, 3.0);
}

TEST(Point3Test, SelfPointOperator)
{
  point3 = point3_with_value;
  ASSERT_DOUBLE_EQ(point3.x, 1.0);
  ASSERT_DOUBLE_EQ(point3.y, 3.0);
  ASSERT_DOUBLE_EQ(point3.z, 5.0);

  point3 += point3_with_value;
  ASSERT_DOUBLE_EQ(point3.x, 2.0);
  ASSERT_DOUBLE_EQ(point3.y, 6.0);
  ASSERT_DOUBLE_EQ(point3.z, 10.0);

  point3 -= point3_with_value;
  ASSERT_DOUBLE_EQ(point3.x, 1.0);
  ASSERT_DOUBLE_EQ(point3.y, 3.0);
  ASSERT_DOUBLE_EQ(point3.z, 5.0);
}

TEST(Point3Test, SelfValueOperator)
{
  point3_with_value += 2.0;
  ASSERT_DOUBLE_EQ(point3_with_value.x, 3.0);
  ASSERT_DOUBLE_EQ(point3_with_value.y, 5.0);
  ASSERT_DOUBLE_EQ(point3_with_value.z, 7.0);

  point3_with_value -= 6.0;
  ASSERT_DOUBLE_EQ(point3_with_value.x, -3.0);
  ASSERT_DOUBLE_EQ(point3_with_value.y, -1.0);
  ASSERT_DOUBLE_EQ(point3_with_value.z, 1.0);

  point3_with_value *= 3.0;
  ASSERT_DOUBLE_EQ(point3_with_value.x, -9.0);
  ASSERT_DOUBLE_EQ(point3_with_value.y, -3.0);
  ASSERT_DOUBLE_EQ(point3_with_value.z, 3.0);

  point3_with_value /= 2.0;
  ASSERT_DOUBLE_EQ(point3_with_value.x, -4.5);
  ASSERT_DOUBLE_EQ(point3_with_value.y, -1.5);
  ASSERT_DOUBLE_EQ(point3_with_value.z, 1.5);
}

TEST(Point3Test, PointOperator)
{
  auto result1 = point3_with_value + point3_assigned_value;
  ASSERT_DOUBLE_EQ(result1.x, 0.5);
  ASSERT_DOUBLE_EQ(result1.y, -5.5);
  ASSERT_DOUBLE_EQ(result1.z, 4.5);

  auto result2 = point3_with_value - point3_assigned_value;
  ASSERT_DOUBLE_EQ(result2.x, -9.5);
  ASSERT_DOUBLE_EQ(result2.y, 2.5);
  ASSERT_DOUBLE_EQ(result2.z, -1.5);
}

TEST(Point3Test, ValueOperator)
{
  auto result1 = point3_assigned_value + 6.0;
  ASSERT_DOUBLE_EQ(result1.x, 11.0);
  ASSERT_DOUBLE_EQ(result1.y, 2.0);
  ASSERT_DOUBLE_EQ(result1.z, 9.0);

  auto result2 = point3_assigned_value - 4.5;
  ASSERT_DOUBLE_EQ(result2.x, 0.5);
  ASSERT_DOUBLE_EQ(result2.y, -8.5);
  ASSERT_DOUBLE_EQ(result2.z, -1.5);

  auto result3 = point3_assigned_value * 2.0;
  ASSERT_DOUBLE_EQ(result3.x, 10.0);
  ASSERT_DOUBLE_EQ(result3.y, -8.0);
  ASSERT_DOUBLE_EQ(result3.z, 6.0);

  auto result4 = point3_assigned_value / -2.0;
  ASSERT_DOUBLE_EQ(result4.x, -2.5);
  ASSERT_DOUBLE_EQ(result4.y, 2.0);
  ASSERT_DOUBLE_EQ(result4.z, -1.5);
}

TEST(Point3Test, DistanceEquation)
{
  auto result1 = keisan::Point3::distance_between(
    point3_with_value, point3_assigned_value);
  ASSERT_DOUBLE_EQ(result1, 9.9373034571758954);

  auto result2 = point3_assigned_value.magnitude();
  ASSERT_DOUBLE_EQ(result2, 7.0710678118654755);

  auto result3 = point3_assigned_value.normalize();
  ASSERT_DOUBLE_EQ(result3.x, 0.70710678118654746);
  ASSERT_DOUBLE_EQ(result3.y, -0.56568542494923801);
  ASSERT_DOUBLE_EQ(result3.z, 0.42426406871192851);
}
