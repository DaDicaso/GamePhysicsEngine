#pragma once

#include "engine/physics/particle/particle.h"

namespace omni
{
  class ParticleContact{

    public:

      Particle* mParticle[2];
      
      real mRestitution;

      Vector3 mContactNormal;

      real mPenetration;


    public:

      void resolve(real duration);
      real calculateSeparatingVelocity() const;


    private:

      void resolveVelocity(real duration);

      void resolvePenetration(real duration);



    private:

      Vector3 mParticleMovement[2];
    // Grant access to resolver to update mParticleMovement and mPenetration
    friend class ParticleContactResolver;
  };
} // namespace omni
