#ifndef LOVE_PHYSICS3D_BT_CONTACTPOINTS_H
#define LOVE_PHYSICS3D_BT_CONTACTPOINTS_H

#include "common/Object.h"
#include "btBulletDynamicsCommon.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class ContactPoint : public Object {
public:
	static love::Type type;

	ContactPoint(const btManifoldPoint &point);
	virtual ~ContactPoint() {}

	btScalar getDistance() const;
	btScalar getAppliedImpulse() const;

	const btVector3 &getPositionA() const;
	const btVector3 &getPositionB() const;

private:
	btManifoldPoint point;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_CONTACTPOINTS_H
