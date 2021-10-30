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

#include "gtest/gtest.h"
#include "keisan/matrix/matrix.hpp"

template<size_t M, size_t N>
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

template<size_t M, size_t N>
inline keisan::Matrix<M, N> operator*(const double & value, const keisan::Matrix<M, N> & matrix)
{
  return matrix * value;
}

namespace keisan
{

template<size_t M, size_t N>
Matrix<M, N>::Matrix()
{
}

template<size_t M, size_t N>
template<typename ... Types>
Matrix<M, N>::Matrix(const double & value, Types ... the_rest)
: data{value, the_rest ...}
{
}

template<size_t M, size_t N>
Matrix<M, N>::Matrix(const Matrix<M, N> & matrix)
{
  *this = matrix;
}

template<size_t M, size_t N>
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

template<size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator=(const Matrix<M, N> & matrix)
{
  std::copy(matrix.data, matrix.data + M * N, data);
  return *this;
}

template<size_t M, size_t N>
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

template<size_t M, size_t N>
bool Matrix<M, N>::operator!=(const Matrix<M, N> & matrix) const
{
  return !(*this == matrix);
}

template<size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator+=(const Matrix<M, N> & matrix)
{
  for (size_t i = 0; i < M * N; ++i) {
    data[i] += matrix.data[i];
  }

  return *this;
}

template<size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator-=(const Matrix<M, N> & matrix)
{
  for (size_t i = 0; i < M * N; ++i) {
    data[i] -= matrix.data[i];
  }

  return *this;
}

template<size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator+=(const double & value)
{
  for (size_t i = 0; i < M * N; ++i) {
    data[i] += value;
  }

  return *this;
}

template<size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator-=(const double & value)
{
  for (size_t i = 0; i < M * N; ++i) {
    data[i] -= value;
  }

  return *this;
}

template<size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator*=(const double & value)
{
  for (size_t i = 0; i < M * N; ++i) {
    data[i] *= value;
  }

  return *this;
}

template<size_t M, size_t N>
Matrix<M, N> & Matrix<M, N>::operator/=(const double & value)
{
  for (size_t i = 0; i < M * N; ++i) {
    data[i] /= value;
  }

  return *this;
}


template<size_t M, size_t N>
template<size_t O>
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

template<size_t M, size_t N>
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

template<size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator+(const Matrix<M, N> & matrix) const
{
  auto new_matrix = *this;
  new_matrix += matrix;

  return new_matrix;
}

template<size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator-(const Matrix<M, N> & matrix) const
{
  auto new_matrix = *this;
  new_matrix -= matrix;

  return new_matrix;
}

template<size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator+(const double & value) const
{
  auto new_matrix = *this;
  new_matrix += value;

  return new_matrix;
}

template<size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator-(const double & value) const
{
  auto new_matrix = *this;
  new_matrix -= value;

  return new_matrix;
}

template<size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator*(const double & value) const
{
  auto new_matrix = *this;
  new_matrix *= value;

  return new_matrix;
}

template<size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator/(const double & value) const
{
  auto new_matrix = *this;
  new_matrix /= value;

  return new_matrix;
}

template<size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator-() const
{
  Matrix<M, N> matrix;
  for (size_t i = 0; i < M * N; ++i) {
    matrix.data[i] = -data[i];
  }

  return matrix;
}

template<size_t M, size_t N>
double * Matrix<M, N>::operator[](size_t pos)
{
  return data + (pos * N);
}

template<size_t M, size_t N>
const double * Matrix<M, N>::operator[](size_t pos) const
{
  return data + (pos * N);
}

}  // namespace keisan

#endif  // KEISAN__MATRIX__MATRIX_IMPL_HPP_
