#ifndef LOVE_PHYSICS3D_BT_GHOSTOBJECT_H
#define LOVE_PHYSICS3D_BT_GHOSTOBJECT_H

#include "btBulletDynamicsCommon.h"
#include "Shape.h"
#include "common/Object.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class GhostObject : public Object {
public:
	static love::Type type;

	GhostObject(Shape *shape);

	void getTransform(btScalar *a16);

	void setTransform(btScalar *a16);
private:
	btPairCachingGhostObject *pair_caching_ghost_object;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_GHOSTOBJECT_H
