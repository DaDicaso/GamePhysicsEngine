#include "engine/physics/force/ParticleDrag.h"
#include "engine/math/vector3.h"
#include "engine/physics/particle/particle.h"

namespace omni
{
  ParticleDrag::ParticleDrag(const real k1, const real k2)
    : mK1(k1), mK2(k2)
  {
  }

  void ParticleDrag::updateForce(Particle* particle, real duration){
    Vector3 dragForce = particle->getVelocity();

    if(dragForce.squareMagnitude() == 0){
      return;
    }

    real speed = dragForce.magnitude();
    real dragCoeff = mK1 * speed;
    dragCoeff += mK2 * speed * speed;

    dragForce.normalize();

    dragForce *= -dragCoeff;

    particle->addForce(dragForce);
  }
} // namespace omni
