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
#include <keisan/matrix/square_matrix.hpp>
#include <keisan/matrix/vector.hpp>
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
  // Set matrix
  auto mat_point = Vector<3>(point.x, point.y, 1.0);

  auto mat_scale = SquareMatrix<3>::identity();
  mat_scale[0][0] = scale.x;
  mat_scale[1][1] = scale.y;

  auto mat_rotation = SquareMatrix<3>::identity();
  auto angle = deg_to_rad(rotation);
  mat_rotation[0][0] = cos(angle);
  mat_rotation[0][1] = -1 * sin(angle);
  mat_rotation[1][0] = sin(angle);
  mat_rotation[1][1] = cos(angle);

  auto mat_translation = SquareMatrix<3>::identity();
  mat_translation[0][2] = translation.x;
  mat_translation[1][2] = translation.y;

  // Multiplication Matrix
  // The order is scale, rotation, translation
  auto mat_temp = mat_translation * mat_rotation * mat_scale;
  auto mat_result = mat_temp * mat_point;

  auto result_point = Point2(mat_result);

  return result_point;
}

}  // namespace keisan
