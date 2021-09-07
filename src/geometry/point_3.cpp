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
#include "keisan/geometry/point_3.hpp"

std::ostream & operator<<(std::ostream & out, const keisan::Point3 point)
{
  return out << "{" << point.x << "," << point.y << "," << point.z << "}";
}

namespace keisan
{

double distance_between(const Point3 & a, const Point3 & b)
{
  return a.distance_to(b);
}

double dot_product(const Point3 & a, const Point3 & b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Point3 cross_product(const Point3 & a, const Point3 & b)
{
  return Point3(
    a.y * b.z - a.z * b.y,
    a.z * b.x - a.x * b.z,
    a.x * b.y - a.y * b.x);
}

Point3::Point3()
{
}

Point3::Point3(double x, double y, double z)
: x(x),
  y(y),
  z(z)
{
}

Point3::Point3(const Vector<3> & vector)
: x(vector[0]),
  y(vector[1]),
  z(vector[2])
{
}

Point3::Point3(const Vector<4> & vector)
: x(vector[0] / vector[3]),
  y(vector[1] / vector[3]),
  z(vector[2] / vector[3])
{
}

Point3::Point3(const Point3 & point)
{
  *this = point;
}

Point3::operator Vector<3>() const
{
  return Vector<3>(x, y, z);
}

Point3::operator Vector<4>() const
{
  return Vector<4>(x, y, z, 1.0);
}

Point3 Point3::zero()
{
  return Point3(Vector<3>::zero());
}

Point3 & Point3::operator=(const Point3 & point)
{
  x = point.x;
  y = point.y;
  z = point.z;

  return *this;
}

bool Point3::operator==(const Point3 & point) const
{
  return (Vector<3>)(*this) == (Vector<3>)point;
}

bool Point3::operator!=(const Point3 & point) const
{
  return (Vector<3>)(*this) != (Vector<3>)point;
}

Point3 & Point3::operator+=(const Point3 & point)
{
  return *this = *this + point;
}

Point3 & Point3::operator-=(const Point3 & point)
{
  return *this = *this - point;
}

Point3 & Point3::operator+=(const double & value)
{
  return *this = *this + value;
}

Point3 & Point3::operator-=(const double & value)
{
  return *this = *this - value;
}

Point3 & Point3::operator*=(const double & value)
{
  return *this = *this * value;
}

Point3 & Point3::operator/=(const double & value)
{
  return *this = *this / value;
}

Point3 Point3::operator+(const Point3 & point) const
{
  return Point3((Vector<3>)(*this) + (Vector<3>)point);
}

Point3 Point3::operator-(const Point3 & point) const
{
  return Point3((Vector<3>)(*this) - (Vector<3>)point);
}

Point3 Point3::operator+(const double & value) const
{
  return Point3((Vector<3>)(*this) + value);
}

Point3 Point3::operator-(const double & value) const
{
  return Point3((Vector<3>)(*this) - value);
}

Point3 Point3::operator*(const double & value) const
{
  return Point3((Vector<3>)(*this) * value);
}

Point3 Point3::operator/(const double & value) const
{
  return Point3((Vector<3>)(*this) / value);
}

Point3 Point3::operator-() const
{
  return Point3(-(Vector<3>)(*this));
}

double Point3::magnitude() const
{
  return std::hypot(std::hypot(x, y), z);
}

Point3 Point3::normalize() const
{
  double mag = magnitude();

  return Point3(x / mag, y / mag, z / mag);
}

double Point3::distance_to(const Point3 & other) const
{
  return (other - *this).magnitude();
}

}  // namespace keisan
