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
#include <keisan/geometry/point_2.hpp>

namespace keisan
{

Point2::Point2()
{
  x = 0;
  y = 0;
}

Point2::Point2(double x, double y)
{
  this->x = x;
  this->y = y;
}

Point2::Point2(const Point2 & point)
{
  x = point.x;
  y = point.y;
}

Point2::Point2(const Vector<3> & vector)
{
  x = vector[0] / vector[2];
  y = vector[1] / vector[2];
}

Point2 & Point2::operator=(const Point2 & point)
{
  x = point.x;
  y = point.y;

  return *this;
}

Point2 & Point2::operator+=(const Point2 & point)
{
  x += point.x;
  y += point.y;

  return *this;
}

Point2 & Point2::operator-=(const Point2 & point)
{
  x -= point.x;
  y -= point.y;

  return *this;
}

Point2 & Point2::operator+=(double value)
{
  x += value;
  y += value;

  return *this;
}

Point2 & Point2::operator-=(double value)
{
  x -= value;
  y -= value;

  return *this;
}

Point2 & Point2::operator*=(double value)
{
  x *= value;
  y *= value;

  return *this;
}

Point2 & Point2::operator/=(double value)
{
  x /= value;
  y /= value;

  return *this;
}

Point2 Point2::operator+(const Point2 & point) const
{
  return Point2(x + point.x, y + point.y);
}

Point2 Point2::operator-(const Point2 & point) const
{
  return Point2(x - point.x, y - point.y);
}

Point2 Point2::operator+(double value) const
{
  return Point2(x + value, y + value);
}

Point2 Point2::operator-(double value) const
{
  return Point2(x - value, y - value);
}

Point2 Point2::operator*(double value) const
{
  return Point2(x * value, y * value);
}

Point2 Point2::operator/(double value) const
{
  return Point2(x / value, y / value);
}

double Point2::distance_between(const Point2 & point_a, const Point2 & point_b)
{
  double dx = point_a.x - point_b.x;
  double dy = point_a.y - point_b.y;

  return sqrt(dx * dx + dy * dy);
}

double Point2::angle_between(const Point2 & point_a, const Point2 & point_b)
{
  double dot = dot_product(point_a, point_b);
  double mag = point_a.magnitude() * point_b.magnitude();

  return wrap_rad(acos(dot / mag));
}

double Point2::dot_product(const Point2 & point_a, const Point2 & point_b)
{
  return point_a.x * point_b.x + point_a.y * point_b.y;
}

double Point2::cross_product(const Point2 & point_a, const Point2 & point_b)
{
  return point_a.magnitude() * point_b.magnitude() * sin(angle_between(point_a, point_b));
}

double Point2::magnitude() const
{
  return sqrt(x * x + y * y);
}

double Point2::direction() const
{
  return wrap_rad(atan2(y, x));
}

Point2 Point2::normalize() const
{
  double mag = magnitude();

  return Point2(x / mag, y / mag);
}

}  // namespace keisan
