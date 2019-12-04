#include "ContactPoint.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type ContactPoint::type("btContactPoint", &Object::type);

ContactPoint::ContactPoint(const btManifoldPoint &point) :
	point(point)
{

}

btScalar ContactPoint::getDistance() const {
	return point.getDistance();
}
btScalar ContactPoint::getAppliedImpulse() const {
	return point.getAppliedImpulse();
}

const btVector3 &ContactPoint::getPositionA() const {
	return point.getPositionWorldOnA();
}
const btVector3 &ContactPoint::getPositionB() const {
	return point.getPositionWorldOnB();
}

} // bt
} // physics3d
} // love