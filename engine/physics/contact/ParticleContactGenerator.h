#pragma once

#include"engine/physics/particle/particle.h"
#include"engine/physics/contact/ParticleContactResolver.h"

namespace omni
{
  class ParticleContactGenerator{
    public:

      virtual ~ParticleContactGenerator() = default;

      /**
       * Inpects the physical state and writes generated contacts to the pool
       */
      virtual unsigned addContact(
        ParticleContact* contact,
        unsigned limit
      ) const = 0;
  };
} // namespace omni
