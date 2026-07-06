#pragma once

#include "engine/physics/force/ParticleForceGenerator.h"

namespace omni
{
  class ParticleDrag : public ParticleForceGenerator{
    public:
      
      explicit ParticleDrag(real k1, real k2);

      void updateForce(Particle* particle, real duration) override;

    private:

      const real mK1;
      const real mK2;

  };
} // namespace omni
