#include "RigidBody.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type RigidBody::type("btRigidBody", &CollisionObject::type);

MotionState::MotionState(RigidBody *rbody, lua_State *L) :
	rbody(rbody),
	reference(new Reference(L)),
	L(L)
{

}

void MotionState::getWorldTransform(btTransform& t) const {
	if( rbody->world ) {
		reference->push(L);
		int idx = lua_gettop(L);
		btScalar a16[16];
		for( int i = 0; i < 16; i++ ) {
			lua_rawgeti(L, idx, i+1);
			a16[i] = (float)luaL_checknumber(L, -1);
			lua_pop(L, 1);
		}
		t.setFromOpenGLMatrix(a16);
	}
}
void MotionState::setWorldTransform(const btTransform& t) {
	if( rbody->world ) {
		reference->push(L);
		int idx = lua_gettop(L);
		btScalar a16[16];
		t.getOpenGLMatrix(a16);
		for( int i = 0; i < 16; i++ ) {
			lua_pushnumber(L, a16[i]);
			lua_rawseti(L, idx, i+1);
		}
	}
}

btRigidBody *RigidBody::create_bt_rigid_body(Shape *shape, float mass, lua_State *L) {
	btCollisionShape *bt_shape = shape->shape;
	btVector3 local_inertia(0, 0, 0);
	if( mass != 0.f ) {
		bt_shape->calculateLocalInertia(mass, local_inertia);
	}

	motion_state = new MotionState(this, L);

	btRigidBody::btRigidBodyConstructionInfo c_info(mass, motion_state, bt_shape, local_inertia);
	rbody = new btRigidBody(c_info);
	return rbody;
}

RigidBody::RigidBody(Shape *shape, float mass, lua_State *L) :
	CollisionObject(create_bt_rigid_body(shape, mass, L), shape)
{
}

RigidBody::~RigidBody()
{
	delete rbody;
	delete motion_state;
}

void RigidBody::setDamping(btScalar linear, btScalar angular) {
	rbody->setDamping(linear, angular);
}

void RigidBody::applyForce(btVector3 const &force, btVector3 const &rel_pos) {
	rbody->applyForce(force, rel_pos);
}

void RigidBody::setAngularFactor(const btVector3 &factor) {
	rbody->setAngularFactor(factor);
}

void RigidBody::setLinearFactor(const btVector3 &factor) {
	rbody->setLinearFactor(factor);
}

void RigidBody::setKinematic(bool enable) {
	int flags = rbody->getCollisionFlags();
	if( enable ) {
	    rbody->setCollisionFlags(flags | btCollisionObject::CF_KINEMATIC_OBJECT);
	} else {
		rbody->setCollisionFlags(flags &~btCollisionObject::CF_KINEMATIC_OBJECT);
	}
    rbody->forceActivationState(enable ? DISABLE_DEACTIVATION : ISLAND_SLEEPING);
}

const btVector3 &RigidBody::getLinearVelocity() const {
	return rbody->getLinearVelocity();
}

void RigidBody::setLinearVelocity(btVector3 const &v) {
	rbody->setLinearVelocity(v);
}

} // bt
} // physics3d
} // love
