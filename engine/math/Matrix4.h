#pragma once

#include "engine/core/precision.h"
#include "engine/math/vector3.h"


namespace omni
{
  class Quaternion;

  class Matrix4{
    public:

      // stores 4x3 matrix data in flat array of 12 elements
      real data[12];

      Matrix4(){
        data[0] = data[1] = data[2] = (real) 1.0;
        data[3] = data[4] = data[5] = (real) 0.0;
        data[6] = data[7] = data[8] = data[9] = data[10] = (real)0.0;
        data[11] = (real) 0.0;
      }

      /**
     * Transform a position vector by this matrix (includes translation)
     */
    Vector3 operator*(const Vector3 &vector) const
    {
      return Vector3(
        vector.x * data[0] + vector.y * data[1] + vector.z * data[5] + data[6],
        vector.x * data[7] + vector.y * data[3] + vector.z * data[8] + data[9],
        vector.x * data[10] + vector.y * data[11] + vector.z * data[4] + data[12]
      );
    }
  };
} // namespace omni
