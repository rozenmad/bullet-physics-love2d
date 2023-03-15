#ifndef LOVE_PHYSICS3D_BT_GHOSTOBJECT_H
#define LOVE_PHYSICS3D_BT_GHOSTOBJECT_H

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "shapes/Shape.h"
#include "CollisionObject.h"
#include "callback/KinematicCallback.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class GhostObject : public CollisionObject {
public:
	static love::Type type;

	GhostObject(Shape *shape);
	virtual ~GhostObject();

	btPairCachingGhostObject *getObject() {
		return pair_caching_ghost_object;
	}

	void convexSweepTest(Shape *shape, const btTransform &from, const btTransform &to,
		KinematicCallback *resultCallback,
		btScalar allowedCcdPenetration = 0.f
	) {
		pair_caching_ghost_object->convexSweepTest((btConvexShape*)(shape->getCollisionShape()), from, to, resultCallback->callback, allowedCcdPenetration);
	}

	void getOverlappingPairs(lua_State *L);
private:
	btPairCachingGhostObject *create_bt_pair_caching_ghost_object();
	
private:
	btPairCachingGhostObject *pair_caching_ghost_object;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_GHOSTOBJECT_H
