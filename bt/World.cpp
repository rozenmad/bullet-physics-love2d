#include "World.h"
#include "RigidBody.h"
#include "CollisionObject.h"
#include "CharacterController.h"
#include "ContactPair.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type World::type("btWorld", &Object::type);

World::World(float gx, float gy, float gz) :
	timestamp_sync(0)
{
	m_collisionConfiguration = new btDefaultCollisionConfiguration();

	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);
	m_broadphase = new btDbvtBroadphase();

	m_solver = new btSequentialImpulseConstraintSolver();

	world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
	world->setGravity(btVector3(gx, gy, gz));

	ghost_pair_callback = new btGhostPairCallback();
	world->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(ghost_pair_callback);
    world->setSynchronizeAllMotionStates(true);
}

World::~World() {
	for( auto it = contact_pair_list.begin(); it != contact_pair_list.end(); it++ ) {
		it->second.releaseContactPoints();
	}
	contact_pair_list.clear();

	for( auto &it: object_list ) {
		removeRigidBody(it.second);
	}
	for( auto &it: action_list ) {
		removeCharacterController(it.second);
	}
	object_list.clear();
	action_list.clear();

	delete ghost_pair_callback;
	ghost_pair_callback = nullptr;
	delete world;
	world = nullptr;
	delete m_solver;
	m_solver = nullptr;
	delete m_broadphase;
	m_broadphase = nullptr;
	delete m_dispatcher;
	m_dispatcher = nullptr;
	delete m_collisionConfiguration;
	m_collisionConfiguration = nullptr;
}

void World::update(float time_step, int max_sub_steps) {
	if( world ) {
		world->stepSimulation(time_step, max_sub_steps);
		updateContactList();
	}
}

void World::update(float time_step, int max_sub_steps, float fixed_time_step) {
	if( world ) {
		world->stepSimulation(time_step, max_sub_steps, fixed_time_step);
		updateContactList();
	}
}

void World::updateContactList() {
	int manifolds_count = m_dispatcher->getNumManifolds();

	timestamp_sync++;
	for( int i = 0; i < manifolds_count; i++ ) {
		btPersistentManifold* contact_manifold = m_dispatcher->getManifoldByIndexInternal(i);

		if( contact_manifold->getNumContacts() <= 0 ) {
			continue;
		} 

		ContactPair pair(contact_manifold, timestamp_sync);
		pair.updateContactPoints();

		size_t pair_hash = pair.hash();

		if( contact_pair_list.find(pair_hash) == contact_pair_list.end() ) {
			// begin
			pair.bodyA->contact_beg.report(this, pair);
			pair.bodyB->contact_beg.report(this, pair, true);
		} else {
			pair.releaseContactPoints();
		}

		{ 	// ongoing
			pair.bodyA->contact_ong.report(this, pair);
			pair.bodyB->contact_ong.report(this, pair, true);
		}

		contact_pair_list[pair_hash] = pair;
	}

	for( auto it = contact_pair_list.begin(); it != contact_pair_list.end(); ) {
		ContactPair &pair = it->second;
	   	if( pair.timestamp < timestamp_sync ) {
	   		pair.bodyA->contact_end.report(this, pair);
			pair.bodyB->contact_end.report(this, pair, true);

			pair.releaseContactPoints();
			it = contact_pair_list.erase(it);
			continue;
	   	}
	   	it++;
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
	object_list[object->collision_object] = object;
	object->world = this;
	world->addRigidBody(object->rbody);
	object->retain();
}

void World::addCharacterController(CharacterController *object) {
	GhostObject *ghost = object->getGhostObject();
	ghost->world = this;
	world->addCollisionObject(ghost->collision_object, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::AllFilter);

	action_list[object->kinematic_character_controller] = object;
    world->addAction(object->kinematic_character_controller);
    object->retain();
}

void World::removeRigidBody(CollisionObject *object) {
	object_list.erase(object->collision_object);
	world->removeCollisionObject(object->collision_object);
	object->release();
}

void World::removeCharacterController(CharacterController *object) {
	GhostObject *ghost = object->getGhostObject();
	world->removeCollisionObject(ghost->collision_object);

	action_list.erase(object->kinematic_character_controller);
	world->removeAction(object->kinematic_character_controller);
	object->release();
}

btDispatcher *World::getDispatcher() {
	return world->getDispatcher();
}

} // bt
} // physics3d
} // love
