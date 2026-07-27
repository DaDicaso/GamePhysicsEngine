#include "engine/physics/force/ParticleBungee.h"
#include "engine/physics/particle/particle.h"

namespace omni
{
  ParticleBungee::ParticleBungee(const Vector3& anchor, real springConstant, real restLength)
    : mAnchor(anchor),
       mSpringConstant(springConstant),
       mRestLength(restLength)
  {
  }

  void ParticleBungee::updateForce(Particle* particle, real duration){
    Vector3 force = particle->getPosition() - mAnchor;

    real extension = force.magnitude() - mRestLength;

    if(extension <= 0.0f){
      return;
    }

    force.normalize();

    force *= -mSpringConstant * extension;

    particle->addForce(force);
  }

  const Vector3& ParticleBungee::getAnchorPosition() const{
    return mAnchor;
  }
} // namespace omni
