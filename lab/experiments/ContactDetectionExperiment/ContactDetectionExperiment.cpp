#include "lab/experiments/ContactDetectionExperiment/ContactDetectionExperiment.h"

#include "engine/debug/Colors.h"
#include "engine/renderer/renderer.h"

namespace omni
{
  ContactDetectionExperiment::ContactDetectionExperiment()
  : mResolver(100)
  {
  }

  void ContactDetectionExperiment::initialize(){
    mParticleA.setPosition(-5, -3, 0);
    mParticleB.setPosition(5, 3, 0);

    mParticleA.setVelocity(5, 3, 0);
    mParticleB.setVelocity(-5, -3, 0);
    
    mParticleA.setMass(1.0f);
    mParticleB.setMass(1.0f);

    mParticleA.setAcceleration(5, 3, 0);
    mParticleB.setAcceleration(-5, -3, 0);

    mParticleA.setDamping(0.99f);
    mParticleB.setDamping(0.99f);

    mCollisionDetector.clear();
    mCollisionDetector.addSphere(&mParticleA, 1.0f);
    mCollisionDetector.addSphere(&mParticleB, 1.0f);

  }

  void ContactDetectionExperiment::update(float dt){
    
    // Intergrate Particle Movement
    mParticleA.integrate(dt);
    mParticleB.integrate(dt);

    // Automate collision detection & contact Generation
    const unsigned MAX_CONTACT = 16;
    ParticleContact contactArray[MAX_CONTACT];

    // This dynamically performs narrow-phase checks and writes overlaps to contactArray
    unsigned usedContacts = mCollisionDetector.addContact(contactArray, MAX_CONTACT);

    // Resolve Constraints and Collisions
    if(usedContacts > 0){
      // Double the contacts count as a rule of thumb for iterations resolution limit
      mResolver.setIterations(usedContacts * 2);
      mResolver.resolveContacts(contactArray, usedContacts, dt);
    }

  }

  void ContactDetectionExperiment::render(Renderer &renderer){
    auto& debug = renderer.getDebugDraw();

    debug.point(
      mParticleA.getPosition(),
      Colors::White,
      15.0f
    );

    debug.point(
      mParticleB.getPosition(),
      Colors::White,
      15.0f
    );

    debug.sphere(
      debug,
      mParticleA.getPosition(),
      1.0f,
      Colors::Cyan
    );
    debug.sphere(
      debug,
      mParticleB.getPosition(),
      1.0f,
      Colors::Cyan
    );
  }

  void ContactDetectionExperiment::shutdown(){
  }
} // namespace omni
