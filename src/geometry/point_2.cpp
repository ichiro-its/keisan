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

#include <cmath>

#include "keisan/angle.hpp"
#include "keisan/geometry/point_2.hpp"

keisan::Point2 operator*(const double & value, const keisan::Point2 & point)
{
  return point * value;
}

namespace keisan
{

Point2::Point2()
{
}

Point2::Point2(double x, double y)
: x(x),
  y(y)
{
}

Point2::Point2(const Vector<2> & vector)
: x(vector[0]),
  y(vector[1])
{
}

Point2::Point2(const Vector<3> & vector)
: x(vector[0] / vector[2]),
  y(vector[1] / vector[2])
{
}

Point2::Point2(const Point2 & point)
{
  *this = point;
}

Point2::operator Vector<2>() const
{
  return Vector<2>(x, y);
}

Point2::operator Vector<3>() const
{
  return Vector<3>(x, y, 1.0);
}

Point2 Point2::zero()
{
  return Point2(0.0, 0.0);
}

Point2 & Point2::operator=(const Point2 & point)
{
  x = point.x;
  y = point.y;

  return *this;
}

bool Point2::operator==(const Point2 & other) const
{
  return x == other.x && y == other.y;
}

bool Point2::operator!=(const Point2 & other) const
{
  return x != other.x || y != other.y;
}

Point2 & Point2::operator+=(const Point2 & other)
{
  x += other.x;
  y += other.y;

  return *this;
}

Point2 & Point2::operator-=(const Point2 & other)
{
  x -= other.x;
  y -= other.y;

  return *this;
}

Point2 & Point2::operator+=(const double & value)
{
  x += value;
  y += value;

  return *this;
}

Point2 & Point2::operator-=(const double & value)
{
  x -= value;
  y -= value;

  return *this;
}

Point2 & Point2::operator*=(const double & value)
{
  x *= value;
  y *= value;

  return *this;
}

Point2 & Point2::operator/=(const double & value)
{
  x /= value;
  y /= value;

  return *this;
}

Point2 Point2::operator+(const Point2 & other) const
{
  return Point2(x + other.x, y + other.y);
}

Point2 Point2::operator-(const Point2 & other) const
{
  return Point2(x - other.x, y - other.y);
}

Point2 Point2::operator+(const double & value) const
{
  return Point2(x + value, y + value);
}

Point2 Point2::operator-(const double & value) const
{
  return Point2(x - value, y - value);
}

Point2 Point2::operator*(const double & value) const
{
  return Point2(x * value, y * value);
}

Point2 Point2::operator/(const double & value) const
{
  return Point2(x / value, y / value);
}

Point2 Point2::operator-() const
{
  return Point2(-x, -y);
}

double Point2::magnitude() const
{
  return std::hypot(x, y);
}

Angle<double> Point2::direction() const
{
  return signed_arctan(y, x);
}

Point2 Point2::normalize() const
{
  double mag = magnitude();
  return Point2(x / mag, y / mag);
}

double Point2::dot(const Point2 & other) const
{
  return x * other.x + y * other.y;
}

double Point2::cross(const Point2 & other) const
{
  return x * other.y - y * other.x;
}

Point2 Point2::translate(const Point2 & translation) const
{
  return *this + translation;
}

Point2 Point2::scale(const Point2 & scaling) const
{
  return Point2(x * scaling.x, y * scaling.y);
}

Point2 Point2::scale(const double & scaling) const
{
  return scale({scaling, scaling});
}

Point2 Point2::rotate(const Angle<double> & rotation) const
{
  Point2 point;

  point.x = x * cos(rotation) - y * sin(rotation);
  point.y = x * sin(rotation) + y * cos(rotation);

  return point;
}

Point2 Point2::scale_from(const Point2 & scaling, const Point2 & anchor) const
{
  return translate(-anchor).scale(scaling).translate(anchor);
}

Point2 Point2::scale_from(const double & scaling, const Point2 & anchor) const
{
  return translate(-anchor).scale(scaling).translate(anchor);
}

Point2 Point2::rotate_from(const Angle<double> & rotation, const Point2 & anchor) const
{
  return translate(-anchor).rotate(rotation).translate(anchor);
}

}  // namespace keisan
