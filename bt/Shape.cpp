#include "Shape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type Shape::type("btShape", &Object::type);

Shape::Shape(btCollisionShape *shape) :
	shape(shape) 
{

}

Shape::~Shape() {
	delete shape;
}

Shape::Type Shape::getType() const {
	switch( shape->getShapeType() ) {
		case BOX_SHAPE_PROXYTYPE:
			return SHAPE_BOX;
		default:
			return SHAPE_INVALID;
	}
}

void Shape::setMargin(btScalar margin) {
	shape->setMargin(margin);
}

} // bt
} // physics3d
} // love
