#pragma once

#include "lab/experiment.h"

#include "engine/physics/particle/particle.h"
#include"engine/physics/contact/ParticleContact.h"
#include"engine/physics/contact/ParticleRod.h"
#include"engine/physics/contact/ParticleCable.h"
#include"engine/physics/contact/ParticleContactResolver.h"
#include "engine/physics/contact/ParticleContactDetector.h"


namespace omni
{
  class ConstraintExperiment : public Experiment{

    protected:

      const real mRodLength = 5.0f;
      const real mMaxCableLength = 4;
      const real mRestitution = 0.5f;

    public:

      ConstraintExperiment();

      void initialize() override;
      void update(float dt) override;
      void render(Renderer& renderer) override;
      void shutdown() override;

    private:

      Particle mParticleA;
      Particle mParticleB;
      Particle mParticleC;
      Particle mParticleD;
      Particle mParticleE;
      Particle mParticleF;

      // Replace the single mContact with a pool of contacts
      static constexpr unsigned MAX_CONTACT = 6;
      ParticleContact mContactPool[MAX_CONTACT];

      ParticleContactResolver mContactResolver;

      ParticleRod mRod1;
      ParticleRod mRod2;
      ParticleRod mRod3;
      ParticleRod mRod4;
      ParticleRod mRod5;
      ParticleRod mRod6 ;
  };
} // namespace omni
