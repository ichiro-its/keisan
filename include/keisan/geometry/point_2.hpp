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

#include "../matrix.hpp"

namespace keisan
{

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

  static double distance_between(const Point2 & point_a, const Point2 & point_b);
  static double angle_between(const Point2 & point_a, const Point2 & point_b);
  static double dot_product(const Point2 & point_a, const Point2 & point_b);
  static double cross_product(const Point2 & point_a, const Point2 & point_b);

  double magnitude() const;
  double direction() const;

  Point2 normalize() const;

  double x;
  double y;
};

}  // namespace keisan

#endif  // KEISAN__GEOMETRY__POINT_2_HPP_