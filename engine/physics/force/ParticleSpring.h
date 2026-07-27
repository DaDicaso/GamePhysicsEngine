#pragma once

#include "engine/physics/force/ParticleForceGenerator.h"

namespace omni
{
  class ParticleSpring : public ParticleForceGenerator{

    public:

      ParticleSpring(Particle* other, real springConstant, real restLength); 

      void updateForce(Particle* particle, real duration) override;
    private:
      const real mSpringConstant;
      const real mRestLength;
      Particle* mOtherParticle;
      
  };
} // namespace omn
