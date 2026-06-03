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

#include "keisan/geometry/line.hpp"

namespace keisan
{

Line::Line() {}

Line::Line(double a, double b, double c) : a(a), b(b), c(a) {}

Line Line::from_points(const Point2 & p1, const Point2 & p2)
{
  double a = p2.y - p1.y;
  double b = p1.x - p2.x;
  double c = -(a * p1.x + b * p1.y);
  return Line(a, b, c);
}

Line Line::from_point(const Point2 & point, const Angle<double> & angle)
{
  double a = -angle.sin();
  double b = angle.cos();
  double c = -(a * point.x + b * point.y);

  return Line(a, b, c);
}

double Line::distance(const Point2 & point) const
{
  double denominator = std::hypot(a, b);

  if (denominator < 1e-9) {
    throw std::runtime_error(
      "Invalid line equations: coefficients 'a' and 'b' cannot both be zero.");
  }

  return std::abs(a * point.x + b * point.y + c) / denominator;
}

std::optional<Point2> Line::intersection(const Line & other) const
{
  double determinant = a * other.b - other.a * b;
  if (std::abs(determinant) < 1e-9) {
    return std::nullopt;  // Lines are parallel or coincident
  }
  double x = (b * other.c - other.b * c) / determinant;
  double y = (other.a * c - a * other.c) / determinant;
  return Point2{x, y};
}

std::optional<double> Line::slope() const
{
  if (std::abs(b) < 1e-9) return std::nullopt;  // Line is vertical
  return -a / b;
}

Angle<double> Line::angle() const { return signed_arctan(a, -b); }

}  // namespace keisan