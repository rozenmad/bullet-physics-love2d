#include "CollisionObject.h"
#include "ContactPoint.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type CollisionObject::type("btCollisionObject", &Object::type);

int CollisionObject::ContactCallback::report(World *world, 
	btPersistentManifold *manifold, 
	CollisionObject *a, 
	CollisionObject *b)
{
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

CollisionObject::CollisionObject(btCollisionObject *collision_object) :
	collision_object(collision_object),
	world(nullptr),
	userdata(new UserData())
{
	userdata->obj = this;
	collision_object->setUserPointer((void*)userdata);

	contact_callback.reference = new Reference();
}

CollisionObject::~CollisionObject() {
	if( userdata ) {
		if( userdata->reference ) {
			delete userdata->reference;
		}
		delete userdata;
	}
}

void CollisionObject::getTransform(btScalar *a16) const {
	auto &t = collision_object->getWorldTransform();
	t.getOpenGLMatrix(a16);
}

void CollisionObject::setTransform(btScalar *a16) {
	auto &t = collision_object->getWorldTransform();
	t.setFromOpenGLMatrix(a16);
}

int CollisionObject::setUserData(lua_State *L) {
	love::luax_assert_argc(L, 1, 1);

	if( userdata->reference == nullptr ) {
		userdata->reference = new Reference();
	}
	userdata->reference->ref(L);
	return 0;
}

int CollisionObject::getUserData(lua_State *L) {
	if( userdata != nullptr && userdata->reference != nullptr ) {
		userdata->reference->push(L);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int CollisionObject::setCallback(lua_State *L) {
	if( contact_callback.reference ) {
		contact_callback.reference->unref();
	}

	luaL_checktype(L, 1, LUA_TFUNCTION);
	lua_pushvalue(L, 1);
	contact_callback.reference = luax_refif(L, LUA_TFUNCTION);
	contact_callback.L = L;
	return 0;
}

} // bt
} // physics3d
} // love
