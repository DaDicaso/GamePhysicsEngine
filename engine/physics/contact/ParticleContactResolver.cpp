#include "engine/physics/contact/ParticleContactResolver.h"

namespace omni
{
  ParticleContactResolver::ParticleContactResolver(unsigned iterations)
    : mIterations(iterations)
  {
  }

  void ParticleContactResolver::setIterations(unsigned iterations){
    mIterations = iterations;
  }

  void ParticleContactResolver::resolveContacts(ParticleContact* contactArray, unsigned numContacts, real duration){
    
    unsigned iterationsUsed = 0;

    while(iterationsUsed < mIterations){
      real max = std::numeric_limits<real>::max();
      unsigned maxIndex = numContacts;

      // Find the contact with the most severe violation (lowest separating velocity)
      for(unsigned i =0; i < numContacts; ++i){
        
        real sepVel = contactArray[i].calculateSeparatingVelocity();

        if(sepVel < max && (sepVel < 0 || contactArray[i].mPenetration > 0)){
          max = sepVel;
          maxIndex = i;
        }
      }
      // is there is no violation the no need to change anything
      if(maxIndex == numContacts){
        break;
      }

      // Keep reference to the contact before resolving it
      Particle* p0 = contactArray[maxIndex].mParticle[0];
      Particle* p1 = contactArray[maxIndex].mParticle[1];

      // resolve the most violated contact
      contactArray[maxIndex].resolve(duration);

      // The selected contact has now been resolved
      contactArray[maxIndex].mPenetration = 0;

      // Update the penetration of every other contact affected by the particle movement
      for(unsigned i = 0; i < numContacts; ++i){
        if(i == maxIndex){
          continue;
        }

        ParticleContact& contact = contactArray[i];

        // Particle 0 of the resolved contact moved
        if(p0 != nullptr){
          if(contact.mParticle[0] == p0){
            contact.mPenetration -= contactArray[maxIndex].mParticleMovement[0].dot(contact.mContactNormal);
          }
          else if(contact.mParticle[1] == p0){
            contact.mPenetration += contactArray[maxIndex].mParticleMovement[0].dot(contact.mContactNormal);
          }
        }

        // Particle 1 of the resolved contact moved
        if(p1 != nullptr){
          if(contact.mParticle[0] == p1){
            contact.mPenetration -= contactArray[maxIndex].mParticleMovement[1].dot(contact.mContactNormal);
          }
          else if(contact.mParticle[1] == p1){
            contact.mPenetration += contactArray[maxIndex].mParticleMovement[1].dot(contact.mContactNormal);
          }
        }
      }

      ++iterationsUsed;
    }
  }
  
} // namespace omni
