#include "engine/math/Matrix3.h"

namespace omni
{
  void Matrix3::setOrientation(const Quaternion &q){
    //Evaluate directly from algebraic simplifications of the quaternion
    data[0] = 1 - (2 * q.j * q.j + 2*q.k * q.k);
    data[1] = 2 * q.i * q.j + 2 * q.k * q.r;
    data[2] = 2 * q.i * q.k - 2 * q.j * q.r;
    data[3] = 2 * q.i * q.j - 2 * q.k * q.r;
    data[4] = 1 - (2 * q.i * q.i + 2 * q.k * q.k);
    data[5] = 2 * q.j * q.k + 2 * q.i * q.r;
    data[6] = 2 * q.i * q.k + 2 * q.j * q.r;
    data[7] = 2 * q.j * q.k - 2 * q.i * q.r;
    data[8] = 1 - (2 * q.i * q.i + 2 * q.j * q.j);
  }
} // namespace omni
 