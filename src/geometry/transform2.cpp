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
#include <keisan/geometry/transform2.hpp>

namespace keisan
{

Transform2::Transform2()
: translation(0.0, 0.0),
  rotation(0.0),
  scale(1.0, 1.0)
{
}

Transform2::operator SquareMatrix<3>() const
{
  auto scale_matrix = SquareMatrix<3>::identity();
  scale_matrix[0][0] = scale.x;
  scale_matrix[1][1] = scale.y;

  auto rotation_matrix = SquareMatrix<3>::identity();
  rotation_matrix[0][0] = cos(rotation);
  rotation_matrix[0][1] = -sin(rotation);
  rotation_matrix[1][0] = sin(rotation);
  rotation_matrix[1][1] = cos(rotation);

  auto translation_matrix = SquareMatrix<3>::identity();
  translation_matrix[0][2] = translation.x;
  translation_matrix[1][2] = translation.y;

  // Transform matrix order is in scale, rotation, then translation
  return translation_matrix * rotation_matrix * scale_matrix;
}

Point2 Transform2::operator*(const Point2 & point) const
{
  return Point2((SquareMatrix<3>)(*this) * (Vector<3>)point);
}

void Transform2::set_translation(const Point2 & translation)
{
  this->translation = translation;
}

void Transform2::set_rotation(const Angle & rotation)
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

const Angle & Transform2::get_rotation() const
{
  return rotation;
}

const Point2 & Transform2::get_scale() const
{
  return scale;
}

}  // namespace keisan
