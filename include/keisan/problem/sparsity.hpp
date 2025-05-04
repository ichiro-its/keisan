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

#ifndef KEISAN__PROBLEM__SPARSITY_HPP_
#define KEISAN__PROBLEM__SPARSITY_HPP_

#include <Eigen/Dense>

#include <vector>

namespace keisan
{

class Sparsity
{
public:
  struct Interval
  {
    Interval();
    Interval(int start, int end);

    int start = 0;
    int end = 0;

    // True jika interval memiliki kolom i
    bool contains(int i);
  };

  void add_interval(int start, int end);

  std::vector<Interval> intervals;

  Sparsity operator+(const Sparsity & other) const;

  static Sparsity detect_columns_sparsity(const Eigen::MatrixXd M);
};

}  // namespace keisan

#endif  // KEISAN__PROBLEM__SPARSITY_HPP_
