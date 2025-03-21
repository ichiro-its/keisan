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

#ifndef KEISAN__MATRIX__MATRIX_HPP_
#define KEISAN__MATRIX__MATRIX_HPP_

#include <ostream>

#include "keisan/angle/angle.hpp"
#include "keisan/angle/euler.hpp"
#include "keisan/geometry/point_2.hpp"
#include "keisan/geometry/point_3.hpp"
#include "keisan/matrix/vector.hpp"

namespace keisan
{

template<size_t M, size_t N>
class Matrix
{
public:
  Matrix();

  template<typename ... Types>
  explicit Matrix(const double & value, Types ... the_rest);

  Matrix(const Matrix<M, N> & matrix);

  static Matrix<M, N> zero();
  static Matrix<M, N> identity();

  Matrix<M, N> & operator=(const Matrix<M, N> & matrix);

  bool operator==(const Matrix<M, N> & matrix) const;
  bool operator!=(const Matrix<M, N> & matrix) const;

  Matrix<M, N> & operator+=(const Matrix<M, N> & matrix);
  Matrix<M, N> & operator-=(const Matrix<M, N> & matrix);

  Matrix<M, N> & operator+=(const double & value);
  Matrix<M, N> & operator-=(const double & value);
  Matrix<M, N> & operator*=(const double & value);
  Matrix<M, N> & operator/=(const double & value);

  template<size_t O>
  Matrix<M, O> operator*(const Matrix<N, O> & matrix);

  Vector<M> operator*(const Vector<N> & vector);

  Matrix<M, N> operator+(const Matrix<M, N> & matrix) const;
  Matrix<M, N> operator-(const Matrix<M, N> & matrix) const;

  Matrix<M, N> operator+(const double & value) const;
  Matrix<M, N> operator-(const double & value) const;
  Matrix<M, N> operator*(const double & value) const;
  Matrix<M, N> operator/(const double & value) const;

  Matrix<M, N> operator-() const;

  double * operator[](size_t pos);
  const double * operator[](size_t pos) const;

  bool inverse();
  bool inverse2();

  Matrix<N, M> transpose() const;
  Matrix<M, N> round(double tolerance) const;

private:
  double data[M * N];
};

Matrix<3, 3> translation_matrix(const Point2 & point);

Matrix<4, 4> translation_matrix(const Point3 & point);

Matrix<3, 3> rotation_matrix(const Angle<double> & angle);

Matrix<4, 4> rotation_matrix(const Euler<double> & angle);

Matrix<4, 4> rotation_matrix(const Quaternion<double> & quaternion);

}  // namespace keisan

template<size_t M, size_t N>
std::ostream & operator<<(std::ostream & out, const keisan::Matrix<M, N> & matrix);

template<size_t M, size_t N>
keisan::Matrix<M, N> operator*(const double & value, const keisan::Matrix<M, N> & matrix);

#include "keisan/matrix/matrix.impl.hpp"

#endif  // KEISAN__MATRIX__MATRIX_HPP_
