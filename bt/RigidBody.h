#ifndef LOVE_PHYSICS3D_BT_RIGIDBODY_H
#define LOVE_PHYSICS3D_BT_RIGIDBODY_H

#include "common/Object.h"
#include "common/runtime.h"
#include "common/Reference.h"
#include "btBulletDynamicsCommon.h"

#include "World.h"
#include "Shape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

struct UserData
{
	RigidBody *rbody = nullptr;
	Reference *reference = nullptr;
};

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

class RigidBody : public Object {
public:
	friend class World;
	friend class MotionState;

	struct ContactCallback {
		Reference *reference = nullptr;
		lua_State *L = nullptr;
		int report(World *world, btPersistentManifold *manifold, RigidBody *a, RigidBody *b);
	};

	static love::Type type;

	RigidBody(Shape *shape, float mass, lua_State *L);
	virtual ~RigidBody();

	void getTransform(btScalar *a16);

	void setTransform(btScalar *a16);

	void setDamping(btScalar linear, btScalar angular);

	void setRestitution(float factor);
	void applyForce(btVector3 const &force, btVector3 const &rel_pos);

	void setAngularFactor(const btVector3 &factor);
	
	void setLinearFactor(const btVector3 &factor);

	void setKinematic(bool enable = true);

	void activate(bool forceActivation = false);

	const btVector3 &getLinearVelocity() const;
	void setLinearVelocity(btVector3 const &v);

	int setUserData(lua_State *L);
	int getUserData(lua_State *L);

	int setCallback(lua_State *L);

private:
	btRigidBody* rbody;
	btMotionState *motion_state;
	World *world;

	ContactCallback contact_callback;

	StrongRef<Shape> shape_reference;

	UserData *userdata;

	bool in_world;
};

}
}
}

#endif // LOVE_PHYSICS3D_BT_RIGIDBODY_H
