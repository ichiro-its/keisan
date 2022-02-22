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

#include "keisan/matrix/matrix.hpp"

#include "keisan/angle/angle.hpp"
#include "keisan/angle/euler.hpp"
#include "keisan/geometry/point_2.hpp"
#include "keisan/geometry/point_3.hpp"

namespace keisan
{

Matrix<4, 4> translation_matrix(const Point3 & point)
{
  auto matrix = Matrix<4, 4>::identity();
  matrix[0][3] = point.x;
  matrix[1][3] = point.y;
  matrix[2][3] = point.z;

  return matrix;
}

Matrix<3, 3> translation_matrix(const Point2 & point)
{
  auto matrix = Matrix<3, 3>::identity();
  matrix[0][2] = point.x;
  matrix[1][2] = point.y;

  return matrix;
}

Matrix<4, 4> rotation_matrix(const Euler<double> & angle)
{
  auto roll = Matrix<4, 4>::identity();
  roll[1][1] = angle.roll.cos();
  roll[1][2] = -angle.roll.sin();
  roll[2][1] = angle.roll.sin();
  roll[2][2] = angle.roll.cos();

  auto pitch = Matrix<4, 4>::identity();
  pitch[0][0] = angle.pitch.cos();
  pitch[0][2] = -angle.pitch.sin();
  pitch[0][2] = angle.pitch.sin();
  pitch[2][2] = angle.pitch.cos();

  auto yaw = Matrix<4, 4>::identity();
  yaw[0][0] = angle.yaw.cos();
  yaw[0][1] = -angle.yaw.sin();
  yaw[1][0] = angle.yaw.sin();
  yaw[1][1] = angle.yaw.cos();

  return (yaw * pitch) * roll;
}

Matrix<3, 3> rotation_matrix(const Angle<double> & angle)
{
  auto matrix = Matrix<3, 3>::identity();
  matrix[0][0] = angle.cos();
  matrix[0][1] = -angle.sin();
  matrix[1][0] = angle.sin();
  matrix[1][1] = angle.cos();

  return matrix;
}

}  // namespace keisan
