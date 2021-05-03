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

#include <array>

namespace keisan
{

template<size_t N>
class Vector
{
public:
  Vector();
  Vector(const Vector<N> & vector);

  template<typename ... Types>
  explicit Vector(Types ... values);

  Vector<N> & operator=(const Vector<N> & vector);

  Vector<N> & operator+=(const Vector<N> & vector);
  Vector<N> & operator-=(const Vector<N> & vector);

  Vector<N> & operator+=(const double & value);
  Vector<N> & operator-=(const double & value);
  Vector<N> & operator*=(const double & value);
  Vector<N> & operator/=(const double & value);

  Vector<N> operator+(const Vector<N> & vector) const;
  Vector<N> operator-(const Vector<N> & vector) const;

  Vector<N> operator+(const double & value) const;
  Vector<N> operator-(const double & value) const;
  Vector<N> operator*(const double & value) const;
  Vector<N> operator/(const double & value) const;

  double & operator[](size_t pos);
  const double & operator[](size_t pos) const;

private:
  std::array<double, N> data;
};

template<size_t N>
Vector<N>::Vector()
{
  data.fill(0.0);
}

template<size_t N>
Vector<N>::Vector(const Vector<N> & vector)
: data(vector.data)
{
}

template<size_t N>
template<typename ... Types>
Vector<N>::Vector(Types ... values)
: data({values ...})
{
}

template<size_t N>
Vector<N> & Vector<N>::operator=(const Vector<N> & vector)
{
  for (size_t i = 0; i < N; ++i) {
    data[i] = vector[i];
  }

  return *this;
}

template<size_t N>
Vector<N> & Vector<N>::operator+=(const Vector<N> & vector)
{
  for (size_t i = 0; i < N; ++i) {
    data[i] += vector[i];
  }

  return *this;
}

template<size_t N>
Vector<N> & Vector<N>::operator-=(const Vector<N> & vector)
{
  for (size_t i = 0; i < N; ++i) {
    data[i] -= vector[i];
  }

  return *this;
}

template<size_t N>
Vector<N> & Vector<N>::operator+=(const double & value)
{
  for (auto & datum : data) {
    datum += value;
  }

  return *this;
}

template<size_t N>
Vector<N> & Vector<N>::operator-=(const double & value)
{
  for (auto & datum : data) {
    datum -= value;
  }

  return *this;
}

template<size_t N>
Vector<N> & Vector<N>::operator*=(const double & value)
{
  for (auto & datum : data) {
    datum *= value;
  }

  return *this;
}

template<size_t N>
Vector<N> & Vector<N>::operator/=(const double & value)
{
  for (auto & datum : data) {
    datum /= value;
  }

  return *this;
}

template<size_t N>
Vector<N> Vector<N>::operator+(const Vector<N> & vector) const
{
  auto new_vector = *this;
  new_vector += vector;

  return new_vector;
}

template<size_t N>
Vector<N> Vector<N>::operator-(const Vector<N> & vector) const
{
  auto new_vector = *this;
  new_vector -= vector;

  return new_vector;
}

template<size_t N>
Vector<N> Vector<N>::operator+(const double & value) const
{
  auto new_vector = *this;
  new_vector += value;

  return new_vector;
}

template<size_t N>
Vector<N> Vector<N>::operator-(const double & value) const
{
  auto new_vector = *this;
  new_vector -= value;

  return new_vector;
}

template<size_t N>
Vector<N> Vector<N>::operator*(const double & value) const
{
  auto new_vector = *this;
  new_vector *= value;

  return new_vector;
}

template<size_t N>
Vector<N> Vector<N>::operator/(const double & value) const
{
  auto new_vector = *this;
  new_vector /= value;

  return new_vector;
}

template<size_t N>
double & Vector<N>::operator[](size_t pos)
{
  return data[pos];
}

template<size_t N>
const double & Vector<N>::operator[](size_t pos) const
{
  return data[pos];
}

}  // namespace keisan

#endif  // KEISAN__MATRIX__VECTOR_HPP_
