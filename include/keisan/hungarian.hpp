// Copyright (c) 2025 ICHIRO ITS
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

#ifndef KEISAN__HUNGARIAN_HPP_
#define KEISAN__HUNGARIAN_HPP_

#include <array>

#include "keisan/matrix.hpp"

namespace keisan
{

template<size_t N>
class Hungarian
{
public:
  Hungarian();
  Matrix<N, N> solve(const Matrix<N, N> & matrix, int actual_size);

private:
  Matrix<N, N> matrix;
  Matrix<N, N> mask;
  Matrix<N + 1, 2> path;
  std::array<int, N> row_cover;
  std::array<int, N> col_cover;
  size_t size;
  int step;
  int actual_size;
  int path_row_0;
  int path_col_0;

  void clear_covers(std::array<int, N> & cover);
  void find_a_zero(int & row, int & col);
  bool star_in_row(int row);
  void find_star_in_row(int row, int & col);
  void find_star_in_col(int col, int & row);
  void find_prime_in_row(int row, int & col);
  void augment_path(int path_count);
  void erase_primes();
  void find_smallest(double & minval);

  void step_1();
  void step_2();
  void step_3();
  void step_4();
  void step_5();
  void step_6();
};

} // namespace keisan

#include "keisan/hungarian.impl.hpp"

#endif // KEISAN__HUNGARIAN_HPP_
