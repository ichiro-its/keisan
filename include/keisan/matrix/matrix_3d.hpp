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

#ifndef KEISAN__MATRIX__MATRIX_3D_HPP_
#define KEISAN__MATRIX__MATRIX_3D_HPP_

#include <memory>

#include "keisan/matrix/matrix.hpp"
#include "keisan/geometry/point_3.hpp"
#include "keisan/matrix/vector.hpp"

namespace keisan
{

class Matrix3D
{
public:
  static Matrix<4, 4> identity();

  static bool inverse(std::shared_ptr<Matrix<4, 4>> matrix);

  static void transform(std::shared_ptr<Matrix<4, 4>> matrix,
    const Point3 & point, const Vector<3> & angle);
};

}  // namespace keisan

#endif  // KEISAN__MATRIX__MATRIX_3D_HPP_
