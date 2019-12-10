#ifndef LOVE_PHYSICS3D_BT_CONTACTPAIR_H
#define LOVE_PHYSICS3D_BT_CONTACTPAIR_H

#include "btBulletDynamicsCommon.h"
#include <unordered_map>

#include "ContactPoint.h"
#include "CollisionObject.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class ContactPair
{
public:
	friend class World;

	ContactPair();
	ContactPair(btPersistentManifold* manifold, int timestamp);

	size_t hash();

	void updateContactPoints();

	void releaseContactPoints();

	size_t getContactPointsCount() const {
		return contact_points.size();
	}
	ContactPoint *getContactPoint(int index) const {
		return contact_points[index];
	}

	CollisionObject *getBodyA() {
		return bodyA;
	}
	CollisionObject *getBodyB() {
		return bodyB;
	}

private:
	// boost::hash_combine
	static void hash_combine(size_t & seed, void* const& v) {
		seed ^= std::hash<void*>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}
	
	std::vector<ContactPoint*> contact_points;
	btPersistentManifold* manifold;
	CollisionObject *bodyA;
	CollisionObject *bodyB;
	int timestamp;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_CONTACTPAIR_H
