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
	virtual ~World();

	void update(float time_step, int max_sub_steps);
	void update(float time_step, int max_sub_steps, float fixed_time_step);

	int raycast(lua_State *L, const btVector3 &origin, const btVector3 &direction, float max_distance, unsigned mask);

	void addRigidBody(RigidBody *rbody);

	void addCharacterController(CharacterController *object);

	void removeRigidBody(CollisionObject *object);

	void removeCharacterController(CharacterController *object);

	btDispatcher *getDispatcher();

	love::Object *findObject(void *bt_collision_object) const;

	void attachObject(void *bt_collision_object, love::Object *object);
	void detachObject(void *bt_collision_object);

private:
	btBroadphaseInterface* m_broadphase;
	btCollisionDispatcher* m_dispatcher;
	btConstraintSolver* m_solver;
	btDefaultCollisionConfiguration* m_collisionConfiguration;
	btDiscreteDynamicsWorld* world;

	std::unordered_map<void*, love::Object*> object_list;

	std::unordered_map<void*, love::Object*> action_list;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS_BOX2D_WORLD_H
