#pragma once

#include "engine/core/precision.h"
#include <vector>

namespace omni{
  class Particle;
  class ParticleForceGenerator;
  
  class ParticleForceRegistry{
    
    public:
      void add(Particle* particle, ParticleForceGenerator* force);
      void remove(Particle* particle, ParticleForceGenerator* force);
      void clear();
      void updateForces(real duration);

    private:

      struct ParticleForceRegistration
      {
        Particle* particle;
        ParticleForceGenerator* forceGenerator;
      };
      std::vector<ParticleForceRegistration> mRegistrations;
  };

}