#pragma once
#include "engine/physics/force/ParticleForceGenerator.h"
#include "engine/math/vector3.h"

namespace omni
{
  class ParticleGravity : public ParticleForceGenerator{
    
    public:
    
    explicit ParticleGravity(const Vector3& gravity);
    
    void updateForce(Particle* particle, real duration) override;


    private:

      const Vector3 mGravity;
  };
} // namespace omni
