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

#ifndef KEISAN__MATRIX__MATRIX_IMPL_HPP_
#define KEISAN__MATRIX__MATRIX_IMPL_HPP_

#include <algorithm>
#include <ostream>
#include <cmath>

#include "gtest/gtest.h"
#include "keisan/matrix/matrix.hpp"

template <size_t M, size_t N>
std::ostream & operator<<(std::ostream & out, const keisan::Matrix<M, N> & matrix)
{
  out << "[";
  for (size_t i = 0; i < M; ++i) {
    if (i > 0) {
      out << ",";
    }

    out << "[";
    for (size_t j = 0; j < N; ++j) {
      if (j > 0) {
        out << ",";
      }

      out << matrix[i][j];
    }

    out << "]";
  }

  out << "]";

  return out;
}

template <size_t M, size_t N>
inline keisan::Matrix<M, N> operator*(const double & value, const keisan::Matrix<M, N> & matrix)
{
  return matrix * value;
}

namespace keisan
{

template <size_t M, size_t N>
Matrix<M, N>::Matrix()
{
}

template <size_t M, size_t N>
template <typename... Types>
Matrix<M, N>::Matrix(const double & value, Types... the_rest) : data{value, the_rest...}
{
}

template <size_t M, size_t N>
Matrix<M, N>::Matrix(const Matrix<M, N> & matrix)
{
  *this = matrix;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::zero()
{
  Matrix<M, N> matrix;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix[i][j] = 0.0;
    }
  }

  return matrix;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::identity()
{
  static_assert(
    M == N,
    "The dimensions of matrix are not matched. "
    "There is no identity matrix for non-square matrix!");

  Matrix<N, N> matrix;
  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix[i][j] = (i == j) ? 1.0 : 0.0;
    }
  }

  return matrix;
}

template <size_t M, size_t N>
double Matrix<M, N>::norm() const
{
  double norm = 0.0;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      norm += std::pow((*this)[i][j], 2);
    }
  }

  return std::sqrt(norm);
}

template<size_t M, size_t N>
void Matrix<M, N>::set_row(size_t pos, const Vector<M> & vector)
{
  std::copy(vector.begin(), vector.end(), (*this)[pos]);
}

template<size_t M, size_t N>
Vector<M> Matrix<M, N>::get_row(size_t pos) const
{
  Vector<M> vector;
  std::copy((*this)[pos], (*this)[pos] + M, vector.begin());
  return vector;
}

template<size_t M, size_t N>
void Matrix<M, N>::set_column(size_t pos, const Vector<N> & vector)
{
  for (size_t i = 0; i < N; ++i) {
    (*this)[i][pos] = vector[i];
  }
}

template<size_t M, size_t N>
Vector<N> Matrix<M, N>::get_column(size_t pos) const
{
  Vector<N> vector;
  for (size_t i = 0; i < N; ++i) {
    vector[i] = (*this)[i][pos];
  }

  return vector;
}

template<size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::exp(double tau, size_t terms)
{
  static_assert(
    M == N,
    "The dimensions of matrix are not matched. "
    "There is no exponential matrix for non-square matrix!");

  auto exponential = identity();
  auto term = identity();

  for (size_t k = 1; k <= terms; ++k) {
    term = term * (*this);

    for (size_t i = 0; i < M; ++i) {
      for (size_t j = 0; j < N; ++j) {
        exponential[i][j] += term[i][j] * std::pow(tau, k) / tgamma(k + 1);
      }
    }
  }

  return exponential;
}

template <size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator=(const Matrix<M, N> & matrix)
{
  std::copy(matrix.data, matrix.data + M * N, data);
  return *this;
}

template <size_t M, size_t N>
bool Matrix<M, N>::operator==(const Matrix<M, N> & matrix) const
{
  using testing::internal::FloatingPoint;
  for (size_t i = 0; i < M * N; ++i) {
    if (!FloatingPoint<double>(data[i]).AlmostEquals(FloatingPoint<double>(matrix.data[i]))) {
      return false;
    }
  }

  return true;
}

template <size_t M, size_t N>
bool Matrix<M, N>::operator!=(const Matrix<M, N> & matrix) const
{
  return !(*this == matrix);
}

template <size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator+=(const Matrix<M, N> & matrix)
{
  for (size_t i = 0; i < M * N; ++i) {
    data[i] += matrix.data[i];
  }

  return *this;
}

template <size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator-=(const Matrix<M, N> & matrix)
{
  for (size_t i = 0; i < M * N; ++i) {
    data[i] -= matrix.data[i];
  }

  return *this;
}

