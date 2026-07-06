#include "engine/physics/force/ParticleGravity.h"
#include "engine/physics/particle/particle.h"

namespace omni
{
  ParticleGravity::ParticleGravity(const Vector3& gravity) : mGravity(gravity) {}

  void ParticleGravity::updateForce(Particle* particle, real duration){

    if(!particle->hasFiniteMass()){
      return;
    }

    particle->addForce(mGravity * particle->getMass());
  }
} // namespace omni
