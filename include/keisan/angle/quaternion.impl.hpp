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

#ifndef KEISAN__ANGLE__QUATERNION_IMPL_HPP_
#define KEISAN__ANGLE__QUATERNION_IMPL_HPP_

#include "keisan/angle/euler.hpp"
#include "keisan/angle/quaternion.hpp"
#include "keisan/angle/trigonometry.hpp"

using keisan::literals::operator""_pi;

template<typename T>
std::ostream & operator<<(std::ostream & out, const keisan::Quaternion<T> & quaternion)
{
  return out << quaternion.x << " " << quaternion.y << " " << quaternion.z << " " << quaternion.w;
}

namespace keisan
{

template<typename T>
Quaternion<T>::Quaternion()
{
}

template<typename T>
Quaternion<T>::Quaternion(const T & x, const T & y, const T & z, const T & w)
: x(x), y(y), z(z), w(w)
{
}

template<typename T>
template<typename U>
Quaternion<T>::operator Quaternion<U>() const
{
  return Quaternion<U>(x, y, z, w);
}

template<typename T>
bool Quaternion<T>::operator==(const Quaternion<T> & other) const
{
  return x == other.x && y == other.y && z == other.z && w == other.w;
}

template<typename T>
bool Quaternion<T>::operator!=(const Quaternion<T> & other) const
{
  return x != other.x || y != other.y || z != other.z || w != other.w;
}

template<typename T>
RadEuler<T> Quaternion<T>::to_rad_euler() const
{
  RadEuler<T> rad_euler;

  T sqx = x * x;
  T sqy = y * y;
  T sqz = z * z;
  T sqw = w * w;

  T sarg = -2 * (x * z - w * y) / (sqx + sqy + sqz + sqw);
  if (sarg <= -0.99999) {
    rad_euler.roll = RadAngle<T>(0.0);
    rad_euler.pitch = RadAngle<T>(-0.5_pi);
    rad_euler.yaw = -2.0 * signed_arctan(y, x);
  } else if (sarg >= 0.99999) {
    rad_euler.roll = RadAngle<T>(0.0);
    rad_euler.pitch = RadAngle<T>(0.5_pi);
    rad_euler.yaw = 2.0 * signed_arctan(y, x);
  } else {
    rad_euler.roll = signed_arctan(2 * (y * z + w * x), sqw - sqx - sqy + sqz);
    rad_euler.pitch = arcsin(sarg);
    rad_euler.yaw = signed_arctan(2 * (x * y + w * z), sqw + sqx - sqy - sqz);
  }

  rad_euler.roll = rad_euler.roll.normalize();
  rad_euler.pitch = rad_euler.pitch.normalize();
  rad_euler.yaw = rad_euler.yaw.normalize();

  return rad_euler;
}

}  // namespace keisan

#endif  // KEISAN__ANGLE__QUATERNION_IMPL_HPP_
