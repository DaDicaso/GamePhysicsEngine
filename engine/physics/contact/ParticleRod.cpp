#include"engine/physics/contact/ParticleRod.h"

namespace omni
{
  ParticleRod::ParticleRod(
    Particle* p1,
    Particle* p2,
    real length
  ): mLength(length)
  {
    setParticles(p1, p2);
  }

  unsigned ParticleRod::addContact(
    ParticleContact* contact, unsigned limit
  ) const{

    if(!mParticle[0]) return 0;
    if(!mParticle[1]) return 0;
    if(currentLength() == mLength) return 0;
    if(limit == 0) return 0;

    if(currentLength() < mLength){
      Vector3 contactNormal = mParticle[1]->getPosition() - mParticle[0]->getPosition();

      contactNormal.normalize();

      real penetration = mLength - currentLength();

      contact->mPenetration = penetration;
      contact->mContactNormal = contactNormal;

      contact->mParticle[0] = mParticle[0];
      contact->mParticle[1] = mParticle[1];
      contact->mRestitution =0;
      return 1;
    }

    if(currentLength() > mLength){
      Vector3 contactNormal = mParticle[0]->getPosition() - mParticle[1]->getPosition();
      contactNormal.normalize();

      real penetration = currentLength() - mLength;

      contact->mContactNormal = contactNormal;
      contact->mPenetration = penetration;

      contact->mParticle[0] = mParticle[0];
      contact->mParticle[1] = mParticle[1];
      contact->mRestitution =0;
      return 1;
    }
  }
} // namespace omni
