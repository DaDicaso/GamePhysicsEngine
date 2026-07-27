#pragma once

#include "engine/physics/contact/ParticleContact.h"

namespace omni
{
  class ParticleContactResolver{
    public:

      explicit ParticleContactResolver(unsigned iterations);

      void setIterations(unsigned iterations);

      void resolveContacts(
        ParticleContact* contactArray,
        unsigned numContacts,
        real duration
      );

    private:

      unsigned mIterations;
  };
} // namespace omni
