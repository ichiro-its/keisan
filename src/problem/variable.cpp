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

#include "keisan/problem/variable.hpp"

#include "keisan/problem/expression.hpp"

#include <Eigen/Dense>

namespace keisan
{

Expression Variable::expr(int start, int rows)
{
  start = (start == -1) ? 0 : start;
  rows = (rows == -1) ? 0 : rows;

  Expression e;
  e.A = Eigen::MatrixXd(rows, offset_start);
  e.A.setZero();
  e.b = Eigen::VectorXd(rows);
  e.b.setZero();

  for (int k = 0; k < rows; ++k) {
    e.A(k, offset_start + start + k) = 1;
  }

  return e;
}

int Variable::size() { return offset_end - offset_start; }

}  // namespace keisan
