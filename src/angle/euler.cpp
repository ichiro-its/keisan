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

namespace keisan
{

std::ostream & operator<<(std::ostream & out, const Euler & euler)
{
  return out << euler.roll << " " << euler.pitch << " " << euler.yaw;
}

Euler::Euler()
{
}

Euler::Euler(
  const Angle<double> & roll, const Angle<double> & pitch, const Angle<double> & yaw)
: roll(roll), pitch(pitch), yaw(yaw)
{
}

Euler::Euler(const Euler & other)
: roll(other.roll), pitch(other.pitch), yaw(other.yaw)
{
}

Euler & Euler::operator=(const Euler & other)
{
  roll = other.roll;
  pitch = other.pitch;
  yaw = other.yaw;

  return *this;
}

bool Euler::operator==(const Euler & other) const
{
  return roll == other.roll && yaw == other.yaw && pitch == other.pitch;
}

bool Euler::operator!=(const Euler & other) const
{
  return roll != other.roll || yaw != other.yaw || pitch != other.pitch;
}

Quaternion Euler::quaternion() const
{
  Quaternion quaternion;

  double sr = sin(0.5 * roll);
  double cr = cos(0.5 * roll);
  double sp = sin(0.5 * pitch);
  double cp = cos(0.5 * pitch);
  double sy = sin(0.5 * yaw);
  double cy = cos(0.5 * yaw);

  quaternion.x = sr * cp * cy - cr * sp * sy;
  quaternion.y = cr * sp * cy + sr * cp * sy;
  quaternion.z = cr * cp * sy - sr * sp * cy;
  quaternion.w = cr * cp * cy + sr * sp * sy;

  return quaternion;
}

}  // namespace keisan
