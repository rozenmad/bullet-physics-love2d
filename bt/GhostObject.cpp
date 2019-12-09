#include "GhostObject.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type GhostObject::type("btGhostObject", &CollisionObject::type);

GhostObject::GhostObject(Shape *shape) :
	CollisionObject(create_bt_pair_caching_ghost_object(), shape)
{
	pair_caching_ghost_object->setCollisionShape(shape->getCollisionShape());
    pair_caching_ghost_object->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
}

btPairCachingGhostObject *GhostObject::create_bt_pair_caching_ghost_object() {
	pair_caching_ghost_object = new btPairCachingGhostObject();
	return pair_caching_ghost_object;
}

GhostObject::~GhostObject() {
	delete pair_caching_ghost_object;
}


} // bt
} // physics3d
} // love