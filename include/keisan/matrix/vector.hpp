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

#ifndef KEISAN__MATRIX__VECTOR_HPP_
#define KEISAN__MATRIX__VECTOR_HPP_

#include "./matrix.hpp"

namespace keisan
{

template<size_t N>
class Vector
{
public:
  inline Vector();
  inline explicit Vector(const Matrix<N, 1> & matrix);

  template<typename ... Types>
  inline explicit Vector(const double & value, Types ... the_rest);

  inline Vector(const Vector<N> & vector);

  inline operator Matrix<N, 1>() const;

  inline static Vector<N> zero();

  inline Vector<N> & operator=(const Vector<N> & vector);

  inline Vector<N> & operator+=(const Vector<N> & vector);
  inline Vector<N> & operator-=(const Vector<N> & vector);

  inline Vector<N> & operator+=(const double & value);
  inline Vector<N> & operator-=(const double & value);
  inline Vector<N> & operator*=(const double & value);
  inline Vector<N> & operator/=(const double & value);

  inline Vector<N> operator+(const Vector<N> & matrix) const;
  inline Vector<N> operator-(const Vector<N> & matrix) const;

  inline Vector<N> operator+(const double & value) const;
  inline Vector<N> operator-(const double & value) const;
  inline Vector<N> operator*(const double & value) const;
  inline Vector<N> operator/(const double & value) const;

  inline Vector<N> operator-() const;

  inline double & operator[](size_t pos);
  inline const double & operator[](size_t pos) const;

private:
  Matrix<N, 1> matrix;
};

template<size_t N>
Vector<N>::Vector()
{
}

template<size_t N>
Vector<N>::Vector(const Matrix<N, 1> & matrix)
: matrix(matrix)
{
}

template<size_t N>
template<typename ... Types>
Vector<N>::Vector(const double & value, Types ... the_rest)
: matrix(value, the_rest ...)
{
}

template<size_t N>
Vector<N>::Vector(const Vector<N> & vector)
: matrix(vector)
{
}

template<size_t N>
Vector<N>::operator Matrix<N, 1>() const
{
  return matrix;
}

template<size_t N>
Vector<N> Vector<N>::zero()
{
  return Vector<N>(Matrix<N, 1>::zero());
}

template<size_t N>
Vector<N> & Vector<N>::operator=(const Vector<N> & vector)
{
  matrix = vector.matrix;
  return *this;
}

template<size_t N>
Vector<N> & Vector<N>::operator+=(const Vector<N> & vector)
{
  matrix += vector.matrix;
  return *this;
}

template<size_t N>
Vector<N> & Vector<N>::operator-=(const Vector<N> & vector)
{
  matrix -= vector.matrix;
  return *this;
}

template<size_t N>
Vector<N> & Vector<N>::operator+=(const double & value)
{
  matrix += value;
  return *this;
}

template<size_t N>
Vector<N> & Vector<N>::operator-=(const double & value)
{
  matrix -= value;
  return *this;
}

template<size_t N>
Vector<N> & Vector<N>::operator*=(const double & value)
{
  matrix *= value;
  return *this;
}

template<size_t N>
Vector<N> & Vector<N>::operator/=(const double & value)
{
  matrix /= value;
  return *this;
}

template<size_t N>
Vector<N> Vector<N>::operator+(const Vector<N> & vector) const
{
  return Vector<N>(matrix + vector.matrix);
}

template<size_t N>
Vector<N> Vector<N>::operator-(const Vector<N> & vector) const
{
  return Vector<N>(matrix - vector.matrix);
}

template<size_t N>
Vector<N> Vector<N>::operator+(const double & value) const
{
  return Vector<N>(matrix + value);
}

template<size_t N>
Vector<N> Vector<N>::operator-(const double & value) const
{
  return Vector<N>(matrix - value);
}

template<size_t N>
Vector<N> Vector<N>::operator*(const double & value) const
{
  return Vector<N>(matrix * value);
}

template<size_t N>
Vector<N> Vector<N>::operator/(const double & value) const
{
  return Vector<N>(matrix / value);
}

template<size_t N>
Vector<N> Vector<N>::operator-() const
{
  return Vector<N>(-matrix);
}

template<size_t N>
double & Vector<N>::operator[](size_t pos)
{
  return matrix[pos][0];
}

template<size_t N>
const double & Vector<N>::operator[](size_t pos) const
{
  return matrix[pos][0];
}

}  // namespace keisan

#endif  // KEISAN__MATRIX__VECTOR_HPP_
