#pragma once

#include "engine/physics/particle/particle.h"
#include "engine/physics/contact/ParticleContact.h"

namespace omni
{
  class ParticleLink{
    
    public:

      ParticleLink();

      real currentLength() const;

      void setParticles(Particle* p1, Particle* p2);

      virtual unsigned addContact(
        ParticleContact* contact, 
        unsigned limit
      ) const = 0;
      
      Particle* mParticle[2];
      
  };
} // namespace omni
