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

#include "keisan/matrix/matrix_3d.hpp"
#include "keisan/matrix/matrix.hpp"

namespace keisan
{

Matrix<4, 4> Matrix3D::identity()
{
  return Matrix<4, 4>(
    1.0, 0.0, 0.0, 0.0,
    0.0, 1.0, 0.0, 0.0,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0);
}

bool Matrix3D::inverse(std::shared_ptr<Matrix<4, 4>> matrix)
{
  auto inverse = Matrix<4, 4>::zero();
  auto source = * matrix;

  inverse[0][0] = source[1][1] * source[2][2] * source[3][3] -
                  source[1][1] * source[2][3] * source[3][2] -
                  source[2][1] * source[1][2] * source[3][3] +
                  source[2][1] * source[1][3] * source[3][2] +
                  source[3][1] * source[1][2] * source[2][3] -
                  source[3][1] * source[1][3] * source[2][2];

  inverse[1][0] = -source[1][0] * source[2][2] * source[3][3] +
                   source[1][0] * source[2][3] * source[3][2] +
                   source[2][0] * source[1][2] * source[3][3] -
                   source[2][0] * source[1][3] * source[3][2] -
                   source[3][0] * source[1][2] * source[2][3] +
                   source[3][0] * source[1][3] * source[2][2];

  inverse[2][0] = source[1][0] * source[2][1] * source[3][3] -
                  source[1][0] * source[2][3] * source[3][1] -
                  source[2][0] * source[1][1] * source[3][3] +
                  source[2][0] * source[1][3] * source[3][1] +
                  source[3][0] * source[1][1] * source[2][3] -
                  source[3][0] * source[1][3] * source[2][1];

  inverse[3][0] = -source[1][0] * source[2][1] * source[3][2] +
                   source[1][0] * source[2][2] * source[3][1] +
                   source[2][0] * source[1][1] * source[3][2] -
                   source[2][0] * source[1][2] * source[3][1] -
                   source[3][0] * source[1][1] * source[2][2] +
                   source[3][0] * source[1][2] * source[2][1];

  inverse[0][1] = -source[0][1] * source[2][2] * source[3][3] +
                   source[0][1] * source[2][3] * source[3][2] +
                   source[2][1] * source[0][2] * source[3][3] -
                   source[2][1] * source[0][3] * source[3][2] -
                   source[3][1] * source[0][2] * source[2][3] +
                   source[3][1] * source[0][3] * source[2][2];

  inverse[1][1] = source[0][0] * source[2][2] * source[3][3] -
                  source[0][0] * source[2][3] * source[3][2] -
                  source[2][0] * source[0][2] * source[3][3] +
                  source[2][0] * source[0][3] * source[3][2] +
                  source[3][0] * source[0][2] * source[2][3] -
                  source[3][0] * source[0][3] * source[2][2];

  inverse[2][1] = -source[0][0] * source[2][1] * source[3][3] +
                   source[0][0] * source[2][3] * source[3][1] +
                   source[2][0] * source[0][1] * source[3][3] -
                   source[2][0] * source[0][3] * source[3][1] -
                   source[3][0] * source[0][1] * source[2][3] +
                   source[3][0] * source[0][3] * source[2][1];

  inverse[3][1] = source[0][0] * source[2][1] * source[3][2] -
                  source[0][0] * source[2][2] * source[3][1] -
                  source[2][0] * source[0][1] * source[3][2] +
                  source[2][0] * source[0][2] * source[3][1] +
                  source[3][0] * source[0][1] * source[2][2] -
                  source[3][0] * source[0][2] * source[2][1];

  inverse[0][2] = source[0][1] * source[1][2] * source[3][3] -
                  source[0][1] * source[1][3] * source[3][2] -
                  source[1][1] * source[0][2] * source[3][3] +
                  source[1][1] * source[0][3] * source[3][2] +
                  source[3][1] * source[0][2] * source[1][3] -
                  source[3][1] * source[0][3] * source[1][2];

  inverse[1][2] = -source[0][0] * source[1][2] * source[3][3] +
                   source[0][0] * source[1][3] * source[3][2] +
                   source[1][0] * source[0][2] * source[3][3] -
                   source[1][0] * source[0][3] * source[3][2] -
                   source[3][0] * source[0][2] * source[1][3] +
                   source[3][0] * source[0][3] * source[1][2];

  inverse[2][2] = source[0][0] * source[1][1] * source[3][3] -
                  source[0][0] * source[1][3] * source[3][1] -
                  source[1][0] * source[0][1] * source[3][3] +
                  source[1][0] * source[0][3] * source[3][1] +
                  source[3][0] * source[0][1] * source[1][3] -
                  source[3][0] * source[0][3] * source[1][1];

  inverse[2][3] = -source[0][0] * source[1][1] * source[3][2] +
                   source[0][0] * source[1][2] * source[3][1] +
                   source[1][0] * source[0][1] * source[3][2] -
                   source[1][0] * source[0][2] * source[3][1] -
                   source[3][0] * source[0][1] * source[1][2] +
                   source[3][0] * source[0][2] * source[1][1];

  inverse[0][3] = -source[0][1] * source[1][2] * source[2][3] +
                   source[0][1] * source[1][3] * source[2][2] +
                   source[1][1] * source[0][2] * source[2][3] -
                   source[1][1] * source[0][3] * source[2][2] -
                   source[2][1] * source[0][2] * source[1][3] +
                   source[2][1] * source[0][3] * source[1][2];

  inverse[1][3] = source[0][0] * source[1][2] * source[2][3] -
                  source[0][0] * source[1][3] * source[2][2] -
                  source[1][0] * source[0][2] * source[2][3] +
                  source[1][0] * source[0][3] * source[2][2] +
                  source[2][0] * source[0][2] * source[1][3] -
                  source[2][0] * source[0][3] * source[1][2];

  inverse[2][3] = -source[0][0] * source[1][1] * source[2][3] +
                   source[0][0] * source[1][3] * source[2][1] +
                   source[1][0] * source[0][1] * source[2][3] -
                   source[1][0] * source[0][3] * source[2][1] -
                   source[2][0] * source[0][1] * source[1][3] +
                   source[2][0] * source[0][3] * source[1][1];

  inverse[3][3] = source[0][0] * source[1][1] * source[2][2] -
                  source[0][0] * source[1][2] * source[2][1] -
                  source[1][0] * source[0][1] * source[2][2] +
                  source[1][0] * source[0][2] * source[2][1] +
                  source[2][0] * source[0][1] * source[1][2] -
                  source[2][0] * source[0][2] * source[1][1];

  double determinant = source[0][0] * inverse[0][0] + source[0][1] * inverse[1][0] +
                       source[0][2] * inverse[2][0] + source[0][3] * inverse[3][0];

  if (determinant == 0) {
    return false;
  }

  inverse *= (1.0 / determinant);
  matrix = std::make_shared<Matrix<4, 4>>(inverse);

  return true;
}

}  // namespace keisan
