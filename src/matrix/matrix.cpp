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

#include <memory>

#include "keisan/matrix/matrix.hpp"

#include "keisan/angle/angle.hpp"
#include "keisan/angle/euler.hpp"
#include "keisan/geometry/point_2.hpp"
#include "keisan/geometry/point_3.hpp"

namespace keisan
{

Matrix<4, 4> translation_matrix(const Point3 & point) {}
Matrix<3, 3> translation_matrix(const Point2 & point) {}

Matrix<4, 4> rotation_matrix(const Euler<double> & angle) {}
Matrix<3, 3> rotation_matrix(const Angle<double> & angle) {}

// Matrix<4, 4> Matrix3D::transformation_of(const Point3 & point, const Vector<3> & angle)
// {
//   double cos_x = cos(angle[0]);
//   double cos_y = cos(angle[1]);
//   double cos_z = cos(angle[2]);
//   double sin_x = sin(angle[0]);
//   double sin_y = sin(angle[1]);
//   double sin_z = sin(angle[2]);

//   auto result = Matrix<4, 4>::identity();
//   result[0][0] = cos_z * cos_y;
//   result[0][1] = cos_z * sin_y * sin_x - sin_z * cos_x;
//   result[0][2] = cos_z * sin_y * cos_x + sin_z * sin_x;
//   result[0][3] = point.x;
//   result[1][0] = sin_z * cos_y;
//   result[1][1] = sin_z * sin_y * sin_x + cos_z * cos_x;
//   result[1][2] = sin_z * sin_y * cos_x - cos_z * sin_x;
//   result[1][3] = point.y;
//   result[2][0] = -sin_y;
//   result[2][1] = cos_y * sin_x;
//   result[2][2] = cos_y * cos_x;
//   result[2][3] = point.z;

//   return result;
// }

}  // namespace keisan
