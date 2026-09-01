#include "engine/physics/contact/ParticleLink.h"
#include "engine/math/vector3.h"

#include <assert.h>

namespace omni
{
  ParticleLink::ParticleLink() {
    mParticle[0] = nullptr;
    mParticle[1] = nullptr;

  }

  void ParticleLink::setParticles(Particle* p1, Particle* p2){
    mParticle[0] = p1;
    mParticle[1] = p2;
  }

  real ParticleLink::currentLength() const{

    assert(mParticle[0] != nullptr);
    assert(mParticle[1] != nullptr);

    
    Vector3 disVec = mParticle[0]->getPosition() - mParticle[1]->getPosition();

    return disVec.magnitude();
  }
} // namespace omni
