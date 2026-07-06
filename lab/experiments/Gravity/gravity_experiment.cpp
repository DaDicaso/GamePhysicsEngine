#include<iostream>

#include "lab/experiments/Gravity/gravity_experiment.h"

#include "engine/renderer/renderer.h"

namespace omni
{
  GravityExperiment::GravityExperiment()
    : mGravity(Vector3(0.0f, -9.81f, 0.0f)){

  }

  GravityExperiment::~GravityExperiment(){

  }

  void GravityExperiment::initialize(){

    //std::cout << "Particle address is initialized: " << &mParticle << std::endl;
    mParticle.setPosition(-10.0f, 0.0f, 0.0f);

    mParticle.setVelocity(10.0f, 10.0f, 0.0f);

   // mParticle.setAcceleration(0.0f, 0.0f, 0.0f);
   
   mParticle.setMass(1.0f);
   
   mParticle.setDamping(0.999f);

   mForceRegistry.add(&mParticle, &mGravity);
  }

  void GravityExperiment::update(float dt){
    mForceRegistry.updateForces(dt);
    mParticle.integrate(dt);
    //std::cout << "Particle address in update: " << &mParticle << std::endl;

    //std::cout << mParticle.getPosition().y << std::endl;
  }

  void GravityExperiment::render(Renderer& renderer){

    renderer.drawPoint(
      mParticle.getPosition()
    );
  }

  void GravityExperiment::shutdown(){

  }
} // namespace omni
