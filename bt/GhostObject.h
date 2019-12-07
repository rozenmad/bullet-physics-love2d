#ifndef LOVE_PHYSICS3D_BT_GHOSTOBJECT_H
#define LOVE_PHYSICS3D_BT_GHOSTOBJECT_H

#include "btBulletDynamicsCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "Shape.h"
#include "CollisionObject.h"

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

	btPairCachingGhostObject *getObject() {
		return pair_caching_ghost_object;
	}

private:
	btPairCachingGhostObject *create_bt_pair_caching_ghost_object();
	
private:
	btPairCachingGhostObject *pair_caching_ghost_object;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_GHOSTOBJECT_H
