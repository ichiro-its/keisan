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

#ifndef KEISAN__POINT_3_HPP_
#define KEISAN__POINT_3_HPP_

namespace keisan
{

struct Point3
{
  Point3();
  Point3(double x, double y, double z);
  Point3(const Point3 & point);

  Point3 & operator=(Point3 & point);
  Point3 & operator+=(Point3 & point);
  Point3 & operator-=(Point3 & point);

  Point3 & operator+=(double value);
  Point3 & operator-=(double value);
  Point3 & operator*=(double value);
  Point3 & operator/=(double value);

  Point3 operator+(Point3 & point);
  Point3 operator-(Point3 & point);

  Point3 operator+(double value);
  Point3 operator-(double value);
  Point3 operator*(double value);
  Point3 operator/(double value);

  static double distance_between(Point3 & point_a, Point3 & point_b);

  double magnitude();
  Point3 normalize();

  double direction();
  static double angle_between(Point3 point1, Point3 point2);

  double x;
  double y;
  double z;
};

}  // namespace keisan

#endif  // KEISAN__POINT_3_HPP_
