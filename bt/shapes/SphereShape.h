#ifndef LOVE_PHYSICS3D_BT_SPHERESHAPE_H
#define LOVE_PHYSICS3D_BT_SPHERESHAPE_H

#include "btBulletDynamicsCommon.h"
#include "Shape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class SphereShape : public Shape {
public:
	static love::Type type;

	SphereShape(btScalar radius);
	virtual ~SphereShape();
	
private:
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_SPHERESHAPE_H
