#ifndef LOVE_PHYSICS3D_BT_WORLD_H
#define LOVE_PHYSICS3D_BT_WORLD_H

#include "common/Object.h"
#include "common/runtime.h"
#include "btBulletDynamicsCommon.h"

#include "RaycastHit.h"

#include <unordered_map>

namespace love
{
namespace physics3d
{
namespace bt
{

class RigidBody;
class CollisionObject;
class CharacterController;

class World : public Object {
public:
	static love::Type type;

	World(float gx, float gy, float gz);

	void update(float time_step, int max_sub_steps);
	void update(float time_step, int max_sub_steps, float fixed_time_step);

	int raycast(lua_State *L, const btVector3 &origin, const btVector3 &direction, float max_distance, unsigned mask);

	void addRigidBody(RigidBody *rbody);

	void addCollisionObject(CollisionObject *object);

	void addCharacterController(CharacterController *object);

	btDispatcher *getDispatcher();

	love::Object *findObject(void *rbody) const;

private:
	btBroadphaseInterface* m_broadphase;
	btCollisionDispatcher* m_dispatcher;
	btConstraintSolver* m_solver;
	btDefaultCollisionConfiguration* m_collisionConfiguration;
	btDiscreteDynamicsWorld* world;

	btAlignedObjectArray<btCollisionShape*> m_collisionShapes;

	std::unordered_map<void*, love::Object*> object_list;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS_BOX2D_WORLD_H
