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

      for(unsigned i =0; i < numContacts; ++i){
        
        real sepVel = contactArray[i].calculateSeparatingVelocity();

        if(sepVel < max && (sepVel < 0 || contactArray[i].mPenetration > 0)){
          max = sepVel;
          maxIndex = i;
        }
      }
      if(maxIndex == numContacts){
        break;
      }

      contactArray[maxIndex].resolve(duration);

      ++iterationsUsed;
    }
  }
  
} // namespace omni
