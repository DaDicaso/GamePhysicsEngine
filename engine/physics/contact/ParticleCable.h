#pragma once

#include "engine/physics/contact/ParticleLink.h"

namespace omni
{
 class ParticleCable : public ParticleLink{

  public:

    ParticleCable(Particle* p1, Particle* p2, real maxLength, real restitution);

    virtual unsigned addContact(
      ParticleContact* contact,
      unsigned limit
    ) const override;


  private:
    real mMaxLength;
    real mRestitution;
 }; 
} // namespace omni
