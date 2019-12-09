#ifndef LOVE_PHYSICS3D_BT_SHAPE_H
#define LOVE_PHYSICS3D_BT_SHAPE_H

#include "common/Object.h"
#include "btBulletDynamicsCommon.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class Shape : public Object {
public:
	friend class RigidBody;

	enum Type
	{
		SHAPE_INVALID,
		SHAPE_BOX,
		SHAPE_MAX_ENUM
	};

	static love::Type type;
	
	Shape(btCollisionShape *shape);
	virtual ~Shape();

	btCollisionShape *getCollisionShape() {
		return shape;
	}

	void setMargin(btScalar margin);

	Type getType() const;

protected:
	btCollisionShape *shape;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_SHAPE_H
