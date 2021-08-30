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

#ifndef KEISAN__ANGLE__EULER_IMPL_HPP_
#define KEISAN__ANGLE__EULER_IMPL_HPP_

#include "keisan/angle/euler.hpp"
#include "keisan/angle/quaternion.hpp"
#include "keisan/angle/trigonometry.hpp"

namespace keisan
{

template<typename T>
std::ostream & operator<<(std::ostream & out, const Euler<T> & euler)
{
  return out << euler.roll << " " << euler.pitch << " " << euler.yaw;
}

template<typename T>
Euler<T>::Euler()
{
}

template<typename T>
Euler<T>::Euler(const Angle<T> & roll, const Angle<T> & pitch, const Angle<T> & yaw)
: roll(roll), pitch(pitch), yaw(yaw)
{
}

template<typename T>
template<typename U>
Euler<T>::operator Euler<U>() const
{
  return Euler<U>(roll, pitch, yaw);
}

template<typename T>
bool Euler<T>::operator==(const Euler<T> & other) const
{
  return roll == other.roll && yaw == other.yaw && pitch == other.pitch;
}

template<typename T>
bool Euler<T>::operator!=(const Euler<T> & other) const
{
  return roll != other.roll || yaw != other.yaw || pitch != other.pitch;
}

template<typename T>
Quaternion<T> Euler<T>::quaternion() const
{
  Quaternion<T> quaternion;

  T sr = sin(0.5 * roll);
  T cr = cos(0.5 * roll);
  T sp = sin(0.5 * pitch);
  T cp = cos(0.5 * pitch);
  T sy = sin(0.5 * yaw);
  T cy = cos(0.5 * yaw);

  quaternion.x = sr * cp * cy - cr * sp * sy;
  quaternion.y = cr * sp * cy + sr * cp * sy;
  quaternion.z = cr * cp * sy - sr * sp * cy;
  quaternion.w = cr * cp * cy + sr * sp * sy;

  return quaternion;
}

}  // namespace keisan

#endif  // KEISAN__ANGLE__EULER_IMPL_HPP_
