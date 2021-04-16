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

#include <keisan/point_3.hpp>

namespace keisan
{

Point3::Point3()
{
  X = 0;
  Y = 0;
  Z = 0;
}

Point3::Point3(double x, double y, double z)
{
  X = x;
  Y = y;
  Z = z;
}

Point3::Point3(const Point3 & point)
{
  X = point.X;
  Y = point.Y;
  Z = point.Z;
}

Point3 & Point3::operator=(Point3 & point)
{
  X = point.X;
  Y = point.Y;
  Z = point.Z;
  return *this;
}

Point3 & Point3::operator+=(Point3 & point)
{
  X += point.X;
  Y += point.Y;
  Z += point.Z;
  return *this;
}

Point3 & Point3::operator-=(Point3 & point)
{
  X -= point.X;
  Y -= point.Y;
  Z -= point.Z;
  return *this;
}

Point3 & Point3::operator+=(double value)
{
  X += value;
  Y += value;
  Z += value;
  return *this;
}

Point3 & Point3::operator-=(double value)
{
  X -= value;
  Y -= value;
  Z -= value;
  return *this;
}

Point3 & Point3::operator*=(double value)
{
  X *= value;
  Y *= value;
  Z *= value;
  return *this;
}

Point3 & Point3::operator/=(double value)
{
  X /= value;
  Y /= value;
  Z /= value;
  return *this;
}

Point3 Point3::operator+(Point3 & point)
{
  return Point3(X + point.X, Y + point.Y, Z + point.Z);
}

Point3 Point3::operator-(Point3 & point)
{
  return Point3(X - point.X, Y - point.Y, Z - point.Z);
}

Point3 Point3::operator+(double value)
{
  return Point3(X + value, Y + value, Z + value);
}

Point3 Point3::operator-(double value)
{
  return Point3(X - value, Y - value, Z - value);
}

Point3 Point3::operator*(double value)
{
  return Point3(X * value, Y * value, Z * value);
}

Point3 Point3::operator/(double value)
{
  return Point3(X / value, Y / value, Z / value);
}

}  // namespace keisan
