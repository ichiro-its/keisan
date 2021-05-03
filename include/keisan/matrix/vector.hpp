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

  template<typename ... Types>
  explicit Vector(Types ... values);

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
template<typename ... Types>
Vector<N>::Vector(Types ... values)
: data({values ...})
{
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
