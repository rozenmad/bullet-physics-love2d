#include "CapsuleShape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type CapsuleShape::type("btCapsuleShape", &Shape::type);

CapsuleShape::CapsuleShape(btScalar radius, btScalar height) :
	Shape(new btCapsuleShape(radius, height))
{

}

} // bt
} // physics3d
} // love