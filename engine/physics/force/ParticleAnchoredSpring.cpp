#include "engine/physics/force/ParticleAnchoredSpring.h"
#include "engine/physics/particle/particle.h"

namespace omni
{
  ParticleAnchoredSpring::ParticleAnchoredSpring(const Vector3& anchor, real springConstant, real restLength)
    : mAnchor(anchor),
      mSpringConstant(springConstant),
      mRestLength(restLength)
  {
  }

  void ParticleAnchoredSpring::updateForce(Particle* particle, real duration){
    Vector3 force = particle->getPosition() - mAnchor;

    real extension = force.magnitude() - mRestLength;

    if(force.squareMagnitude() == 0.0f){
      return;
    }

    force.normalize();
    force *= -mSpringConstant * extension;

    particle->addForce(force);
  }

  const Vector3& ParticleAnchoredSpring::getAnchorPosition() const{
    return mAnchor;
  }
} // namespace omni
