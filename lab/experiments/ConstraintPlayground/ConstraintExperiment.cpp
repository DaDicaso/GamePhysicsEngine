#include"lab/experiments/ConstraintPlayground/ConstraintExperiment.h"

#include "engine/renderer/renderer.h"
#include"engine/debug/Colors.h"

#include<iostream>

namespace omni
{
  ConstraintExperiment::ConstraintExperiment()
    : mContactResolver(100),
    mRod1(&mParticleA, &mParticleB, mRodLength),  
    mRod2(&mParticleB, &mParticleC, mRodLength),
    mRod3(&mParticleC, &mParticleD, mRodLength),
    mRod4(&mParticleD, &mParticleE, mRodLength),
    mRod5(&mParticleE, &mParticleF, mRodLength),
    mRod6(&mParticleF, &mParticleA, mRodLength)
  {
  }

  void ConstraintExperiment::initialize(){
    // Centered at (0, 0, 0)
    mParticleA.setPosition(5.0f,   0.0f,    0.0f);
    mParticleB.setPosition(2.5f,   4.33f,   0.0f);  // 5 * sin(60 deg) = 4.33
    mParticleC.setPosition(-2.5f,  4.33f,   0.0f);
    mParticleD.setPosition(-5.0f,  0.0f,    0.0f);
    mParticleE.setPosition(-2.5f,  -4.33f,  0.0f);
    mParticleF.setPosition(2.5f,   -4.33f,  0.0f);


    mParticleA.setMass(1.0f);
    mParticleB.setMass(1.0f);
    mParticleC.setMass(1.0f);
    mParticleD.setMass(1.0f);
    mParticleE.setMass(1.0f);
    mParticleF.setMass(1.0f);

    mParticleA.setAcceleration(Vector3(10.0f, 2, 0.0f));
    mParticleB.setAcceleration(Vector3(0.0f, 0.0f, 0.0f));
    mParticleC.setAcceleration(Vector3(0.0f, 0.0f, 0.0f));
    mParticleD.setAcceleration(Vector3(-10.0f, -1, 0.0f));
    mParticleE.setAcceleration(Vector3(0.0f, 0.0f, 0.0f));
    mParticleF.setAcceleration(Vector3(0.0f, 0.0f, 0.0f));

    mParticleA.setVelocity(Vector3(0, 0, 0));
    mParticleB.setVelocity(Vector3(0, 0, 0));
    mParticleC.setVelocity(Vector3(0, 0, 0));
    mParticleD.setVelocity(Vector3(0, 0, 0));
    mParticleE.setVelocity(Vector3(0, 0, 0));
    mParticleF.setVelocity(Vector3(0, 0, 0));

    mParticleA.setDamping(0.99);
    mParticleB.setDamping(0.99);
    mParticleC.setDamping(0.99);
    mParticleD.setDamping(0.99);
    mParticleE.setDamping(0.99);
    mParticleF.setDamping(0.99);

  }

  void ConstraintExperiment::update(float dt){
    mParticleA.integrate(dt);
    mParticleB.integrate(dt);
    mParticleC.integrate(dt);
    mParticleD.integrate(dt);
    mParticleE.integrate(dt);
    mParticleF.integrate(dt);

    unsigned usedContacts = 0;

    usedContacts += mRod1.addContact(&mContactPool[usedContacts], MAX_CONTACT - usedContacts);
    usedContacts += mRod2.addContact(&mContactPool[usedContacts], MAX_CONTACT - usedContacts);
    usedContacts += mRod3.addContact(&mContactPool[usedContacts], MAX_CONTACT - usedContacts);
    usedContacts += mRod4.addContact(&mContactPool[usedContacts], MAX_CONTACT - usedContacts);
    usedContacts += mRod5.addContact(&mContactPool[usedContacts], MAX_CONTACT - usedContacts);
    usedContacts += mRod6.addContact(&mContactPool[usedContacts], MAX_CONTACT - usedContacts);

    real length = mRod1.currentLength();

    // resolve all active violations
    if(usedContacts > 0){
      mContactResolver.resolveContacts(
        mContactPool,
        usedContacts,
        dt
      );
    }

    // std::cout << "Current Length: " << length << "\n" << "A velocity: " << mParticleA.getVelocity().y << "\n" << "B velocity: " << mParticleB.getVelocity().y << "\nUsedContacts: " << usedContacts << "\nPenetration: " << mContact.mPenetration << "\nRodLength: " << mRodLength << "\n" << std::endl;
  }

  void ConstraintExperiment::render(Renderer& renderer){
    auto& debug = renderer.getDebugDraw();

    // Render all the points
    debug.point(
      mParticleA.getPosition(),
      Colors::Red
    );
    debug.point(
      mParticleB.getPosition(),
      Colors::White
    );
    debug.point(
      mParticleC.getPosition(),
      Colors::White
    );
    debug.point(
      mParticleD.getPosition(),
      Colors::Red
    );
    debug.point(
      mParticleE.getPosition(),
      Colors::White
    );
    debug.point(
      mParticleF.getPosition(),
      Colors::White
    );

    debug.line(
      mParticleA.getPosition(),
      mParticleB.getPosition(),
      Colors::Blue,
      10
    );
    debug.line(
      mParticleB.getPosition(),
      mParticleC.getPosition(),
      Colors::Blue,
      10
    );
    debug.line(
      mParticleC.getPosition(),
      mParticleD.getPosition(),
      Colors::Blue,
      10
    );
    debug.line(
      mParticleD.getPosition(),
      mParticleE.getPosition(),
      Colors::Blue,
      10
    );
    debug.line(
      mParticleE.getPosition(),
      mParticleF.getPosition(),
      Colors::Blue,
      10
    );
    debug.line(
      mParticleF.getPosition(),
      mParticleA.getPosition(),
      Colors::Blue,
      10
    );
  }

  void ConstraintExperiment::shutdown(){
    
  }

} // namespace omni
