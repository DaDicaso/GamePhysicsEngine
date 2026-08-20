#pragma once

#include"engine/physics/contact/ParticleLink.h"

namespace omni
{
  class ParticleRod : public ParticleLink{

    public:

      ParticleRod(Particle* p1, Particle* p2, real length);

      unsigned addContact(
        ParticleContact* contact,
        unsigned limit
      ) const override;

    public:
      real mLength;
  };
} // namespace omni
