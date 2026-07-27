#include "engine/physics/particle/particle.h"
#include "engine/physics/force/ParticleSpring.h"

namespace omni
{
  ParticleSpring::ParticleSpring(Particle* other, real springConstant, real restLength)
    : mOtherParticle(other), mSpringConstant(springConstant), mRestLength(restLength)
    {
    }
  
  void ParticleSpring::updateForce(Particle* particle, real duration){

    Vector3 force = particle->getPosition() - mOtherParticle->getPosition();

    real extention = force.magnitude() - mRestLength;

    force.normalize();
    force *= -mSpringConstant * extention;

    particle->addForce(force);
  }
} // namespace omni
