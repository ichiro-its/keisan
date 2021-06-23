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

#ifndef KEISAN__MATRIX__SQUARE_MATRIX_HPP_
#define KEISAN__MATRIX__SQUARE_MATRIX_HPP_

#include <ostream>

#include "./matrix.hpp"
#include "./vector.hpp"

namespace keisan
{

template<size_t N>
class SquareMatrix;

template<size_t N>
inline std::ostream & operator<<(std::ostream & out, const SquareMatrix<N> square_matrix);

template<size_t N>
class SquareMatrix
{
public:
  inline SquareMatrix();
  inline explicit SquareMatrix(const Matrix<N, N> & matrix);

  template<typename ... Types>
  inline explicit SquareMatrix(const double & value, Types ... the_rest);

  inline SquareMatrix(const SquareMatrix<N> & square_matrix);

  inline operator Matrix<N, N>() const;

  inline static SquareMatrix<N> zero();
  inline static SquareMatrix<N> identity();

  inline SquareMatrix<N> & operator=(const SquareMatrix<N> & square_matrix);

  inline SquareMatrix<N> & operator+=(const SquareMatrix<N> & square_matrix);
  inline SquareMatrix<N> & operator-=(const SquareMatrix<N> & square_matrix);

  inline SquareMatrix<N> & operator+=(const double & value);
  inline SquareMatrix<N> & operator-=(const double & value);
  inline SquareMatrix<N> & operator*=(const double & value);
  inline SquareMatrix<N> & operator/=(const double & value);

  template<size_t O>
  inline Matrix<N, O> operator*(const Matrix<N, O> & matrix);

  inline SquareMatrix<N> operator*(const SquareMatrix<N> & square_matrix);
  inline Vector<N> operator*(const Vector<N> & vector);

  inline SquareMatrix<N> operator+(const SquareMatrix<N> & square_matrix) const;
  inline SquareMatrix<N> operator-(const SquareMatrix<N> & square_matrix) const;

  inline SquareMatrix<N> operator+(const double & value) const;
  inline SquareMatrix<N> operator-(const double & value) const;
  inline SquareMatrix<N> operator*(const double & value) const;
  inline SquareMatrix<N> operator/(const double & value) const;

  inline SquareMatrix<N> operator-() const;

  inline double * operator[](size_t pos);
  inline const double * operator[](size_t pos) const;

private:
  Matrix<N, N> matrix;
};

template<size_t N>
std::ostream & operator<<(std::ostream & out, const SquareMatrix<N> square_matrix)
{
  return out << (Matrix<N, N>)square_matrix;
}

template<size_t N>
SquareMatrix<N>::SquareMatrix()
{
}

template<size_t N>
SquareMatrix<N>::SquareMatrix(const Matrix<N, N> & matrix)
: matrix(matrix)
{
}

template<size_t N>
template<typename ... Types>
SquareMatrix<N>::SquareMatrix(const double & value, Types ... the_rest)
: matrix(value, the_rest ...)
{
}

template<size_t N>
SquareMatrix<N>::SquareMatrix(const SquareMatrix<N> & square_matrix)
: matrix(square_matrix)
{
}

template<size_t N>
SquareMatrix<N>::operator Matrix<N, N>() const
{
  return matrix;
}

template<size_t N>
SquareMatrix<N> SquareMatrix<N>::zero()
{
  return SquareMatrix<N>(Matrix<N, N>::zero());
}

template<size_t N>
SquareMatrix<N> SquareMatrix<N>::identity()
{
  auto square_matrix = zero();
  for (size_t i = 0; i < N; ++i) {
    square_matrix[i][i] = 1.0;
  }

  return square_matrix;
}

template<size_t N>
SquareMatrix<N> & SquareMatrix<N>::operator=(const SquareMatrix<N> & square_matrix)
{
  matrix = square_matrix.matrix;
  return *this;
}

template<size_t N>
SquareMatrix<N> & SquareMatrix<N>::operator+=(const SquareMatrix<N> & square_matrix)
{
  matrix += square_matrix.matrix;
  return *this;
}

template<size_t N>
SquareMatrix<N> & SquareMatrix<N>::operator-=(const SquareMatrix<N> & square_matrix)
{
  matrix -= square_matrix.matrix;
  return *this;
}

template<size_t N>
SquareMatrix<N> & SquareMatrix<N>::operator+=(const double & value)
{
  matrix += value;
  return *this;
}

template<size_t N>
SquareMatrix<N> & SquareMatrix<N>::operator-=(const double & value)
{
  matrix -= value;
  return *this;
}

template<size_t N>
SquareMatrix<N> & SquareMatrix<N>::operator*=(const double & value)
{
  matrix *= value;
  return *this;
}

template<size_t N>
SquareMatrix<N> & SquareMatrix<N>::operator/=(const double & value)
{
  matrix /= value;
  return *this;
}

template<size_t N>
template<size_t O>
Matrix<N, O> SquareMatrix<N>::operator*(const Matrix<N, O> & matrix)
{
  return this->matrix * matrix;
}

template<size_t N>
SquareMatrix<N> SquareMatrix<N>::operator*(const SquareMatrix<N> & square_matrix)
{
  return SquareMatrix<N>(matrix * square_matrix.matrix);
}

template<size_t N>
Vector<N> SquareMatrix<N>::operator*(const Vector<N> & vector)
{
  return matrix * vector;
}

template<size_t N>
SquareMatrix<N> SquareMatrix<N>::operator+(const SquareMatrix<N> & square_matrix) const
{
  return SquareMatrix<N>(matrix + square_matrix.matrix);
}

template<size_t N>
SquareMatrix<N> SquareMatrix<N>::operator-(const SquareMatrix<N> & square_matrix) const
{
  return SquareMatrix<N>(matrix - square_matrix.matrix);
}

template<size_t N>
SquareMatrix<N> SquareMatrix<N>::operator+(const double & value) const
{
  return SquareMatrix<N>(matrix + value);
}

template<size_t N>
SquareMatrix<N> SquareMatrix<N>::operator-(const double & value) const
{
  return SquareMatrix<N>(matrix - value);
}

template<size_t N>
SquareMatrix<N> SquareMatrix<N>::operator*(const double & value) const
{
  return SquareMatrix<N>(matrix * value);
}

template<size_t N>
SquareMatrix<N> SquareMatrix<N>::operator/(const double & value) const
{
  return SquareMatrix<N>(matrix / value);
}

template<size_t N>
SquareMatrix<N> SquareMatrix<N>::operator-() const
{
  return SquareMatrix<N>(-matrix);
}

template<size_t N>
double * SquareMatrix<N>::operator[](size_t pos)
{
  return matrix[pos];
}

template<size_t N>
const double * SquareMatrix<N>::operator[](size_t pos) const
{
  return matrix[pos];
}

}  // namespace keisan

#endif  // KEISAN__MATRIX__SQUARE_MATRIX_HPP_
