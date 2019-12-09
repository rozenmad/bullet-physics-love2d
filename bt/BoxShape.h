#ifndef LOVE_PHYSICS3D_BT_BOXSHAPE_H
#define LOVE_PHYSICS3D_BT_BOXSHAPE_H

#include "btBulletDynamicsCommon.h"
#include "Shape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class BoxShape : public Shape {
public:
	static love::Type type;

	BoxShape(const btVector3 &box_half_extents);
	virtual ~BoxShape();
private:
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_BOXSHAPE_H
