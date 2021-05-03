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
class Vector : public Matrix<N, 1>
{
public:
  inline Vector();
  inline explicit Vector(const Matrix<N, 1> & matrix);

  template<typename ... Types>
  inline explicit Vector(Types ... values);

  inline static Vector<N> zero();

  inline Vector<N> & operator=(const Matrix<N, 1> & matrix);

  inline Vector<N> & operator+=(const Matrix<N, 1> & matrix);
  inline Vector<N> & operator-=(const Matrix<N, 1> & matrix);

  inline Vector<N> & operator+=(const double & value);
  inline Vector<N> & operator-=(const double & value);
  inline Vector<N> & operator*=(const double & value);
  inline Vector<N> & operator/=(const double & value);

  inline Vector<N> operator+(const Matrix<N, 1> & matrix) const;
  inline Vector<N> operator-(const Matrix<N, 1> & matrix) const;

  inline Vector<N> operator+(const double & value) const;
  inline Vector<N> operator-(const double & value) const;
  inline Vector<N> operator*(const double & value) const;
  inline Vector<N> operator/(const double & value) const;

  inline double & operator[](size_t pos);
  inline const double & operator[](size_t pos) const;
};

template<size_t N>
Vector<N>::Vector()
{
}

template<size_t N>
Vector<N>::Vector(const Matrix<N, 1> & matrix)
: Matrix<N, 1>(matrix)
{
}

template<size_t N>
template<typename ... Types>
Vector<N>::Vector(Types ... values)
: Matrix<N, 1>(values ...)
{
}

template<size_t N>
Vector<N> Vector<N>::zero()
{
  return (Vector<N>)Matrix<N, 1>::zero();
}

template<size_t N>
Vector<N> & Vector<N>::operator=(const Matrix<N, 1> & matrix)
{
  return (Vector<N> & ) Matrix<N, 1>::operator=(matrix);
}

template<size_t N>
Vector<N> & Vector<N>::operator+=(const Matrix<N, 1> & matrix)
{
  return (Vector<N> & ) Matrix<N, 1>::operator+=(matrix);
}

template<size_t N>
Vector<N> & Vector<N>::operator-=(const Matrix<N, 1> & matrix)
{
  return (Vector<N> & ) Matrix<N, 1>::operator-=(matrix);
}

template<size_t N>
Vector<N> & Vector<N>::operator+=(const double & value)
{
  return (Vector<N> & ) Matrix<N, 1>::operator+=(value);
}

template<size_t N>
Vector<N> & Vector<N>::operator-=(const double & value)
{
  return (Vector<N> & ) Matrix<N, 1>::operator-=(value);
}

template<size_t N>
Vector<N> & Vector<N>::operator*=(const double & value)
{
  return (Vector<N> & ) Matrix<N, 1>::operator*=(value);
}

template<size_t N>
Vector<N> & Vector<N>::operator/=(const double & value)
{
  return (Vector<N> & ) Matrix<N, 1>::operator/=(value);
}

template<size_t N>
Vector<N> Vector<N>::operator+(const Matrix<N, 1> & matrix) const
{
  return (Vector<N>) Matrix<N, 1>::operator+(matrix);
}

template<size_t N>
Vector<N> Vector<N>::operator-(const Matrix<N, 1> & matrix) const
{
  return (Vector<N>) Matrix<N, 1>::operator-(matrix);
}

template<size_t N>
Vector<N> Vector<N>::operator+(const double & value) const
{
  return (Vector<N>) Matrix<N, 1>::operator+(value);
}

template<size_t N>
Vector<N> Vector<N>::operator-(const double & value) const
{
  return (Vector<N>) Matrix<N, 1>::operator-(value);
}

template<size_t N>
Vector<N> Vector<N>::operator*(const double & value) const
{
  return (Vector<N>) Matrix<N, 1>::operator*(value);
}

template<size_t N>
Vector<N> Vector<N>::operator/(const double & value) const
{
  return (Vector<N>) Matrix<N, 1>::operator/(value);
}

template<size_t N>
double & Vector<N>::operator[](size_t pos)
{
  return * Matrix<N, 1>::operator[](pos);
}

template<size_t N>
const double & Vector<N>::operator[](size_t pos) const
{
  return * Matrix<N, 1>::operator[](pos);
}

}  // namespace keisan

#endif  // KEISAN__MATRIX__VECTOR_HPP_
