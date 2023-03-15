#ifndef LOVE_PHYSICS3D_BT_RIGIDBODY_H
#define LOVE_PHYSICS3D_BT_RIGIDBODY_H

#include "../love_luapi/Object.h"
#include "../love_luapi/runtime.h"
#include "../love_luapi/Reference.h"
#include "btBulletDynamicsCommon.h"

#include "shapes/Shape.h"
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

	void applyGravity();

	void setDamping(btScalar linear, btScalar angular);

	void applyCentralForce(btVector3 const &force);
	void applyForce(btVector3 const &force, btVector3 const &rel_pos);

	void setAngularFactor(const btVector3 &factor);
	
	void setLinearFactor(const btVector3 &factor);

	void setKinematic(bool enable = true);

	void translate(const btVector3 &v);

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
