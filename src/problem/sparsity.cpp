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

#include "keisan/problem/sparsity.hpp"

namespace keisan
{

Sparsity::Interval::Interval() {}

Sparsity::Interval::Interval(int start, int end) : start(start), end(end) {}

bool Sparsity::Interval::contains(int i) { return (start <= i) && (i <= end); }

void Sparsity::add_interval(int start, int end)
{
  std::vector<Interval> old_intervals = intervals;
  intervals.clear();

  bool inserted = false;
  for (Interval old_interval : old_intervals) {
    if (inserted) {
      intervals.push_back(old_interval);

    } else {
      if (end < old_interval.start) {
        intervals.push_back(Interval(start, end));
        intervals.push_back(old_interval);
        inserted = true;

      } else if (old_interval.contains(start) && old_interval.contains(end)) {
        intervals.push_back(old_interval);
        inserted = true;

      } else if (old_interval.contains(start)) {
        start = old_interval.start;

      } else if (old_interval.contains(end)) {
        intervals.push_back(Interval(start, old_interval.end));
        inserted = true;

      } else {
        if (start > old_interval.start) {
          intervals.push_back(old_interval);
        }
      }
    }
  }

  if (!inserted) {
    intervals.push_back(Interval(start, end));
  }
}

Sparsity Sparsity::operator+(const Sparsity & other) const
{
  Sparsity s;

  for (auto & interval : intervals) {
    s.add_interval(interval.start, interval.end);
  }
  for (auto & interval : other.intervals) {
    s.add_interval(interval.start, interval.end);
  }

  return s;
}

Sparsity Sparsity::detect_columns_sparsity(const Eigen::MatrixXd M)
{
  Sparsity sparsity;
  int last_nonzero_column = -1;

  for (int column = 0; column < M.cols(); ++column) {
    if (M.col(column).isZero(1e-12)) {
      if (last_nonzero_column != -1) {
        sparsity.add_interval(last_nonzero_column, column - 1);
        last_nonzero_column = -1;
      }
    } else if (last_nonzero_column == -1) {
      last_nonzero_column = column;
    }
  }

  if (last_nonzero_column != -1) {
    sparsity.add_interval(last_nonzero_column, M.cols() - 1);
  }

  return sparsity;
}

}  // namespace keisan
