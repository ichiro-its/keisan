// Copyright (c) 2021 Ichiro ITS
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

#include <keisan/point_3.hpp>

namespace keisan
{

Point3::Point3()
{
  x = 0;
  y = 0;
  z = 0;
}

Point3::Point3(double x, double y, double z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

Point3::Point3(const Point3 & point)
{
  x = point.x;
  y = point.y;
  z = point.z;
}

Point3 & Point3::operator=(Point3 & point)
{
  x = point.x;
  y = point.y;
  z = point.z;

  return *this;
}

Point3 & Point3::operator+=(Point3 & point)
{
  x += point.x;
  y += point.y;
  z += point.z;

  return *this;
}

Point3 & Point3::operator-=(Point3 & point)
{
  x -= point.x;
  y -= point.y;
  z -= point.z;

  return *this;
}

Point3 & Point3::operator+=(double value)
{
  x += value;
  y += value;
  z += value;

  return *this;
}

Point3 & Point3::operator-=(double value)
{
  x -= value;
  y -= value;
  z -= value;

  return *this;
}

Point3 & Point3::operator*=(double value)
{
  x *= value;
  y *= value;
  z *= value;

  return *this;
}

Point3 & Point3::operator/=(double value)
{
  x /= value;
  y /= value;
  z /= value;

  return *this;
}

Point3 Point3::operator+(Point3 & point)
{
  return Point3(x + point.x, y + point.y, z + point.z);
}

Point3 Point3::operator-(Point3 & point)
{
  return Point3(x - point.x, y - point.y, z - point.z);
}

Point3 Point3::operator+(double value)
{
  return Point3(x + value, y + value, z + value);
}

Point3 Point3::operator-(double value)
{
  return Point3(x - value, y - value, z - value);
}

Point3 Point3::operator*(double value)
{
  return Point3(x * value, y * value, z * value);
}

Point3 Point3::operator/(double value)
{
  return Point3(x / value, y / value, z / value);
}

double Point3::distance_between(Point3 & point_a, Point3 & point_b)
{
  double dx = point_a.x - point_b.x;
  double dy = point_a.y - point_b.y;
  double dz = point_a.z - point_b.z;

  return sqrt(dx * dx + dy * dy + dz * dz);
}

double Point3::angle_between(Point3 point1, Point3 point2)
{
  return acos(
    (point1.x * point2.x + point1.y * point2.y + point1.z * point2.z) /
    (point1.magnitude() * point2.magnitude())
  );
}

double Point3::magnitude()
{
  return sqrt(x * x + y * y + z * z);
}

double Point3::direction()
{
  double temp = sqrt(x * x + y * y);
  return atan(z / temp);
}

Point3 Point3::normalize()
{
  double mag = magnitude();

  return Point3(x / mag, y / mag, z / mag);
}

}  // namespace keisan
