#include "lab/experiments/ContactResolution/ContactResolutionExperiment.h"

#include "engine/debug/Colors.h"
#include "engine/renderer/renderer.h"

namespace omni
{
  ContactResolutionExperiment::ContactResolutionExperiment()
  : mResolver(100)
  {
  }

  void ContactResolutionExperiment::initialize(){
    mParticleA.setPosition(-2.0f, 0.0f, 0.0f);
    mParticleB.setPosition(2.0f, 0.0f, 0.0f);

    mParticleA.setVelocity(3.0f, 0.0f, 0.0f);
    mParticleB.setVelocity(-3.0f, 0.0f, 0.0f);

    mParticleA.setAcceleration(0.0f, 0.0f, 0.0f);
    mParticleB.setAcceleration(0.0f, -9.86f, 0.0f);

    mParticleA.setInverseMass(1.0f);
    mParticleB.setInverseMass(1.0f);

    mParticleA.setDamping(0.99f);
    mParticleB.setDamping(0.99f);

    mParticleA.clearAccumulator();
    mParticleB.clearAccumulator();
  }

  void ContactResolutionExperiment::update(real dt){
    mParticleA.integrate(dt);
    mParticleB.integrate(dt);

    Vector3 seperation = mParticleB.getPosition() - mParticleA.getPosition();

    real distance = seperation.magnitude();

    constexpr real particleRadius = 0.5f;
    constexpr real collisionDistance = particleRadius * 2.0f;

    if(distance < collisionDistance){
      mContact.mParticle[0] = &mParticleA;
      mContact.mParticle[1] = &mParticleB;

      if(distance > 0.0001f){
        mContact.mContactNormal = -seperation / distance;
      }
      else{
        mContact.mContactNormal = Vector3(1.0f, 0.0f, 0.0f);
      }

      mContact.mPenetration = collisionDistance - distance;
      mContact.mRestitution = 1.0f;

      mResolver.resolveContacts(&mContact, 1, dt);
    }
  }

  void ContactResolutionExperiment::render(Renderer& renderer){
    
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

    debug.line(
      mParticleA.getPosition(),
      mParticleB.getPosition(),
      Colors::Yellow,
      2.0f
    );

    Vector3 midPoint = (mParticleA.getPosition() + mParticleB.getPosition()) * 0.5f;

    debug.line(
      midPoint,
      midPoint + mContact.mContactNormal,
      Colors::Red,
      3.0f
    );

    constexpr real velocityScale = 0.25f;

    debug.line(
      mParticleA.getPosition(),
      mParticleA.getPosition() +mParticleA.getVelocity() * velocityScale,
      Colors::Green,
      2.0f
    );
    debug.line(
      mParticleB.getPosition(),
      mParticleB.getPosition() +mParticleB.getVelocity() * velocityScale,
      Colors::Green,
      2.0f
    );
    
  }

  void ContactResolutionExperiment::shutdown()
  {
  }
} // namespace omni
