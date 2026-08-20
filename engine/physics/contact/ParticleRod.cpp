#include"engine/physics/contact/ParticleRod.h"
#include<iostream>

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

    std::cout << "Entered Contact Method" <<std::endl;

    if(mParticle[0] == nullptr) {
      std::cout << "First particle is NULL" << std::endl;
      return 0;
    }
    if(mParticle[1] == nullptr){
      std::cout << "Second particle is NULL" << std::endl;
      return 0;
    }
    if(currentLength() == mLength){
      std::cout << "The length is fine constraint NOT needed" << std::endl;
      return 0;
    }
    if(limit == 0) {
      std::cout << "The contact limit is finished" << std::endl;
      return 0;
    }

    if(currentLength() < mLength){
      std::cout <<"Entered the Small condition" <<std::endl;
      Vector3 contactNormal = mParticle[0]->getPosition() - mParticle[1]->getPosition();

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

      std::cout << "entered the big condition" << std::endl;
      Vector3 contactNormal = mParticle[1]->getPosition() - mParticle[0]->getPosition();
      contactNormal.normalize();

      real penetration = currentLength() - mLength;

      contact->mContactNormal = contactNormal;
      contact->mPenetration = penetration;

      contact->mParticle[0] = mParticle[0];
      contact->mParticle[1] = mParticle[1];
      contact->mRestitution =0;
      return 1;
    }

    return 0;
  }
} // namespace omni
