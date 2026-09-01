#pragma once

#include "lab/experiment.h"

#include "engine/physics/particle/particle.h"
#include "engine/physics/contact/ParticleContact.h"
#include "engine/physics/contact/ParticleContactResolver.h"
#include "engine/physics/contact/ParticleContactDetector.h"
#include "engine/physics/force/ParticleForceRegistry.h"

namespace omni
{
  class ContactDetectionExperiment : public Experiment{
    public:
      ContactDetectionExperiment();

      void initialize() override;
      void update(float dt) override;
      void render(Renderer& renderer) override;
      void shutdown() override;

    private:

      Particle mParticleA;
      Particle mParticleB;

      ParticleContactResolver mResolver;
      ParticleContactDetector mCollisionDetector;

      ParticleForceRegistry mForceRegistry;
  };
} // namespace omni
