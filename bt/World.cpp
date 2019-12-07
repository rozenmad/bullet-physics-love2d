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
	//m_collisionConfiguration->setConvexConvexMultipointIterations();
	m_dispatcher = new btCollisionDispatcher(m_collisionConfiguration);

	m_broadphase = new btDbvtBroadphase();
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver();
	m_solver = solver;

	world = new btDiscreteDynamicsWorld(m_dispatcher, m_broadphase, m_solver, m_collisionConfiguration);
	world->setGravity(btVector3(gx, gy, gz));

	world->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
	//world->getDispatchInfo().m_useContinuous = true;
    //world->getSolverInfo().m_splitImpulse = false;
    world->setSynchronizeAllMotionStates(true);
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

void World::addRigidBody(RigidBody *rbody) {
	rbody->world = this;
	world->addRigidBody(rbody->rbody);
}

void World::addCollisionObject(CollisionObject *object) {
	object->world = this;
	world->addCollisionObject(object->collision_object);
}

void World::addCharacterController(CharacterController *object) {
	btPairCachingGhostObject *ghost_object = object->getGhostObject();

	world->addCollisionObject(ghost_object, btBroadphaseProxy::CharacterFilter, btBroadphaseProxy::AllFilter);
    world->addAction(object->kinematic_character_controller);
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

} // bt
} // physics3d
} // love
