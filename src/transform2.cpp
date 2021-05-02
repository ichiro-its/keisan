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

#include <math.h>

#include <keisan/angle.hpp>
#include <keisan/transform2.hpp>

namespace keisan
{

Transform2::Transform2()
{
  translation = Point2(0, 0);
  rotation = 0;
  scale = Point2(0, 0);
}

void Transform2::set_translation(Point2 & point)
{
  translation.x = point.x;
  translation.y = point.y;
}

void Transform2::set_rotation(double value)
{
  rotation = value;
}

void Transform2::set_scale(Point2 & point)
{
  scale.x = point.x;
  scale.y = point.y;
}

Point2 Transform2::operator*(Point2 & point)
{
  point.x *= scale.x;
  point.y *= scale.y;
  point.x = point.x * cos(keisan::deg_to_rad(rotation)) -
    point.y * sin(keisan::deg_to_rad(rotation));
  point.y = point.y * cos(keisan::deg_to_rad(rotation)) -
    point.x * sin(keisan::deg_to_rad(rotation));
  point.x += translation.x;
  point.y += translation.y;

  return point;
}

}  // namespace keisan
