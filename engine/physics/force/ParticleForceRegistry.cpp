#include "engine/physics/force/ParticleForceRegistry.h"
#include "engine/physics/force/ParticleForceGenerator.h"
#include "engine/physics/particle/particle.h"

namespace omni
{
  void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* force){
    ParticleForceRegistration reg;
    reg.particle = particle;
    reg.forceGenerator = force;

    mRegistrations.push_back(reg);
  }

  void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* force){

    for(auto it = mRegistrations.begin(); it != mRegistrations.end(); ++it){
      if(it->particle == particle && it->forceGenerator == force){
        mRegistrations.erase(it);
        break;
      }
    }
  }

  void ParticleForceRegistry::clear(){
    mRegistrations.clear();
  }

  void ParticleForceRegistry::updateForces(real duration){
    for(auto& registration : mRegistrations){
      registration.forceGenerator->updateForce(
        registration.particle, duration
      );
    }
  }
} // namespace omni
                             