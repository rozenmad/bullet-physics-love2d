#include "GhostObject.h"
#include "World.h"
#include "../love_luapi/Object.h"
#include "../love_luapi/runtime.h"
#include "../love_luapi/Reference.h"
#include "../love_luapi/StringMap.h"

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

void GhostObject::getOverlappingPairs(lua_State *L)
{
	Shape *shape = getCollisionShape();
	btConvexShape *convexShape = (btConvexShape*)shape->getCollisionShape();
	btVector3 minAabb, maxAabb;
	convexShape->getAabb(pair_caching_ghost_object->getWorldTransform(), minAabb, maxAabb);

	world->getBroadphase()->setAabb(pair_caching_ghost_object->getBroadphaseHandle(),
		minAabb,
		maxAabb,
		world->getDispatcher());



	world->getDispatcher()->dispatchAllCollisionPairs(pair_caching_ghost_object->getOverlappingPairCache(), world->getDispatchInfo(), world->getDispatcher());

	int pairCount = pair_caching_ghost_object->getOverlappingPairCache()->getNumOverlappingPairs();
	lua_createtable(L, pairCount, 0);
	btManifoldArray m_manifoldArray;
	//	btScalar maxPen = btScalar(0.0);
	for (int i = 0; i < pairCount; i++)
	{
		m_manifoldArray.resize(0);

		btBroadphasePair* collisionPair = &pair_caching_ghost_object->getOverlappingPairCache()->getOverlappingPairArray()[i];

		btCollisionObject* obj0 = static_cast<btCollisionObject*>(collisionPair->m_pProxy0->m_clientObject);
		btCollisionObject* obj1 = static_cast<btCollisionObject*>(collisionPair->m_pProxy1->m_clientObject);

		if ((obj0 && !obj0->hasContactResponse()) || (obj1 && !obj1->hasContactResponse()))
			continue;

		if (collisionPair->m_algorithm)
			collisionPair->m_algorithm->getAllContactManifolds(m_manifoldArray);

		int manifoldCount = m_manifoldArray.size();
		lua_createtable(L, manifoldCount, 0);

		for (int j = 0; j < manifoldCount; j++)
		{
			//ContactPair(m_manifoldArray[j]);
			//btScalar directionSign = manifold->getBody0() == pair_caching_ghost_object ? btScalar(-1.0) : btScalar(1.0);
		}
	}
}


} // bt
} // physics3d
} // love