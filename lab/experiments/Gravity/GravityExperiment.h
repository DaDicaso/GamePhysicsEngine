#pragma once

#include "lab/experiment.h"
#include "engine/physics/particle/particle.h"
#include "engine/physics/force/ParticleGravity.h"
#include "engine/physics/force/ParticleDrag.h"
#include "engine/physics/force/ParticleForceRegistry.h"

namespace omni{

  class GravityExperiment : public Experiment{
    public:

      GravityExperiment();
      ~GravityExperiment();

      void initialize() override;
      void update(float dt) override;
      void render(Renderer& renderer) override;
      void shutdown() override;

    private:
    
      Particle mParticle;

      ParticleGravity mGravity;
      ParticleDrag mDrag;

      ParticleForceRegistry mForceRegistry;
  };
}