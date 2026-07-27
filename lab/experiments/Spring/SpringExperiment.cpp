#include<iostream>

#include "lab/experiments/Spring/SpringExperiment.h"

#include "engine/renderer/renderer.h"


namespace omni
{
  SpringExperiment::SpringExperiment()
    : mSpringAB(&mParticleB, mSpringConstant, mRestLength),
      mSpringBA(&mParticleA, mSpringConstant, mRestLength),
      mAnchoredSpring(Vector3(0, 5, 0), mSpringConstant, mRestLength),
      mBungee(Vector3(0,-1,0), mSpringConstant, mRestLength),
      mBuoyancy(1.0f, 1.0f, 0.0f, 100.0f),
      mGravity(Vector3(0.0f, -9.8f, 0.0f)),
      mDragA(0.1f, 0.01f),
      mDragB(0.1f, 0.01f),
      mDragC(0.1f, 0.01f),
      mDragD(0.1f, 0.01f),
      mDragE(0.1f, 0.01f)
  {
  }

  SpringExperiment::~SpringExperiment(){

  }

  void SpringExperiment::initialize(){

    mParticleA.setPosition(-2, 0, 0);
    mParticleB.setPosition(2, 0, 0);
    mParticleC.setPosition(0, 0, 0);
    mParticleD.setPosition(0, 5, 0);
    mParticleE.setPosition(0, 0, 0);

    mParticleA.setVelocity(0, 0, 0);
    mParticleB.setVelocity(0, 0, 0);
    mParticleC.setVelocity(0, 0, 0);
    mParticleD.setVelocity(0, 0, 0);
    mParticleE.setVelocity(0, 0, 0);

    mParticleA.setAcceleration(0, 0, 0);
    mParticleB.setAcceleration(0, 0, 0);
    mParticleC.setAcceleration(0, 0, 0);
    mParticleD.setAcceleration(0, 0, 0);
    mParticleE.setAcceleration(0, 0, 0);

    mParticleA.setMass(1.0f);
    mParticleB.setMass(1.0f);
    mParticleC.setMass(1.0f);
    mParticleD.setMass(1.0f);
    mParticleE.setMass(1.0f);

    mParticleA.setDamping(0.99f);
    mParticleB.setDamping(0.99f);
    mParticleC.setDamping(0.99f);
    mParticleD.setDamping(0.99f);
    mParticleE.setDamping(0.99f);
    
    mForceRegistry.add(&mParticleA, &mSpringAB);
    mForceRegistry.add(&mParticleB, &mSpringBA);
    mForceRegistry.add(&mParticleC, &mAnchoredSpring);
    mForceRegistry.add(&mParticleD, &mBungee);
    mForceRegistry.add(&mParticleE, &mBuoyancy);
    mForceRegistry.add(&mParticleE, &mGravity);
    mForceRegistry.add(&mParticleA, &mDragA);
    mForceRegistry.add(&mParticleB, &mDragB);
    mForceRegistry.add(&mParticleC, &mDragC);
    mForceRegistry.add(&mParticleD, &mDragD);
  }

  void SpringExperiment::update(float dt){
    mForceRegistry.updateForces(dt);
    mParticleA.integrate(dt);
    mParticleB.integrate(dt);
    mParticleC.integrate(dt);
    mParticleD.integrate(dt);
    mParticleE.integrate(dt);
  }

  void SpringExperiment::render(Renderer& renderer){

    renderer.drawPoint(
      mParticleA.getPosition()
    );
    renderer.drawPoint(
      mParticleB.getPosition()
    );
    renderer.drawPoint(
      mParticleC.getPosition()
    );
    renderer.drawPoint(
      mParticleD.getPosition()
    );
    renderer.drawPoint(
      mParticleE.getPosition()
    );

    renderer.drawLine(mParticleA.getPosition(), mParticleB.getPosition());

    renderer.drawLine(mParticleC.getPosition(), mAnchoredSpring.getAnchorPosition());

    renderer.drawLine(mParticleD.getPosition(), mBungee.getAnchorPosition());

    renderer.getDebugDraw().line(
      Vector3(-5.0f, 5.0f, 0.0f),
      Vector3(5.0f, 5.0f, 0.0f),
      Colors::Red,
      3.0f
    );
    renderer.getDebugDraw().line(
      Vector3(-5.0f, -5.0f, 0.0f),
      Vector3(5.0f, -5.0f, 0.0f),
      Colors::Green,
      3.0f
    );
    renderer.getDebugDraw().line(
      Vector3(-5.0f, 0.0f, 0.0f),
      Vector3(5.0f, 0.0f, 0.0f),
      Colors::Blue,
      3.0f
    );

    renderer.getDebugDraw().point(
      Vector3(0.0f, 0.0f, 0.0f),
      Colors::Yellow,
      20.0f
    );
  }

  void SpringExperiment::shutdown(){

  }
} // namespace omni
