#include "BoxShape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type BoxShape::type("btBoxShape", &Shape::type);

BoxShape::BoxShape(const btVector3 &box_half_extents) :
	Shape(new btBoxShape(box_half_extents))
{

}

} // bt
} // physics3d
} // love