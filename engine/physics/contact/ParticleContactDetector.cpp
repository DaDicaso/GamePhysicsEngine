#include"engine/physics/contact/ParticleContactDetector.h"

namespace omni{
  
  ParticleContactDetector::ParticleContactDetector(real defaulteRestitution)
  : mDefaultRestitution(defaulteRestitution)
  {
  }

  void ParticleContactDetector::addSphere(Particle* particle, real radius){
    if(particle != nullptr){
      mSpheres.push_back({particle, radius});
    }
  }

  void ParticleContactDetector::clear(){
    mSpheres.clear();
  }

  unsigned ParticleContactDetector::addContact(ParticleContact* contact, unsigned limit) const{
    unsigned count = 0;
    size_t numSpheres = mSpheres.size();

    // Perform pairwise check to prevent checking self or duplicate pairs
    for(size_t i = 0; i < numSpheres; ++i){
      for(size_t j = i+1; j < numSpheres; ++j){
        if(count >= limit){
          return count; // Contact pool is full
        }

        const ParticleSphere& s0 = mSpheres[i];
        const ParticleSphere& s1 = mSpheres[j];

        // Calculate centre-to-centre midline vector
        Vector3 pos0 = s0.particle->getPosition();
        Vector3 pos1 = s1.particle->getPosition();
        Vector3 midline = pos0 - pos1;
        real distance = midline.magnitude();

        // Check for overlap: distance must be less than sum of radius
        real combinedRadii = s0.radius + s1.radius;

        if(distance > 0.0f && distance < combinedRadii){
          // Overlap detected! Fill in the ParticleContact details
          contact[count].mParticle[0] = s0.particle;
          contact[count].mParticle[1] = s1.particle;

          // Contact normal direction is p1 to p0
          // this ensures s0 moves in +normal and s1 moves in -normal direction
          contact[count].mContactNormal = midline/distance;

          // Penetration dept is the overlap distance
          contact[count].mPenetration = combinedRadii - distance;
          contact[count].mRestitution = mDefaultRestitution;

          count++;
        }
      }
    }
    return count;
  }
} // namespace omni
