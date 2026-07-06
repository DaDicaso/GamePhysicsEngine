#pragma once

#include "engine/core/precision.h"

namespace omni{
  class Particle;

  class ParticleForceGenerator{
    public:
      
      virtual ~ParticleForceGenerator() = default;

      /**
       * Updates the force applied to the given particle
       */

      virtual void updateForce(Particle* particle, real duration) = 0;
  };
}

#include "engine/core/precision.h"

namespace omni{
  class Particle;

  class ParticleForceGenerator{
    public:
      
      virtual ~ParticleForceGenerator() = default;

      /**
       * Updates the force applied to the given particle
       */

      virtual void updateForce(Particle* particle, real duration) = 0;
  };
}