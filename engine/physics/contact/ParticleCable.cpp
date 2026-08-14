#include"engine/physics/contact/ParticleCable.h"
#include"engine/math/vector3.h"

namespace omni
{
  ParticleCable::ParticleCable(
    Particle* p1,
    Particle* p2,
    real maxLength,
    real restitution
  ) : mMaxLength(maxLength), mRestitution(restitution)
  {
    setParticles(p1, p2);
  }

  unsigned ParticleCable::addContact(ParticleContact* contact, unsigned limit) const {
    if(mParticle[0] == nullptr) return 0;
    if(mParticle[1] == nullptr) return 0;

    if(currentLength() <= mMaxLength) return 0;
    if(limit == 0) return 0; 


    Vector3 p0 = mParticle[0]->getPosition();
    Vector3 p1 = mParticle[1]->getPosition();

    Vector3 contactNormal = p0 - p1;
    contactNormal.normalize();

    real penetration = 0;

    penetration = currentLength() - mMaxLength;
    
    contact->mParticle[0] = mParticle[0];
    contact->mParticle[1] = mParticle[1];

    contact->mContactNormal = contactNormal;

    contact->mPenetration = penetration;

    contact->mRestitution = mRestitution;

    return 1;

  }
} // namespace omni
