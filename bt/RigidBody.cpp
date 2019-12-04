#include "RigidBody.h"
#include "ContactPoint.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type RigidBody::type("btRigidBody", &Object::type);

MotionState::MotionState(RigidBody *rbody, lua_State *L) :
	rbody(rbody),
	reference(new Reference(L)),
	L(L)
{
}

void MotionState::getWorldTransform(btTransform& t) const {
	if( rbody->in_world ) {
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
	if( rbody->in_world ) {
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

int RigidBody::ContactCallback::report(World *world, btPersistentManifold *manifold, RigidBody *a, RigidBody *b) {
	if( reference != nullptr && L != nullptr )
	{
		reference->push(L);
		int contacts = manifold->getNumContacts();
		lua_createtable(L, contacts, 0);
		int table_index = lua_gettop(L);
		for( int i = 0; i < contacts; i++ ) {
			ContactPoint *point;
			luax_catchexcept(L, [&](){ point = new ContactPoint(manifold->getContactPoint(i)); });
			luax_pushtype(L, point);
			point->release();
			lua_rawseti(L, table_index, i + 1);
		}
		luax_pushtype(L, a);
		luax_pushtype(L, b);
		lua_call(L, 3, 0);
	}
	return 0;
}

RigidBody::RigidBody(Shape *shape, float mass, lua_State *L) :	
	world(nullptr),
	userdata(new UserData()),
	in_world(false)
{
	userdata->rbody = this;
	shape_reference.set(shape);

	btCollisionShape *bt_shape = shape->shape;
	btVector3 local_inertia(0, 0, 0);
	if( mass != 0.f ) {
		bt_shape->calculateLocalInertia(mass, local_inertia);
	}

	motion_state = new MotionState(this, L);

	btRigidBody::btRigidBodyConstructionInfo c_info(mass, motion_state, bt_shape, local_inertia);
	rbody = new btRigidBody(c_info);

	rbody->setUserPointer((void*)userdata);

	contact_callback.reference = new Reference();
}

RigidBody::~RigidBody()
{
	if( userdata ) {
		if( userdata->reference ) {
			delete userdata->reference;
		}
		delete userdata;
	}
}

void RigidBody::getTransform(btScalar *a16) {
	const btTransform &t = rbody->getWorldTransform();
	t.getOpenGLMatrix(a16);
}

void RigidBody::setTransform(btScalar *a16) {
	btTransform &t = rbody->getWorldTransform();
	t.setFromOpenGLMatrix(a16);
}

void RigidBody::setDamping(btScalar linear, btScalar angular) {
	rbody->setDamping(linear, angular);
}

void RigidBody::setRestitution(float factor) {
	rbody->setRestitution(factor);
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

void RigidBody::activate(bool forceActivation) {
	rbody->activate();
}

const btVector3 &RigidBody::getLinearVelocity() const {
	return rbody->getLinearVelocity();
}

void RigidBody::setLinearVelocity(btVector3 const &v) {
	rbody->setLinearVelocity(v);
}

int RigidBody::setUserData(lua_State *L) {
	love::luax_assert_argc(L, 1, 1);

	if( userdata->reference == nullptr ) {
		userdata->reference = new Reference();
	}
	userdata->reference->ref(L);
	return 0;
}

int RigidBody::getUserData(lua_State *L) {
	if( userdata != nullptr && userdata->reference != nullptr ) {
		userdata->reference->push(L);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int RigidBody::setCallback(lua_State *L) {
	if( contact_callback.reference ) {
		contact_callback.reference->unref();
	}

	luaL_checktype(L, 1, LUA_TFUNCTION);
	lua_pushvalue(L, 1);
	contact_callback.reference = luax_refif(L, LUA_TFUNCTION);
	contact_callback.L = L;
	return 0;
}

}
}
}
