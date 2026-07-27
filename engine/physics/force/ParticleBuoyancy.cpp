#include "engine/physics/force/ParticleBuoyancy.h"
#include "engine/physics/particle/particle.h"

namespace omni
{
  ParticleBuoyancy::ParticleBuoyancy(real maxDepth, real volume, real waterHeight, real liquidDensity)
    : mMaxDepth(maxDepth),
      mVolume(volume),
      mWaterHeight(waterHeight),
      mLiquidDensity(liquidDensity)
  {
  }

  void ParticleBuoyancy::updateForce(Particle* particle, real duration){
    real depth = particle->getPosition().y;
    
    // Completely out of water
    if(depth >= mWaterHeight + mMaxDepth){
      return;
    }

    Vector3 force(0, 0, 0);

    // Completely submerged
    if(depth <= mWaterHeight - mMaxDepth){
      force.y = mLiquidDensity * mVolume;
      particle->addForce(force);
      return;
    }

    // Partially Submergerd

    force.y = mLiquidDensity * mVolume * (depth - mMaxDepth - mWaterHeight) / (2.0f * mMaxDepth);

    particle->addForce(force);
  }
} // namespace omni
