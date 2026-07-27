#pragma once

#include "engine/physics/force/ParticleForceGenerator.h"
#include "engine/math/vector3.h"

namespace omni
{
  class ParticleBungee : public ParticleForceGenerator{

    public:

      ParticleBungee(const Vector3& anchor, real springConstant, real restLength);
      void updateForce(Particle * particle, real duration) override;
      const Vector3& getAnchorPosition() const;

    private:

      Vector3 mAnchor;
      const real mSpringConstant;
      const real mRestLength;
  };
} // namespace omni
