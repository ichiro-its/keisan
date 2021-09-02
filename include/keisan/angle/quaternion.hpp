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

#ifndef KEISAN__ANGLE__QUATERNION_HPP_
#define KEISAN__ANGLE__QUATERNION_HPP_

#include <iostream>

namespace keisan
{

// Forward declaration
template<typename T>
struct Euler;

template<typename T>
struct Quaternion
{
  Quaternion();
  Quaternion(const T & x, const T & y, const T & z, const T & w);

  template<typename U>
  operator Quaternion<U>() const;

  bool operator==(const Quaternion<T> & other) const;
  bool operator!=(const Quaternion<T> & other) const;

  Euler<T> euler() const;

  T x;
  T y;
  T z;
  T w;
};

}  // namespace keisan

template<typename T>
std::ostream & operator<<(std::ostream & out, const keisan::Quaternion<T> & quaternion);

#include "keisan/angle/quaternion.impl.hpp"

#endif  // KEISAN__ANGLE__QUATERNION_HPP_
