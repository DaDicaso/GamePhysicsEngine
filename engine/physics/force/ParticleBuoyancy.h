#pragma once

#include "engine/math/vector3.h"
#include "engine/physics/force/ParticleForceGenerator.h"

namespace omni
{
  class ParticleBuoyancy : public ParticleForceGenerator{

    public:

      ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity = 1000.0f);
      void updateForce(Particle* particle, real duration) override;

    private:

      const real mMaxDepth;
      const real mVolume;
      const real mWaterHeight;
      const real mLiquidDensity;
  };
} // namespace omnie
