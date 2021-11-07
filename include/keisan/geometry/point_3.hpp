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

#ifndef KEISAN__GEOMETRY__POINT_3_HPP_
#define KEISAN__GEOMETRY__POINT_3_HPP_

#include <ostream>

#include "keisan/matrix.hpp"

namespace keisan
{

struct Point3
{
  Point3();
  Point3(double x, double y, double z);
  explicit Point3(const Vector<3> & vector);
  explicit Point3(const Vector<4> & vector);
  Point3(const Point3 & point);

  operator Vector<3>() const;
  operator Vector<4>() const;

  static Point3 zero();

  Point3 & operator=(const Point3 & point);

  bool operator==(const Point3 & other) const;
  bool operator!=(const Point3 & other) const;

  Point3 & operator+=(const Point3 & other);
  Point3 & operator-=(const Point3 & other);

  Point3 & operator+=(const double & value);
  Point3 & operator-=(const double & value);
  Point3 & operator*=(const double & value);
  Point3 & operator/=(const double & value);

  Point3 operator+(const Point3 & other) const;
  Point3 operator-(const Point3 & other) const;

  Point3 operator+(const double & value) const;
  Point3 operator-(const double & value) const;
  Point3 operator*(const double & value) const;
  Point3 operator/(const double & value) const;

  Point3 operator-() const;

  double magnitude() const;

  Point3 normalize() const;

  double dot(const Point3 & other) const;
  Point3 cross(const Point3 & other) const;

  double x;
  double y;
  double z;
};

}  // namespace keisan

std::ostream & operator<<(std::ostream & out, const keisan::Point3 point);

keisan::Point3 operator*(const double & value, const keisan::Point3 & point);

#endif  // KEISAN__GEOMETRY__POINT_3_HPP_
