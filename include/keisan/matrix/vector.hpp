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

namespace keisan
{

template <size_t N>
class Vector
{
public:
  Vector();

  template <typename... Types>
  explicit Vector(const double & value, Types... the_rest);

  Vector(const Vector<N> & vector);

  static Vector<N> zero();

  Vector<N> & operator=(const Vector<N> & vector);

  bool operator==(const Vector<N> & vector) const;
  bool operator!=(const Vector<N> & vector) const;

  Vector<N> & operator+=(const Vector<N> & vector);
  Vector<N> & operator-=(const Vector<N> & vector);

  Vector<N> & operator+=(const double & value);
  Vector<N> & operator-=(const double & value);
  Vector<N> & operator*=(const double & value);
  Vector<N> & operator/=(const double & value);

  Vector<N> operator+(const Vector<N> & matrix) const;
  Vector<N> operator-(const Vector<N> & matrix) const;

  Vector<N> operator+(const double & value) const;
  Vector<N> operator-(const double & value) const;
  Vector<N> operator*(const double & value) const;
  Vector<N> operator/(const double & value) const;

  Vector<N> operator-() const;

  double & operator[](size_t pos);
  const double & operator[](size_t pos) const;

private:
  double data[N];
};

}  // namespace keisan

template <size_t N>
std::ostream & operator<<(std::ostream & out, const keisan::Vector<N> & vector);

template <size_t N>
keisan::Vector<N> operator*(const double & value, const keisan::Vector<N> & vector);

#include "keisan/matrix/vector.impl.hpp"

#endif  // KEISAN__MATRIX__VECTOR_HPP_
