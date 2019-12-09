#include "World.h"
#include "RigidBody.h"
#include "CollisionObject.h"
#include "CharacterController.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type World::type("btWorld", &Object::type);

World::World(float gx, float gy, float gz) 
{
	m_collisionConfiguration = new btDefaultCollisionConfiguration();

	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_broadphase = new btDbvtBroadphase();

	m_solver = new btSequentialImpulseConstraintSolver();

	world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
	world->setGravity(btVector3(gx, gy, gz));

	world->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
    world->setSynchronizeAllMotionStates(true);
}

World::~World() {
	for( auto &it: object_list ) {
		it.second->release();
	}
	object_list.clear();

	delete world;
	delete m_solver;
	delete m_broadphase;
	delete m_dispatcher;
	delete m_collisionConfiguration;
}

void World::update(float time_step, int max_sub_steps) {
	if( world ) {
		world->stepSimulation(time_step, max_sub_steps);
	}

	int manifolds_count = m_dispatcher->getNumManifolds();

	for( int i = 0; i < manifolds_count; i++ ) {
		btPersistentManifold* contactManifold = m_dispatcher->getManifoldByIndexInternal(i);

		const btCollisionObject* obA = contactManifold->getBody0();
		const btCollisionObject* obB = contactManifold->getBody1();

		int contacts = contactManifold->getNumContacts();
		if( contacts > 0 ) {
			CollisionObject *objA = ((UserData*)obA->getUserPointer())->obj;
			CollisionObject *objB = ((UserData*)obB->getUserPointer())->obj;

			objA->contact_callback.report(this, contactManifold, objA, objB);
			objB->contact_callback.report(this, contactManifold, objB, objA);

			/*for( int j = 0; j < contacts; j++ ) {
				btManifoldPoint& pt = contactManifold->getContactPoint(j);
				if( pt.getDistance() < 0.f ) {
					const btVector3& ptA = pt.getPositionWorldOnA();
					const btVector3& ptB = pt.getPositionWorldOnB();

					const btVector3& normalOnB = pt.m_normalWorldOnB;
				}
			}*/
		}
	}
}

void World::update(float time_step, int max_sub_steps, float fixed_time_step) {
	if( world ) {
		world->stepSimulation(time_step, max_sub_steps, fixed_time_step);
	}
}

int World::raycast(lua_State *L, const btVector3 &origin, const btVector3 &direction, float max_distance, unsigned mask) {
	btCollisionWorld::AllHitsRayResultCallback ray_callback(origin, origin + max_distance * direction);

	world->rayTest(ray_callback.m_rayFromWorld, ray_callback.m_rayToWorld, ray_callback);

	int size = ray_callback.m_collisionObjects.size();

	lua_createtable(L, size, 0);
	int table_index = lua_gettop(L);
	for( int i = 0; i < size; i++ ) {
        RaycastHit *hit = new RaycastHit(ray_callback, i, origin);
        luax_pushtype(L, hit);
        hit->release();
        lua_rawseti(L, table_index, i + 1);
    }
    return 1;
}

void World::addRigidBody(RigidBody *object) {
	object->world = this;
	world->addRigidBody(object->rbody);
	attachObject(object->collision_object, object);
	object->retain();
}

void World::addCharacterController(CharacterController *object) {
	GhostObject *ghost = object->getGhostObject();
	ghost->world = this;
	world->addCollisionObject(ghost->collision_object, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::AllFilter);
	attachObject(ghost->collision_object, ghost);
	ghost->retain();

    world->addAction(object->kinematic_character_controller);
    attachObject(object->kinematic_character_controller, object);
    object->retain();
}

void World::removeRigidBody(CollisionObject *object) {
	world->removeCollisionObject(object->collision_object);
	detachObject(object->collision_object);
	object->release();
}

void World::removeCharacterController(CharacterController *object) {
	world->removeAction(object->kinematic_character_controller);
	detachObject(object->kinematic_character_controller);
	object->release();
}

btDispatcher *World::getDispatcher() {
	return world->getDispatcher();
}

love::Object *World::findObject(void *rbody) const
{
	auto it = object_list.find(rbody);
	if (it != object_list.end())
		return it->second;
	else
		return nullptr;
}

void World::attachObject(void *bt_collision_object, love::Object *object) {
	object_list[bt_collision_object] = object;
}

void World::detachObject(void *bt_collision_object) {
	object_list.erase(bt_collision_object);
}

} // bt
} // physics3d
} // love
