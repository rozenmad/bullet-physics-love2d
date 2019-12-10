#include "ContactPair.h"

namespace love
{
namespace physics3d
{
namespace bt
{

ContactPair::ContactPair() :
	manifold(nullptr),
	bodyA(nullptr),
	bodyB(nullptr),
	timestamp(0)
{

}

ContactPair::ContactPair(btPersistentManifold* manifold, int timestamp) :
	manifold(manifold),
	bodyA( ((UserData*)manifold->getBody0()->getUserPointer())->obj ),
	bodyB( ((UserData*)manifold->getBody1()->getUserPointer())->obj ),
	timestamp(timestamp)
{

}

size_t ContactPair::hash() {
	size_t seed = 0;
	hash_combine(seed, bodyA);
	hash_combine(seed, bodyB);
	return seed;
}

void ContactPair::updateContactPoints() {
	int contacts = manifold->getNumContacts();
	for( int i = 0; i < contacts; i++ ) {
		contact_points.push_back(new ContactPoint(manifold->getContactPoint(i)));
	}
}

void ContactPair::releaseContactPoints() {
	for( auto &point : contact_points ) {
		point->release();
	}
	contact_points.clear();
}

} // bt
} // physics3d
} // love
