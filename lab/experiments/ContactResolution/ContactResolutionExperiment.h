#pragma once

#include "lab/experiment.h"

#include "engine/physics/particle/particle.h"
#include "engine/physics/contact/ParticleContact.h"
#include "engine/physics/contact/ParticleContactResolver.h"

namespace omni
{
  class ContactResolutionExperiment : public Experiment{
    public:

      ContactResolutionExperiment();

      void initialize() override;
      void update(float dt) override;
      void render(Renderer& renderer) override;
      void shutdown() override;

    private:

      Particle mParticleA;
      Particle mParticleB;

      ParticleContact mContact;

      ParticleContactResolver mResolver;

  };
} // namespace omni
