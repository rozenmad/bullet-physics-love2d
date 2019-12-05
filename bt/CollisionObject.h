#ifndef LOVE_PHYSICS3D_BT_COLLISIONOBJECT_H
#define LOVE_PHYSICS3D_BT_COLLISIONOBJECT_H

#include "common/Object.h"
#include "common/runtime.h"
#include "common/Reference.h"
#include "btBulletDynamicsCommon.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class CollisionObject;

struct UserData
{
	CollisionObject *obj = nullptr;
	Reference *reference = nullptr;
};

class CollisionObject : public Object {
public:
	friend class World;

	static love::Type type;

	struct ContactCallback {
		Reference *reference = nullptr;
		lua_State *L = nullptr;
		int report(World *world, btPersistentManifold *manifold, CollisionObject *a, CollisionObject *b);
	};

	CollisionObject(btCollisionObject *collision_object);
	virtual ~CollisionObject();

	void getTransform(btScalar *a16) const;
	void setTransform(btScalar *a16);

	int setUserData(lua_State *L);
	int getUserData(lua_State *L);

	int setCallback(lua_State *L);

protected:
	btCollisionObject *collision_object;
	World *world;

	UserData *userdata;

	ContactCallback contact_callback;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_COLLISIONOBJECT_H
