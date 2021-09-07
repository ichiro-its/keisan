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

std::ostream & operator<<(std::ostream & out, const keisan::Point2 & point)
{
  return out << "{" << point.x << "," << point.y << "}";
}

namespace keisan
{

double distance_between(const Point2 & a, const Point2 & b)
{
  return a.distance_to(b);
}

double dot_product(const Point2 & a, const Point2 & b)
{
  return a.x * b.x + a.y * b.y;
}

double cross_product(const Point2 & a, const Point2 & b)
{
  return a.x * b.y - a.y * b.x;
}

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
  return Point2(Vector<2>::zero());
}

Point2 & Point2::operator=(const Point2 & point)
{
  x = point.x;
  y = point.y;

  return *this;
}

bool Point2::operator==(const Point2 & point) const
{
  return (Vector<2>)(*this) == (Vector<2>)point;
}

bool Point2::operator!=(const Point2 & point) const
{
  return (Vector<2>)(*this) != (Vector<2>)point;
}

Point2 & Point2::operator+=(const Point2 & point)
{
  return *this = *this + point;
}

Point2 & Point2::operator-=(const Point2 & point)
{
  return *this = *this - point;
}

Point2 & Point2::operator+=(const double & value)
{
  return *this = *this + value;
}

Point2 & Point2::operator-=(const double & value)
{
  return *this = *this - value;
}

Point2 & Point2::operator*=(const double & value)
{
  return *this = *this * value;
}

Point2 & Point2::operator/=(const double & value)
{
  return *this = *this / value;
}

Point2 Point2::operator+(const Point2 & point) const
{
  return Point2((Vector<2>)(*this) + (Vector<2>)point);
}

Point2 Point2::operator-(const Point2 & point) const
{
  return Point2((Vector<2>)(*this) - (Vector<2>)point);
}

Point2 Point2::operator+(const double & value) const
{
  return Point2((Vector<2>)(*this) + value);
}

Point2 Point2::operator-(const double & value) const
{
  return Point2((Vector<2>)(*this) - value);
}

Point2 Point2::operator*(const double & value) const
{
  return Point2((Vector<2>)(*this) * value);
}

Point2 Point2::operator/(const double & value) const
{
  return Point2((Vector<2>)(*this) / value);
}

Point2 Point2::operator-() const
{
  return Point2(-(Vector<2>)(*this));
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

double Point2::distance_to(const Point2 & other) const
{
  auto delta = other - *this;
  return delta.magnitude();
}

Angle<double> Point2::direction_to(const Point2 & other) const
{
  auto delta = other - *this;
  return delta.direction();
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

Point2 Point2::scale_from(const Point2 & scaling, const Point2 & anchor)
{
  return translate(-anchor).scale(scaling).translate(anchor);
}

Point2 Point2::scale_from(const double & scaling, const Point2 & anchor)
{
  return translate(-anchor).scale(scaling).translate(anchor);
}

Point2 Point2::rotate_from(const Angle<double> & rotation, const Point2 & anchor)
{
  return translate(-anchor).rotate(rotation).translate(anchor);
}

}  // namespace keisan
