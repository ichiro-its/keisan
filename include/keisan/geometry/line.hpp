// Copyright (c) 2026 ICHIRO ITS
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

#ifndef KEISAN__GEOMETRY__LINE_HPP_
#define KEISAN__GEOMETRY__LINE_HPP_

#include "keisan/geometry/point_2.hpp"

namespace keisan
{

struct Line
{
  Line();
  Line(double a, double b, double c);

  static Line from_points(const Point2 & p1, const Point2 & p2);
  static Line from_point(const Point2 & point, const Angle<double> & angle);

  double distance(const Point2 & point) const;

  std::optional<double> slope() const;
  Angle<double> angle() const;

  std::optional<Point2> intersection(const Line & other) const;

  double a;
  double b;
  double c;
};

}  // namespace keisan

#endif  // KEISAN__GEOMETRY__LINE_HPP_