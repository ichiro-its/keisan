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
: translation(0.0, 0.0),
  rotation(0.0),
  scale(1.0, 1.0)
{
}

void Transform2::set_translation(const Point2 & translation)
{
  this->translation = translation;
}

void Transform2::set_rotation(const double & rotation)
{
  this->rotation = rotation;
}

void Transform2::set_scale(const Point2 & scale)
{
  this->scale = scale;
}

void Transform2::set_scale(const double & scale)
{
  set_scale({scale, scale});
}

const Point2 & Transform2::get_translation() const
{
  return translation;
}

const double & Transform2::get_rotation() const
{
  return rotation;
}

const Point2 & Transform2::get_scale() const
{
  return scale;
}

Point2 Transform2::operator*(const Point2 & point) const
{
  // Scale transform
  auto scaled_point = Point2(point.x * scale.x, point.y * scale.y);

  // Rotation transform
  auto angle = deg_to_rad(rotation);
  auto rotated_point = Point2(
    scaled_point.x * cos(angle) - scaled_point.y * sin(angle),
    scaled_point.x * sin(angle) + scaled_point.y * cos(angle));

  // Translation transform
  auto translated_point = rotated_point + translation;

  return translated_point;
}

}  // namespace keisan
