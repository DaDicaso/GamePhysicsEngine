#pragma once

#include "engine/physics/contact/ParticleContactGenerator.h"
#include<vector>

namespace omni
{

  // Lightweight representation of a physical sphere wrapping an active particle
  struct ParticleSphere{
    Particle* particle;
    real radius;
  };


  /**
   * Automated contact Generator that performs narrow-phase sphere to sphere collision checks between all registered particles
   */
  class ParticleContactDetector : public ParticleContactGenerator{
    private:

      real mDefaultRestitution;
      std::vector<ParticleSphere> mSpheres;

    public:

      // Create a collision detector with configurable default restitution
      explicit ParticleContactDetector(real defaultRestitution = 0.5f);

      // Registers a particle sphere with a given collision radius
      void addSphere(Particle* particle, real radius);

      // Clear all registered spheres from the detector
      void clear();

      // Dynamically perform narrow-phase checks on all registered spheres and writes generated contacts to the pool
      unsigned addContact(ParticleContact* contact, unsigned limit) const override;
  };
} // namespace omni
