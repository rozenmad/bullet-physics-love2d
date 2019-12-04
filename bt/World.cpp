#include "World.h"
#include "RigidBody.h"

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
			RigidBody *rbodyA = ((UserData*)obA->getUserPointer())->rbody;
			RigidBody *rbodyB = ((UserData*)obB->getUserPointer())->rbody;

			rbodyA->contact_callback.report(this, contactManifold, rbodyA, rbodyB);
			rbodyB->contact_callback.report(this, contactManifold, rbodyB, rbodyA);

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
	rbody->in_world = true;

	object_list[rbody] = this;
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
