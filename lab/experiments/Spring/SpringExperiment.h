#pragma once

#include "lab/experiment.h"
#include "engine/physics/particle/particle.h"
#include "engine/physics/force/ParticleSpring.h"
#include "engine/physics/force/ParticleGravity.h"
#include "engine/physics/force/ParticleDrag.h"
#include "engine/physics/force/ParticleForceRegistry.h"
#include "engine/physics/force/ParticleAnchoredSpring.h"
#include "engine/physics/force/ParticleBungee.h"
#include "engine/physics/force/ParticleBuoyancy.h"

#include "engine/debug/DebugDraw.h"

namespace omni{

  class SpringExperiment : public Experiment{
    public:

      SpringExperiment();
      ~SpringExperiment();

      void initialize() override;
      void update(float dt) override;
      void render(Renderer& renderer) override;
      void shutdown() override;

    private:
    
      static constexpr real mSpringConstant = 20.0f;
      static constexpr real mRestLength = 3.5f;

      Particle mParticleA;
      Particle mParticleB;
      Particle mParticleC;
      Particle mParticleD;
      Particle mParticleE;

      ParticleSpring mSpringAB;
      ParticleSpring mSpringBA;

      ParticleAnchoredSpring mAnchoredSpring;

      ParticleBungee mBungee;

      ParticleBuoyancy mBuoyancy;

      ParticleGravity mGravity;

      ParticleDrag mDragA;
      ParticleDrag mDragB;
      ParticleDrag mDragC;
      ParticleDrag mDragD;
      ParticleDrag mDragE;

      ParticleForceRegistry mForceRegistry;

  };
}