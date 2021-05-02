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
  auto point_a = keisan::Point2(2.0, 3.0);
  auto point_b = keisan::Point2(2.0, 2.0);
  keisan::Transform2 transform = keisan::Transform2();

  transform.set_translation(point_a);
  transform.set_rotation(180.0);
  transform.set_scale(point_b);

  auto result = transform * point;
  ASSERT_POINT2_EQ(result, -4.0, -7.0);
}
