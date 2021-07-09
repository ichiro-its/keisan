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

TEST(Trasform2Test, GeometryTransformation)
{
  auto point = keisan::Point2(3.0, 5.0);

  auto transform = keisan::Transform2();

  transform.set_scale({2.0, 3.0});
  ASSERT_POINT2_EQ(transform * point, 6.0, 15.0);

  transform.set_rotation(keisan::make_degree(90.0));
  ASSERT_POINT2_EQ(transform * point, -15.0, 6.0);

  transform.set_translation({2.0, 3.0});
  ASSERT_POINT2_EQ(transform * point, -13.0, 9.0);
}

TEST(Trasform2Test, Translation)
{
  auto point = keisan::Point2(3.0, 5.0);

  auto transform = keisan::Transform2();

  transform.set_translation({0.0, 0.0});
  ASSERT_POINT2_EQ(transform * point, 3.0, 5.0);

  transform.set_translation({2.0, 3.0});
  ASSERT_POINT2_EQ(transform * point, 5.0, 8.0);
}

TEST(Trasform2Test, Rotation)
{
  auto point = keisan::Point2(3.0, 5.0);

  auto transform = keisan::Transform2();

  transform.set_rotation(keisan::make_degree(0.0));
  ASSERT_POINT2_EQ(transform * point, 3.0, 5.0);

  transform.set_rotation(keisan::make_degree(180.0));
  ASSERT_POINT2_EQ(transform * point, -3.0, -5.0);
}

TEST(Trasform2Test, Scaling)
{
  auto point = keisan::Point2(3.0, 5.0);

  auto transform = keisan::Transform2();

  transform.set_scale({1.0, 1.0});
  ASSERT_POINT2_EQ(transform * point, 3.0, 5.0);

  transform.set_scale({2.0, 3.0});
  ASSERT_POINT2_EQ(transform * point, 6.0, 15.0);
}
