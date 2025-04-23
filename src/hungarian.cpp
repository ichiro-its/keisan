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

#include "keisan/hungarian.hpp"

namespace keisan
{

template<size_t N>
Hungarian<N>::Hungarian()
: matrix(Matrix<N, N>::zero()), mask(Matrix<N, N>::zero()),
  path(Matrix<N + 1, 2>::zero()), row_cover(N, 0), col_cover(N, 0),
  size(0), step(0), actual_size(0), path_row_0(0), path_col_0(0)
{
}

template<size_t N>
void Hungarian<N>::clear_covers(std::array<int, N> & cover)
{
  for (int i = 0; i < actual_size; ++i) {
    cover[i] = 0;
  }
}

template<size_t N>
void Hungarian<N>::find_a_zero(int & row, int & col)
{
  for (row = 0; row < actual_size; ++row) {
    for (col = 0; col < actual_size; ++col) {
      if (matrix[row][col] == 0 && row_cover[row] == 0 && col_cover[col] == 0) {
        return;
      }
    }
  }

  row = -1;
  col = -1;
}

template<size_t N>
bool Hungarian<N>::star_in_row(int row)
{
  for (int col = 0; col < actual_size; ++col) {
    if (mask[row][col] == 1) {
      return true;
    }
  }

  return false;
}

template<size_t N>
void Hungarian<N>::find_star_in_row(int row, int & col)
{
  for (col = 0; col < actual_size; ++col) {
    if (mask[row][col] == 1) {
      return;
    }
  }

  col = -1;
}

template<size_t N>
void Hungarian<N>::find_star_in_col(int col, int & row)
{
  for (row = 0; row < actual_size; ++row) {
    if (mask[row][col] == 1) {
      return;
    }
  }

  row = -1;
}

template<size_t N>
void Hungarian<N>::find_prime_in_row(int row, int & col)
{
  for (int j = 0; j < actual_size; ++j) {
    if (mask[row][j] == 2) {
      col = j;
      return;
    }
  }
}

template<size_t N>
void Hungarian<N>::augment_path(int path_count)
{
  for (int i = 0; i < path_count; ++i) {
    int row = path[i][0];
    int col = path[i][1];
    if (mask[row][col] == 1) {
      mask[row][col] = 0;
    } else {
      mask[row][col] = 1;
    }
  }
}

template<size_t N>
void Hungarian<N>::erase_primes()
{
  for (int row = 0; row < actual_size; ++row) {
    for (int col = 0; col < actual_size; ++col) {
      if (mask[row][col] == 2) {
        mask[row][col] = 0;
      }
    }
  }
}

template<size_t N>
void Hungarian<N>::find_smallest(double & minval)
{
  minval = std::numeric_limits<double>::max();
  for (int row = 0; row < actual_size; ++row) {
    for (int col = 0; col < actual_size; ++col) {
      if (row_cover[row] == 0 && col_cover[col] == 0) {
        if (matrix[row][col] < minval) {
          minval = matrix[row][col];
        }
      }
    }
  }
}

/* Step 1: Subtract row and column minima
 * For each row and column, find the lowest element and
 * subtract it from each element in that row or column. */
template<size_t N>
void Hungarian<N>::step_1()
{
  // Subtract row minima
  for (int row = 0; row < actual_size; ++row) {
    double lowest_value = matrix[row][0];
    for (int col = 1; col < actual_size; ++col) {
      if (matrix[row][col] < lowest_value) {
        lowest_value = matrix[row][col];
      }
    }

    for (int col = 0; col < actual_size; ++col) {
      matrix[row][col] -= lowest_value;
    }
  }

  // Subtract column minima
  for (int col = 0; col < actual_size; ++col) {
    double lowest_value = matrix[0][col];
    for (int row = 1; row < actual_size; ++row) {
      if (matrix[row][col] < lowest_value) {
        lowest_value = matrix[row][col];
      }
    }

    for (int row = 0; row < actual_size; ++row) {
      matrix[row][col] -= lowest_value;
    }
  }

  step = 2;
}

/* Step 2: Star the first zero
 * Find a zero in the matrix. If there is no starred zero in its row or column,
 * star it and cover its row and column. Repeat until there are no uncovered
 * zeros left. */
template<size_t N>
void Hungarian<N>::step_2()
{
  for (int row = 0; row < actual_size; ++row) {
    for (int col = 0; col < actual_size; ++col) {
      if (matrix[row][col] == 0 && row_cover[row] == 0 && col_cover[col] == 0) {
        mask[row][col] = 1;
        row_cover[row] = 1;
        col_cover[col] = 1;
      }
    }
  }

  clear_covers(row_cover);
  clear_covers(col_cover);

  step = 3;
}

/* Step 3: Cover columns with starred zeros
 * Cover every column that has a starred zero in it. If K columns are covered,
 * the starred zeros describe a complete matching, else go to step 4. */
template<size_t N>
void Hungarian<N>::step_3()
{
  for (int row = 0; row < actual_size; ++row) {
    for (int col = 0; col < actual_size; ++col) {
      if (mask[row][col] == 1) {
        col_cover[col] = 1;
      }
    }
  }

  int col_count = 0;
  for (int col = 0; col < actual_size; ++col) {
    if (col_cover[col] == 1) {
      col_count++;
    }
  }

  if (col_count >= actual_size) {
    step = 7;
  } else {
    step = 4;
  }
}

/* Step 4: Create a star zero
 * Find a non-covered zero and prime it. If there is no starred zero in its row,
 * go to step 5. Otherwise, cover the row and uncover the column of the starred
 * zero. Repeat until there are no uncovered zeros left. */
template<size_t N>
void Hungarian<N>::step_4()
{
  int row, col;
  while (true) {
    find_a_zero(row, col);
    if (row == -1) {
      step = 6;
      return;
    } else {
      mask[row][col] = 2;
      if (star_in_row(row)) {
        find_star_in_row(row, col);
        row_cover[row] = 1;
        col_cover[col] = 0;
      } else {
        path_row_0 = row;
        path_col_0 = col;
        step = 5;
        return;
      }
    }
  }
}

/* Step 5: Augment path
 * Construct a series of alternating primed and starred zeros. Unstar the starred
 * zeros and star the primed ones. Clear all primes and uncover all rows and
 * columns. Return to step 3. */
template<size_t N>
void Hungarian<N>::step_5()
{
  int row = -1;
  int col = -1;
  int path_count = 1;

  path[path_count - 1][0] = path_row_0;
  path[path_count - 1][1] = path_col_0;

  bool done = false;
  while (!done) {
    find_star_in_col(path[path_count - 1][1], row);
    if (row > -1) {
      path_count++;
      path[path_count - 1][0] = row;
      path[path_count - 1][1] = path[path_count - 2][1];
    } else {
      done = true;
    }

    if (!done) {
      find_prime_in_row(path[path_count - 1][0], col);
      path_count++;
      path[path_count - 1][0] = path[path_count - 2][0];
      path[path_count - 1][1] = col;
    }
  }

  augment_path(path_count);
  clear_covers(row_cover);
  clear_covers(col_cover);
  erase_primes();

  step = 3;
}

/* Step 6: Adjust the matrix
 * Find the smallest uncovered element in the matrix. Add it to every element
 * of each covered row, and subtract it from every element of each uncovered
 * column. */
template<size_t N>
void Hungarian<N>::step_6()
{
  double minval;
  find_smallest(minval);

  for (int row = 0; row < actual_size; ++row) {
    for (int col = 0; col < actual_size; ++col) {
      if (row_cover[row] == 1) {
        matrix[row][col] += minval;
      }
      if (col_cover[col] == 0) {
        matrix[row][col] -= minval;
      }
    }
  }

  step = 4;
}

template<size_t N>
Matrix<N, N> Hungarian<N>::solve(const Matrix<N, N> & matrix, int actual_size)
{
  this->matrix = matrix;
  this->actual_size = actual_size;
  step = 1;

  while (true) {
    switch (step) {
      case 1:
        step_1();
        break;
      case 2:
        step_2();
        break;
      case 3:
        step_3();
        break;
      case 4:
        step_4();
        break;
      case 5:
        step_5();
        break;
      case 6:
        step_6();
        break;
      case 7:
        return mask;
      default:
        throw std::runtime_error("Invalid step in Hungarian algorithm");
    }
  }
}

} // namespace keisan
