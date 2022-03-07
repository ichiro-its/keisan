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

#include "../comparison/point_2.hpp"

namespace ksn = keisan;

TEST(Point2Test, InitialValue)
{
  auto point = ksn::Point2(1.0, 3.0);

  EXPECT_DOUBLE_EQ(point.x, 1.0);
  EXPECT_DOUBLE_EQ(point.y, 3.0);
}

TEST(Point2Test, ZeroValue)
{
  auto point = ksn::Point2::zero();

  EXPECT_POINT2_EQ(point, ksn::Point2(0.0, 0.0));
}

TEST(Point2Test, ComparisonOperation)
{
  auto a = ksn::Point2(1.0, 3.0);
  auto b = a;

  EXPECT_TRUE(a == b);
  ASSERT_FALSE(a != b);

  a.x = 5.0;

  EXPECT_FALSE(a == b);
  ASSERT_TRUE(a != b);
}

TEST(Point2Test, SelfPointOperator)
{
  auto a = ksn::Point2(5.0, 4.0);
  auto b = ksn::Point2(1.0, 3.0);

  a = b;
  ASSERT_POINT2_EQ(a, ksn::Point2(1.0, 3.0));

  a += b;
  ASSERT_POINT2_EQ(a, ksn::Point2(2.0, 6.0));

  a -= b;
  ASSERT_POINT2_EQ(a, ksn::Point2(1.0, 3.0));
}

TEST(Point2Test, SelfValueOperator)
{
  auto point = ksn::Point2(1.0, 3.0);

  point += 2.0;
  ASSERT_POINT2_EQ(point, ksn::Point2(3.0, 5.0));

  point -= 6.0;
  ASSERT_POINT2_EQ(point, ksn::Point2(-3.0, -1.0));

  point *= 3.0;
  ASSERT_POINT2_EQ(point, ksn::Point2(-9.0, -3.0));

  point /= 2.0;
  ASSERT_POINT2_EQ(point, ksn::Point2(-4.5, -1.5));
}

TEST(Point2Test, PointOperator)
{
  auto a = ksn::Point2(1.0, 3.0);
  auto b = ksn::Point2(2.0, 5.0);

  EXPECT_POINT2_EQ(a + b, ksn::Point2(3.0, 8.0));
  EXPECT_POINT2_EQ(a - b, ksn::Point2(-1.0, -2.0));
}

TEST(Point2Test, ValueOperator)
{
  auto point = ksn::Point2(1.0, 3.0);

  EXPECT_POINT2_EQ(point + 5.0, ksn::Point2(6.0, 8.0));
  EXPECT_POINT2_EQ(point - 4.0, ksn::Point2(-3.0, -1.0));
  EXPECT_POINT2_EQ(point * 3.0, ksn::Point2(3.0, 9.0));
  EXPECT_POINT2_EQ(3.0 * point, ksn::Point2(3.0, 9.0));
  EXPECT_POINT2_EQ(point / 2.0, ksn::Point2(0.5, 1.5));
}

TEST(Point2Test, NegationOperator)
{
  auto point = ksn::Point2(1.0, 3.0);
  EXPECT_POINT2_EQ(-point, ksn::Point2(-1.0, -3.0));
}

TEST(Point2Test, Magnitude)
{
  auto point = ksn::Point2(3.0, 4.0);
  EXPECT_DOUBLE_EQ(point.magnitude(), 5.0);
}

TEST(Point2Test, Direction)
{
  auto point = ksn::Point2(0.0, 4.0);
  EXPECT_DOUBLE_EQ(point.direction().degree(), 90.0);

  point = ksn::Point2(-4.0, 0.0);
  EXPECT_DOUBLE_EQ(point.direction().degree(), 180.0);
}

TEST(Point2Test, Normalize)
{
  auto point = ksn::Point2(3.0, 4.0);
  EXPECT_POINT2_EQ(point.normalize(), ksn::Point2(0.6, 0.8));
}

TEST(Point2Test, DotProduct)
{
  auto a = ksn::Point2(4.0, 3.0);
  auto b = ksn::Point2(3.0, 4.0);

  EXPECT_DOUBLE_EQ(a.dot(b), 24.0);
}

TEST(Point2Test, CrossProduct)
{
  auto a = ksn::Point2(4.0, 3.0);
  auto b = ksn::Point2(-3.0, 4.0);

  EXPECT_DOUBLE_EQ(a.cross(b), 25.0);
}

TEST(Point2Test, Translation)
{
  auto point = ksn::Point2(4.0, 3.0);
  EXPECT_POINT2_EQ(point.translate({5.0, 10.0}), ksn::Point2(9.0, 13.0));
}

TEST(Point2Test, Scaling)
{
  auto point = ksn::Point2(4.0, 3.0);

  EXPECT_POINT2_EQ(point.scale({2.0, 3.0}), ksn::Point2(8.0, 9.0));
  EXPECT_POINT2_EQ(point.scale(2.0), ksn::Point2(8.0, 6.0));
  EXPECT_POINT2_EQ(point.scale_from({2.0, 3.0}, {1.0, -1.0}), ksn::Point2(7.0, 11.0));
  EXPECT_POINT2_EQ(point.scale_from(2.0, {1.0, -1.0}), ksn::Point2(7.0, 7.0));
}

TEST(Point2Test, Rotation)
{
  auto point = ksn::Point2(4.0, 3.0);

  EXPECT_POINT2_EQ(point.rotate(ksn::angle::from_degree(90.0)), ksn::Point2(-3.0, 4.0));
  EXPECT_POINT2_EQ(
    point.rotate_from(ksn::angle::from_degree(90.0), {1.0, -1.0}), ksn::Point2(-3.0, 2.0));
}
