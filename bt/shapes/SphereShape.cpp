#include "SphereShape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type SphereShape::type("btSphereShape", &Shape::type);

SphereShape::SphereShape(btScalar radius) :
	Shape(new btSphereShape(radius))
{

}

SphereShape::~SphereShape() {

}

} // bt
} // physics3d
} // love