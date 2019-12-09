#ifndef LOVE_PHYSICS3D_BT_CAPSULESHAPE_H
#define LOVE_PHYSICS3D_BT_CAPSULESHAPE_H

#include "btBulletDynamicsCommon.h"
#include "Shape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class CapsuleShape : public Shape {
public:
	static love::Type type;

	CapsuleShape(btScalar radius, btScalar height);
	virtual ~CapsuleShape();
	
private:
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_CAPSULESHAPE_H
