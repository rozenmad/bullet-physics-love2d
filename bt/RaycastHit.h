#ifndef LOVE_PHYSICS3D_BT_RAYCASTHIT_H
#define LOVE_PHYSICS3D_BT_RAYCASTHIT_H

#include "common/Object.h"
#include "btBulletDynamicsCommon.h"
#include "CollisionObject.h"

#include <vector>

namespace love
{
namespace physics3d
{
namespace bt
{

class RaycastHit : public Object {
public:
	static love::Type type;

	RaycastHit(btCollisionWorld::AllHitsRayResultCallback &ray_callback, int index, btVector3 const &origin);
	virtual ~RaycastHit();

public:
	btVector3 position;
    btVector3 normal;

    btScalar distance;
    btScalar hit_fraction;
    
    CollisionObject *object; // maybe StrongRef
};

typedef std::vector<RaycastHit> RaycastHitArray;

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_RAYCASTHIT_H
