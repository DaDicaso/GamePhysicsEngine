#pragma once

#include "engine/math/vector3.h"
#include "engine/physics/force/ParticleForceGenerator.h"

namespace omni
{
  class ParticleAnchoredSpring : public ParticleForceGenerator{
    public:

      ParticleAnchoredSpring(const Vector3& anchor, real springConstant, real restLength);

      void updateForce(Particle* particle, real duration) override;

      const Vector3& getAnchorPosition() const;
      
    private:
      
      Vector3 mAnchor;
      real mSpringConstant;
      real mRestLength;
    
  };
} // namespace omni
