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

#include <ostream>

#include "keisan/matrix/matrix.hpp"

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

  inline bool operator==(const Vector<N> & vector) const;
  inline bool operator!=(const Vector<N> & vector) const;

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

}  // namespace keisan

template<size_t N>
inline std::ostream & operator<<(std::ostream & out, const keisan::Vector<N> & vector);

template<size_t N>
inline keisan::Vector<N> operator*(const double & value, const keisan::Vector<N> & vector);

#include "keisan/matrix/vector.impl.hpp"

#endif  // KEISAN__MATRIX__VECTOR_HPP_
