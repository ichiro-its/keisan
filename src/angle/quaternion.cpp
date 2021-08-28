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

#include "keisan/angle/euler.hpp"
#include "keisan/angle/quaternion.hpp"
#include "keisan/angle/trigonometry.hpp"

using keisan::literals::operator""_pi;

namespace keisan
{

std::ostream & operator<<(std::ostream & out, const Quaternion & quaternion)
{
  return out << quaternion.x << " " << quaternion.y << " " << quaternion.z << " " << quaternion.w;
}

Quaternion::Quaternion()
{
}

Quaternion::Quaternion(const double & x, const double & y, const double & z, const double & w)
: x(x), y(y), z(z), w(w)
{
}

Quaternion::Quaternion(const Quaternion & other)
: x(other.x), y(other.y), z(other.z), w(other.w)
{
}

Quaternion & Quaternion::operator=(const Quaternion & other)
{
  x = other.x;
  y = other.y;
  z = other.z;
  w = other.w;

  return *this;
}

bool Quaternion::operator==(const Quaternion & other) const
{
  return x == other.x && y == other.y && z == other.z && w == other.w;
}

bool Quaternion::operator!=(const Quaternion & other) const
{
  return x != other.x || y != other.y || z != other.z || w != other.w;
}

Euler<double> Quaternion::euler() const
{
  Euler<double> euler;

  double sqx = x * x;
  double sqy = y * y;
  double sqz = z * z;
  double sqw = w * w;

  double sarg = -2 * (x * z - w * y) / (sqx + sqy + sqz + sqw);
  if (sarg <= -0.99999) {
    euler.roll = make_radian(0.0);
    euler.pitch = make_radian(-0.5_pi);
    euler.yaw = -2.0 * signed_arctan(y, x);
  } else if (sarg >= 0.99999) {
    euler.roll = make_radian(0.0);
    euler.pitch = make_radian(0.5_pi);
    euler.yaw = 2.0 * signed_arctan(y, x);
  } else {
    euler.roll = signed_arctan(2 * (y * z + w * x), sqw - sqx - sqy + sqz);
    euler.pitch = arcsin(sarg);
    euler.yaw = signed_arctan(2 * (x * y + w * z), sqw + sqx - sqy - sqz);
  }

  euler.roll = euler.roll.normalize();
  euler.pitch = euler.pitch.normalize();
  euler.yaw = euler.yaw.normalize();

  return euler;
}

}  // namespace keisan
