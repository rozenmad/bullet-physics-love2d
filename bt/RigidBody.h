#ifndef LOVE_PHYSICS3D_BT_RIGIDBODY_H
#define LOVE_PHYSICS3D_BT_RIGIDBODY_H

#include "common/Object.h"
#include "common/runtime.h"
#include "common/Reference.h"
#include "btBulletDynamicsCommon.h"

#include "Shape.h"
#include "CollisionObject.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class RigidBody;

class MotionState : public btMotionState {
public:
	MotionState(RigidBody *rbody, lua_State *L);

	void getWorldTransform(btTransform& t) const;
	void setWorldTransform(const btTransform& t);
	
private:
	RigidBody *rbody;
	Reference *reference;
	lua_State *L;
};

class RigidBody : public CollisionObject {
public:
	friend class World;
	friend class MotionState;

	static love::Type type;

	RigidBody(Shape *shape, float mass, lua_State *L);
	virtual ~RigidBody();

	void setDamping(btScalar linear, btScalar angular);

	void applyForce(btVector3 const &force, btVector3 const &rel_pos);

	void setAngularFactor(const btVector3 &factor);
	
	void setLinearFactor(const btVector3 &factor);

	void setKinematic(bool enable = true);

	const btVector3 &getLinearVelocity() const;
	void setLinearVelocity(btVector3 const &v);

private:
	btRigidBody *create_bt_rigid_body(Shape *shape, float mass, lua_State *L);

private:
	btRigidBody *rbody;
	btMotionState *motion_state;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_RIGIDBODY_H
