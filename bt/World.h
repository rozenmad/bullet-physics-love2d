#ifndef LOVE_PHYSICS3D_BT_WORLD_H
#define LOVE_PHYSICS3D_BT_WORLD_H

#include "../love_luapi/Object.h"
#include "../love_luapi/runtime.h"
#include "btBulletDynamicsCommon.h"
#include "BulletDynamics/Character/btKinematicCharacterController.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"
#include "RaycastHit.h"

#include <unordered_map>
#include <utility>

namespace love
{
namespace physics3d
{
namespace bt
{

class RigidBody;
class CollisionObject;
class CharacterController;
class ContactPair;
typedef btCollisionWorld::ContactResultCallback ContactResultCallback;

class World : public Object {
public:
	static love::Type type;

	World(float gx, float gy, float gz);
	virtual ~World();

	void update(float time_step, int max_sub_steps);
	void update(float time_step, int max_sub_steps, float fixed_time_step);

	int contactTest(CollisionObject *object, lua_State *L);

	int raycast(lua_State *L, const btVector3 &origin, const btVector3 &direction, float max_distance, unsigned mask);

	void addRigidBody(RigidBody *rbody);

	void addCollisionObject(CollisionObject *object);

	void addCharacterController(CharacterController *object);

	void removeRigidBody(CollisionObject *object);

	void removeCharacterController(CharacterController *object);

	btDispatcher *getDispatcher();
	btDispatcherInfo &getDispatchInfo() {
		return world->getDispatchInfo();
	}

	btBroadphaseInterface *getBroadphase() {
		return m_broadphase;
	} 

private:
	void updateContactList();

private:
	btBroadphaseInterface* m_broadphase;
	btCollisionDispatcher* m_dispatcher;
	btConstraintSolver* m_solver;
	btDefaultCollisionConfiguration* m_collisionConfiguration;
	btDiscreteDynamicsWorld* world;
	btGhostPairCallback *ghost_pair_callback;

	std::unordered_map<void*, CollisionObject*> object_list;
	std::unordered_map<void*, CharacterController*> action_list;

	std::unordered_map<size_t, ContactPair> contact_pair_list;

	int timestamp_sync;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS_BOX2D_WORLD_H