template <size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator+=(const double & value)
{
  for (size_t i = 0; i < M * N; ++i) {
    data[i] += value;
  }

  return *this;
}

template <size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator-=(const double & value)
{
  for (size_t i = 0; i < M * N; ++i) {
    data[i] -= value;
  }

  return *this;
}

template <size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator*=(const double & value)
{
  for (size_t i = 0; i < M * N; ++i) {
    data[i] *= value;
  }

  return *this;
}

template <size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator/=(const double & value)
{
  for (size_t i = 0; i < M * N; ++i) {
    data[i] /= value;
  }

  return *this;
}

template <size_t M, size_t N>
template <size_t O>
Matrix<M, O> Matrix<M, N>::operator*(const Matrix<N, O> & matrix)
{
  Matrix<M, O> new_matrix;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < O; ++j) {
      new_matrix[i][j] = 0.0;
      for (size_t k = 0; k < N; ++k) {
        new_matrix[i][j] += (*this)[i][k] * matrix[k][j];
      }
    }
  }

  return new_matrix;
}

template <size_t M, size_t N>
Vector<M> Matrix<M, N>::operator*(const Vector<N> & vector)
{
  Vector<M> new_vector;
  for (size_t i = 0; i < M; ++i) {
    new_vector[i] = 0.0;
    for (size_t j = 0; j < N; ++j) {
      new_vector[i] += (*this)[i][j] * vector[j];
    }
  }

  return new_vector;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator+(const Matrix<M, N> & matrix) const
{
  auto new_matrix = *this;
  new_matrix += matrix;

  return new_matrix;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator-(const Matrix<M, N> & matrix) const
{
  auto new_matrix = *this;
  new_matrix -= matrix;

  return new_matrix;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator+(const double & value) const
{
  auto new_matrix = *this;
  new_matrix += value;

  return new_matrix;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator-(const double & value) const
{
  auto new_matrix = *this;
  new_matrix -= value;

  return new_matrix;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator*(const double & value) const
{
  auto new_matrix = *this;
  new_matrix *= value;

  return new_matrix;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator/(const double & value) const
{
  auto new_matrix = *this;
  new_matrix /= value;

  return new_matrix;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator-() const
{
  Matrix<M, N> matrix;
  for (size_t i = 0; i < M * N; ++i) {
    matrix.data[i] = -data[i];
  }

  return matrix;
}

template <size_t M, size_t N>
double * Matrix<M, N>::operator[](size_t pos)
{
  return data + (pos * N);
}

template <size_t M, size_t N>
const double * Matrix<M, N>::operator[](size_t pos) const
{
  return data + (pos * N);
}

template <size_t M, size_t N>
bool Matrix<M, N>::inverse()
{
  static_assert(
    M == N,
    "The dimensions of matrix are not matched. "
    "There is no inverse matrix for non-square matrix!");

  switch (N) {
    case 2:
      return inverse2();
    case 3:
      return inverse3();
    case 4:
      return inverse4();
    default:
      Matrix<N, N> inverse = identity();
      double tolerance = 1e-9;

      for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
          (*this)[i][j + N] = inverse[i][j];
        }
      }

      // Forward elimination
      for (size_t k = 0; k < N; ++k) {
        size_t max_row = k;
        for (size_t i = k + 1; i < N; ++i) {
          if (std::abs((*this)[i][k]) > std::abs((*this)[max_row][k])) {
            max_row = i;
          }
        }

        if (max_row != k) {
          for (size_t j = 0; j < 2 * N; ++j) {
            std::swap((*this)[k][j], (*this)[max_row][j]);
          }
        }

        if (std::abs((*this)[k][k]) < tolerance) {
          return false;
        }

        double pivot = (*this)[k][k];
        for (size_t j = 0; j < 2 * N; ++j) {
          (*this)[k][j] /= pivot;
        }

        for (size_t i = k + 1; i < N; ++i) {
          double factor = (*this)[i][k];
          for (size_t j = 0; j < 2 * N; ++j) {
            (*this)[i][j] -= factor * (*this)[k][j];
          }
        }
      }

      // Backward elimination
      for (size_t k = N - 1; k > 0; --k) {
        for (size_t i = 0; i < k; ++i) {
          double factor = (*this)[i][k];
          for (size_t j = 0; j < 2 * N; ++j) {
            (*this)[i][j] -= factor * (*this)[k][j];
          }
        }
      }

      for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
          inverse[i][j] = (*this)[i][j + N];
        }
      }

      *this = inverse;

      return true;
  }

}

template<size_t M, size_t N>
bool Matrix<M, N>::inverse4()
{
  auto inverse = Matrix<M, N>::zero();
  auto source = *this;

  inverse[0][0] =
    source[1][1] * source[2][2] * source[3][3] - source[1][1] * source[2][3] * source[3][2] -
    source[2][1] * source[1][2] * source[3][3] + source[2][1] * source[1][3] * source[3][2] +
    source[3][1] * source[1][2] * source[2][3] - source[3][1] * source[1][3] * source[2][2];

  inverse[1][0] =
    -source[1][0] * source[2][2] * source[3][3] + source[1][0] * source[2][3] * source[3][2] +
    source[2][0] * source[1][2] * source[3][3] - source[2][0] * source[1][3] * source[3][2] -
    source[3][0] * source[1][2] * source[2][3] + source[3][0] * source[1][3] * source[2][2];

  inverse[2][0] =
    source[1][0] * source[2][1] * source[3][3] - source[1][0] * source[2][3] * source[3][1] -
    source[2][0] * source[1][1] * source[3][3] + source[2][0] * source[1][3] * source[3][1] +
    source[3][0] * source[1][1] * source[2][3] - source[3][0] * source[1][3] * source[2][1];

  inverse[3][0] =
    -source[1][0] * source[2][1] * source[3][2] + source[1][0] * source[2][2] * source[3][1] +
    source[2][0] * source[1][1] * source[3][2] - source[2][0] * source[1][2] * source[3][1] -
    source[3][0] * source[1][1] * source[2][2] + source[3][0] * source[1][2] * source[2][1];

  inverse[0][1] =
    -source[0][1] * source[2][2] * source[3][3] + source[0][1] * source[2][3] * source[3][2] +
    source[2][1] * source[0][2] * source[3][3] - source[2][1] * source[0][3] * source[3][2] -
    source[3][1] * source[0][2] * source[2][3] + source[3][1] * source[0][3] * source[2][2];

  inverse[1][1] =
    source[0][0] * source[2][2] * source[3][3] - source[0][0] * source[2][3] * source[3][2] -
    source[2][0] * source[0][2] * source[3][3] + source[2][0] * source[0][3] * source[3][2] +
    source[3][0] * source[0][2] * source[2][3] - source[3][0] * source[0][3] * source[2][2];

  inverse[2][1] =
    -source[0][0] * source[2][1] * source[3][3] + source[0][0] * source[2][3] * source[3][1] +
    source[2][0] * source[0][1] * source[3][3] - source[2][0] * source[0][3] * source[3][1] -
    source[3][0] * source[0][1] * source[2][3] + source[3][0] * source[0][3] * source[2][1];

  inverse[3][1] =
    source[0][0] * source[2][1] * source[3][2] - source[0][0] * source[2][2] * source[3][1] -
    source[2][0] * source[0][1] * source[3][2] + source[2][0] * source[0][2] * source[3][1] +
    source[3][0] * source[0][1] * source[2][2] - source[3][0] * source[0][2] * source[2][1];

  inverse[0][2] =
    source[0][1] * source[1][2] * source[3][3] - source[0][1] * source[1][3] * source[3][2] -
    source[1][1] * source[0][2] * source[3][3] + source[1][1] * source[0][3] * source[3][2] +
    source[3][1] * source[0][2] * source[1][3] - source[3][1] * source[0][3] * source[1][2];

  inverse[1][2] =
    -source[0][0] * source[1][2] * source[3][3] + source[0][0] * source[1][3] * source[3][2] +
    source[1][0] * source[0][2] * source[3][3] - source[1][0] * source[0][3] * source[3][2] -
    source[3][0] * source[0][2] * source[1][3] + source[3][0] * source[0][3] * source[1][2];

  inverse[2][2] =
    source[0][0] * source[1][1] * source[3][3] - source[0][0] * source[1][3] * source[3][1] -
    source[1][0] * source[0][1] * source[3][3] + source[1][0] * source[0][3] * source[3][1] +
    source[3][0] * source[0][1] * source[1][3] - source[3][0] * source[0][3] * source[1][1];

  inverse[3][2] =
    -source[0][0] * source[1][1] * source[3][2] + source[0][0] * source[1][2] * source[3][1] +
    source[1][0] * source[0][1] * source[3][2] - source[1][0] * source[0][2] * source[3][1] -
    source[3][0] * source[0][1] * source[1][2] + source[3][0] * source[0][2] * source[1][1];

  inverse[0][3] =
    -source[0][1] * source[1][2] * source[2][3] + source[0][1] * source[1][3] * source[2][2] +
    source[1][1] * source[0][2] * source[2][3] - source[1][1] * source[0][3] * source[2][2] -
    source[2][1] * source[0][2] * source[1][3] + source[2][1] * source[0][3] * source[1][2];

  inverse[1][3] =
    source[0][0] * source[1][2] * source[2][3] - source[0][0] * source[1][3] * source[2][2] -
    source[1][0] * source[0][2] * source[2][3] + source[1][0] * source[0][3] * source[2][2] +
    source[2][0] * source[0][2] * source[1][3] - source[2][0] * source[0][3] * source[1][2];

  inverse[2][3] =
    -source[0][0] * source[1][1] * source[2][3] + source[0][0] * source[1][3] * source[2][1] +
    source[1][0] * source[0][1] * source[2][3] - source[1][0] * source[0][3] * source[2][1] -
    source[2][0] * source[0][1] * source[1][3] + source[2][0] * source[0][3] * source[1][1];

  inverse[3][3] =
    source[0][0] * source[1][1] * source[2][2] - source[0][0] * source[1][2] * source[2][1] -
    source[1][0] * source[0][1] * source[2][2] + source[1][0] * source[0][2] * source[2][1] +
    source[2][0] * source[0][1] * source[1][2] - source[2][0] * source[0][2] * source[1][1];

  double determinant = source[0][0] * inverse[0][0] + source[0][1] * inverse[1][0] +
                       source[0][2] * inverse[2][0] + source[0][3] * inverse[3][0];

  if (determinant == 0) {
    return false;
  }

  (*this) = inverse * (1.0 / determinant);

  return true;
}

template<size_t M, size_t N>
bool Matrix<M, N>::inverse3()
{
  auto inverse = Matrix<M, N>::zero();
  auto source = *this;

  inverse[0][0] = source[1][1] * source[2][2] - source[1][2] * source[2][1];
  inverse[1][0] = source[1][2] * source[2][0] - source[1][0] * source[2][2];
  inverse[2][0] = source[1][0] * source[2][1] - source[1][1] * source[2][0];

  inverse[0][1] = source[0][2] * source[2][1] - source[0][1] * source[2][2];
  inverse[1][1] = source[0][0] * source[2][2] - source[0][2] * source[2][0];
  inverse[2][1] = source[0][1] * source[2][0] - source[0][0] * source[2][1];

  inverse[0][2] = source[0][1] * source[1][2] - source[0][2] * source[1][1];
  inverse[1][2] = source[0][2] * source[1][0] - source[0][0] * source[1][2];
  inverse[2][2] = source[0][0] * source[1][1] - source[0][1] * source[1][0];

  double determinant = source[0][0] * inverse[0][0] + source[0][1] * inverse[1][0] +
    source[0][2] * inverse[2][0];

  if (determinant == 0) {
    return false;
  }

  (*this) = inverse * (1.0 / determinant);

  return true;
}

template <size_t M, size_t N>
bool Matrix<M, N>::inverse2()
{
  auto inverse = Matrix<M, N>::zero();
  auto source = *this;

  inverse[0][0] = source[1][1];
  inverse[0][1] = -source[0][1];
  inverse[1][0] = -source[1][0];
  inverse[1][1] = source[0][0];

  double determinant = source[0][0] * inverse[0][0] + source[0][1] * inverse[1][0];
  if (determinant == 0) {
    return false;
  }

  (*this) = inverse * (1.0 / determinant);
  
  return true;
}

template <size_t M, size_t N>
Matrix<N, M> Matrix<M, N>::transpose() const
{
  Matrix<N, M> matrix;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix[j][i] = (*this)[i][j];
    }
  }

  return matrix;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::round(double tolerance) const
{
  Matrix<M, N> matrix;
  for (size_t i = 0; i < M; ++i) {
    for (size_t j = 0; j < N; ++j) {
      matrix[i][j] = std::abs((*this)[i][j]) < tolerance ? 0.0 : (*this)[i][j];
    }
  }

  return matrix;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::power(double exponent) const
{
  if (exponent == 0) {
    return identity();
  }

  if (exponent == 1) {
    return *this;
  }

  auto matrix = *this;

  if (exponent < 0) {
    matrix.inverse();
    exponent = -exponent;
  }

  for (size_t i = 1; i < exponent; ++i) {
    matrix = matrix * (*this);
  }

  return matrix;
}

}  // namespace keisan

#endif  // KEISAN__MATRIX__MATRIX_IMPL_HPP_
