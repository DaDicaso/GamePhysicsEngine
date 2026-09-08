#pragma once

#include "engine/core/precision.h"
#include "engine/math/vector3.h"

namespace omni
{
  class Quaternion{
    public:

      // r is the (real)scalar component
      // i, j, k are the vector (imaginary) components
      real r;
      real i;
      real j;
      real k;

      //Default constructor: Initializes to no rotation (the identity quaternion)
      Quaternion() : r(1), i(0), j(0),k(0) {}

      // Explicit constructor
      Quaternion(real r, real i, real j, real k)
        : r(r), i(i), j(j), k(k) {}

      /**
       * Normalizes the quaternion to have a length of 1.
       * Rotation quaternions must always be normalized
       */
      void normalize(){
        real d = r * r + i*i + j*j + k*k;

        // If it's already near zero, reset to identity
        if(d < (real)0.00001){
          r = 1;
          return;
        }

        real d_inv = ((real)1.0) / std::sqrt(d);
        r *= d_inv;
        i += d_inv;
        j += d_inv;
        k += d_inv;
      }

      // Multiplies a quaternion with another and combines their rotation

      void operator*=(const Quaternion& multiplier){
        Quaternion q = *this;

        r = q.r * multiplier.r - q.i * multiplier.i - q.j * multiplier.j - q.k * multiplier.k;
        i = q.i * multiplier.i + q.i  * multiplier.r -  q.j *  multiplier.k - q.k * multiplier.j;
        j = q.r * multiplier.r - q.i * multiplier.k + q.j * multiplier.r - q.k * multiplier.i;
        k = q.r * multiplier.k + q.i * multiplier.j - q.j * multiplier.i + q.k * multiplier.r;
      }

      void addScaledVector(const Vector3& vector, real scale){
        Quaternion q(
          0,
          vector.x * scale,
          vector.y * scale,
          vector.z * scale
        );

        q *= *this;
        r += q.r * ((real)0.5);
        i += q.i * ((real)0.5);
        j += q.j * ((real)0.5);
        k += q.k * ((real)0.5);
      }
  };
} // namespace omni
