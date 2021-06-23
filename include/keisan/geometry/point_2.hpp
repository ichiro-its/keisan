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

#ifndef KEISAN__GEOMETRY__POINT_2_HPP_
#define KEISAN__GEOMETRY__POINT_2_HPP_

#include <ostream>

#include "../angle.hpp"
#include "../matrix.hpp"

namespace keisan
{

struct Point2;

std::ostream & operator<<(std::ostream & out, const Point2 & point);

double distance_between(const Point2 & a, const Point2 & b);
Angle angle_between(const Point2 & a, const Point2 & b);

double dot_product(const Point2 & a, const Point2 & b);
double cross_product(const Point2 & a, const Point2 & b);

struct Point2
{
  Point2();
  Point2(double x, double y);
  explicit Point2(const Vector<2> & vector);
  explicit Point2(const Vector<3> & vector);
  Point2(const Point2 & point);

  operator Vector<2>() const;
  operator Vector<3>() const;

  static Point2 zero();

  Point2 & operator=(const Point2 & point);

  bool operator==(const Point2 & point) const;
  bool operator!=(const Point2 & point) const;

  Point2 & operator+=(const Point2 & point);
  Point2 & operator-=(const Point2 & point);

  Point2 & operator+=(const double & value);
  Point2 & operator-=(const double & value);
  Point2 & operator*=(const double & value);
  Point2 & operator/=(const double & value);

  Point2 operator+(const Point2 & point) const;
  Point2 operator-(const Point2 & point) const;

  Point2 operator+(const double & value) const;
  Point2 operator-(const double & value) const;
  Point2 operator*(const double & value) const;
  Point2 operator/(const double & value) const;

  Point2 operator-() const;

  double magnitude() const;
  Angle direction() const;

  Point2 normalize() const;

  double distance_to(const Point2 & other) const;
  Angle direction_to(const Point2 & other) const;

  Point2 translate(const Point2 & translation) const;

  Point2 scale(const Point2 & scaling) const;
  Point2 scale(const double & scaling) const;

  Point2 rotate(const Angle & rotation) const;

  Point2 scale_from(const Point2 & scaling, const Point2 & anchor);
  Point2 scale_from(const double & scaling, const Point2 & anchor);

  Point2 rotate_from(const Angle & rotation, const Point2 & anchor);

  double x;
  double y;
};

}  // namespace keisan

#endif  // KEISAN__GEOMETRY__POINT_2_HPP_
