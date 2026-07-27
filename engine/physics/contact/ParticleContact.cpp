#include "engine/physics/contact/ParticleContact.h"
#include "engine/math/vector3.h"

namespace omni
{
  void ParticleContact::resolve(real duration){
    resolveVelocity(duration);
    resolvePenetration(duration);
  }

  real ParticleContact::calculateSeparatingVelocity() const{
    Vector3 relativeVelocity = mParticle[0]->getVelocity();
  
    if(mParticle[1] != nullptr){
      relativeVelocity -= mParticle[1]->getVelocity();
    }  

    return relativeVelocity.dot(mContactNormal);
  }

  void ParticleContact::resolveVelocity(real duration){
    real seperatingVelocity = calculateSeparatingVelocity();

    // NO need to resolve if particles are already seperating
    if(seperatingVelocity > 0){
      return;
    }

    // Calculate the new separating veclocity.
    real newSeperatingVelocity = -seperatingVelocity * mRestitution;
    
    // Check the velocity build-up due to acceleration only.
    Vector3 accCausedVelocity = mParticle[0]->getAcceleration();

    if(mParticle[1] != nullptr){
      accCausedVelocity -= mParticle[1]->getAcceleration();
    }

    real accCausedSepVelocity = accCausedVelocity.dot(mContactNormal) * duration;

    if(accCausedSepVelocity < 0){
      newSeperatingVelocity += mRestitution * accCausedSepVelocity;

      if(newSeperatingVelocity < 0){
        newSeperatingVelocity = 0;
      }
    }

    real deltaVelocity = newSeperatingVelocity - seperatingVelocity;

    real totalInverseMass = mParticle[0]->getInverseMass();

    if(mParticle[1] != nullptr){
      totalInverseMass += mParticle[1]->getInverseMass();
    }
    
    if(totalInverseMass <= 0){
      return;
    }

    real impulse = deltaVelocity / totalInverseMass;

    Vector3 impulsePerIMass = mContactNormal * impulse;

    mParticle[0]->setVelocity(mParticle[0]->getVelocity() + impulsePerIMass * mParticle[0]->getInverseMass());

    if(mParticle[1] != nullptr){
      mParticle[1]->setVelocity(mParticle[1]->getVelocity() - impulsePerIMass * mParticle[1] ->getInverseMass());
    }
  }

  void ParticleContact::resolvePenetration(real duration){
    if(mPenetration <= 0){
      return;
    }

    real totalInverseMass = mParticle[0]->getInverseMass();

    if(mParticle[1] != nullptr){
      totalInverseMass += mParticle[1]->getInverseMass();
    }

    if(totalInverseMass <= 0){
      return;
    }

    Vector3 movePerIMass = mContactNormal * (mPenetration / totalInverseMass);

    mParticleMovement[0] = movePerIMass * mParticle[0]->getInverseMass();

    if(mParticle[1] != nullptr){
      mParticleMovement[1] = -movePerIMass * mParticle[1]->getInverseMass();
    }
    else{
      mParticleMovement[1].clear();
    }

    mParticle[0]->setPosition(mParticle[0]->getPosition() + mParticleMovement[0]);

    if(mParticle[1] != nullptr){
      mParticle[1]->setPosition(mParticle[1]->getPosition() + mParticleMovement[1]);
    }
  }

} // namespace omni