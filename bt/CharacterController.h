#ifndef LOVE_PHYSICS3D_BT_CHARACTERCONTROLLER_H
#define LOVE_PHYSICS3D_BT_CHARACTERCONTROLLER_H

#include "../love_luapi/Object.h"

#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "GhostObject.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class CharacterController : public Object
{
public:
	friend class World;

    static love::Type type;
    
    CharacterController(GhostObject *ghost_object, btScalar step_height, btVector3 const &up);
    virtual ~CharacterController();

    void setJumpSpeed(btScalar jumpSpeed);
    btScalar getJumpSpeed() const;

    void jump(const btVector3 &v = btVector3(0, 0, 0));

    void applyImpulse(const btVector3 &v);

   	void setWalkDirection(const btVector3 &direction);

    void setGravity(const btVector3 &gravity);

    void setUp(const btVector3 &up);

    void setMaxJumpHeight(btScalar value);

    void setMaxPenetrationDepth(btScalar value);

    void setVelocityForTimeInterval(const btVector3 &velocity, btScalar timeInterval);

    void setStepHeight(btScalar h);
    btScalar getStepHeight() const;

    btScalar getMaxPenetrationDepth() const;

    GhostObject *getGhostObject();

    bool onGround() const;

private:
    btKinematicCharacterController* kinematic_character_controller;

    StrongRef<GhostObject> ghost_object_reference;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_CHARACTERCONTROLLER_H
