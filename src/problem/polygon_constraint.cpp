// Copyright (c) 2025 Rhoban
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

#include "keisan/problem/polygon_constraint.hpp"
#include <Eigen/src/Core/Matrix.h>

#include "keisan/problem/constraint.hpp"
#include "keisan/problem/expression.hpp"

#include <Eigen/Dense>

#include <cmath>
#include <stdexcept>

namespace keisan
{

Constraint PolygonConstraint::in_polygon(
  const Expression & expression_xy, std::vector<Eigen::Vector2d> polygon, double margin)
{
  if (expression_xy.rows() != 2) {
    throw std::runtime_error("Polygon constraint should be called with 2 rows expressions");
  }

  Expression values;
  values.A.resize(polygon.size(), expression_xy.cols());
  values.b.resize(polygon.size());

  for (size_t i = 0; i < polygon.size(); ++i) {
    int j = (i + 1) % polygon.size();

    const Eigen::Vector2d & A = polygon[i];
    const Eigen::Vector2d & B = polygon[j];

    // Menghitung vektor yang dinormalisasikan yang mengarah ke dalam polygon
    Eigen::Vector2d n;
    n << (B - A).y(), (A - B).x();
    n.normalize();

    /*
    * Jarak ke batas polygon berupa rumus:
    * n.T * (P - A) >= margin
    */
    Expression result = (n.transpose() * (expression_xy - A)) - margin;
    values.A.block(i, 0, 1, expression_xy.cols()) = result.A;
    values.b(i) = result.b(0);
  }

  return values >= 0;
}

}  // namespace keisan
