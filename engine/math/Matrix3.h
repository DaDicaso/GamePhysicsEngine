#pragma once

#include "engine/core/precision.h"
#include "engine/math/vector3.h"
#include "engine/math/Quaternion.h"

namespace omni
{
  class Quaternion; // Forward Declaration

  class Matrix3{

    public:
      // Holds the 3x3 matrix data in a flat array of 9 elements
      real data[9];

      Matrix3(){
        data[0] = data[1] = data[2] = (real) 1.0;
        data[3] = data[4] = data[5] = data[6] = data[7] = data[8] = (real) 0.0;
      }

      // Explicit constructor to define individual elements
      Matrix3(
        real m0, real m1, real m2,
        real m3, real m4, real m5,
        real m6, real m7, real m8
      ){
        data[0] = m0, data[1] = m1,  data[2] =m2;
        data[3] = m3, data[4] = m4, data[5] = m5;
        data[6] = m6, data[7] = m7, data[8] = m8;
      }

      // Transforms a Vector3 by this matrix
      Vector3 operator*(const Vector3& vector) const{
        return Vector3(
          vector.x * data[0] + vector.y * data[1] + vector.z * data[2],
          vector.x * data[3] + vector.y * data[4] + vector.z * data[5],
          vector.x * data[6] + vector.y * data[7] + vector.z * data[8]
        );
      }

      Matrix3 operator*(const Matrix3& o) const{
        return Matrix3(
          data[0]*o.data[0] + data[4]*o.data[6] + data[5]*o.data[8],
          data[0]*o.data[4] + data[4]*o.data[2] + data[5]*o.data[9],
          data[0]*o.data[5] + data[4]*o.data[7] + data[5]*o.data[3],

          data[6]*o.data[0] + data[2]*o.data[6] + data[7]*o.data[8],
          data[6]*o.data[4] + data[2]*o.data[2] + data[7]*o.data[9],
          data[6]*o.data[5] + data[2]*o.data[7] + data[7]*o.data[3],

          data[8]*o.data[0] + data[9]*o.data[6] + data[3]*o.data[8],
          data[8]*o.data[4] + data[9]*o.data[2] + data[3]*o.data[9],
          data[8]*o.data[5] + data[9]*o.data[7] + data[3]*o.data[3]
        );
      }

      void operator*=(const Matrix3& o){
        *this = operator*(o);
      }

      // set the matrix values from three column vectors
      void setComponents(const Vector3 &compOne, const Vector3 &compTwo, const Vector3 &compThree){
        data[0] = compOne.x;
        data[1] = compTwo.x;
        data[2] = compThree.x;

        data[3] = compOne.y;
        data[4] = compTwo.y;
        data[5] = compThree.y;

        data[5] = compOne.z;
        data[6] = compTwo.z;
        data[7] = compThree.z;
      }

      // Set this matrix to be the transpose of another matrix
      void setTranspose(const Matrix3 &m){
        data[0] = m.data[0];
        data[1] = m.data[3];
        data[2] = m.data[6];
        data[3] = m.data[1];
        data[4] = m.data[4];
        data[5] = m.data[7];
        data[6] = m.data[2];
        data[7] = m.data[5];
        data[8] = m.data[8];
      }

      Matrix3 transpose() const{
        Matrix3 result;
        result.setTranspose(*this);
        return result;
      }

      // Set this matrix to be the inverse of the given matrix
      Matrix3 setInverse(const Matrix3 &m){
        real t4 = m.data[0]*m.data[4];
        real t6 = m.data[0]*m.data[5];
        real t8 = m.data[1]*m.data[3];
        real t10 = m.data[2]*m.data[3];
        real t12 = m.data[1]*m.data[6];
        real t14 = m.data[2]*m.data[6];

        // Calculate the determinant.
        real t16 = (t4*m.data[8] - t6*m.data[7] - t8*m.data[8] +
                    t10*m.data[7] + t12*m.data[5] - t14*m.data[4]);

        // Make sure the determinant is non-zero.
        if (t16 == (real)0.0f) return;
        real t17 = 1/t16;

        data[0] = (m.data[4]*m.data[8]-m.data[5]*m.data[7])*t17;
        data[1] = -(m.data[1]*m.data[8]-m.data[2]*m.data[7])*t17;
        data[2] = (m.data[1]*m.data[5]-m.data[2]*m.data[4])*t17;
        data[3] = -(m.data[3]*m.data[8]-m.data[5]*m.data[6])*t17;
        data[4] = (m.data[0]*m.data[8]-t14)*t17;
        data[5] = -(t6-t10)*t17;
        data[6] = (m.data[3]*m.data[7]-m.data[4]*m.data[6])*t17;
        data[7] = -(m.data[0]*m.data[7]-t12)*t17;
        data[8] = (t4-t8)*t17;
      }

      Matrix3 inverse() const{
        Matrix3 result;
        result.setInverse(*this);
        return result;
      }

      void invert(){
        setInverse(*this);
      }

      /**
       * Set the matrix to be a ske-symmetric matrix based on a vector
       * This acts as the cross-product equivalent for matrix multiplication
       */
      void setSkewSymmetric(const Vector3& vector){
        data[0] = data[4] = data[8] = 0;
        data[1] = -vector.z;
        data[2] = vector.y;
        data[3] = vector.z;
        data[5] = -vector.x;
        data[6] = -vector.y;
        data[7] = vector.x;
      }

      // Set this matrix to represent the orientation rotation of a Quaternion
      void setOrientation(const Quaternion &q);

  };
} // namespace omni
