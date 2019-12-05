#include "wrap_CollisionObject.h"

namespace love
{
namespace physics3d
{
namespace bt
{

CollisionObject *luax_checkcollisionobject(lua_State *L, int idx)
{
	return luax_checktype<CollisionObject>(L, idx);
}

int w_CollisionObject_getTransform(lua_State *L)
{
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	btScalar a16[16];
	object->getTransform(a16);
	int idx = 2;
	if( lua_istable(L, idx) ) {
		for( int i = 0; i < 16; i++ ) {
			lua_pushnumber(L, a16[i]);
			lua_rawseti(L, idx, i+1);
		}
	}
	return 0;
}

int w_CollisionObject_setTransform(lua_State *L)
{
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	btScalar a16[16];
	int idx = 2;
	if( lua_istable(L, idx) ) {
		for( int i = 0; i < 16; i++ ) {
			lua_rawgeti(L, idx, i+1);
			a16[i] = (float)luaL_checknumber(L, -1);
			lua_pop(L, 1);
		}
		object->setTransform(a16);
	}
	return 0;
}


int w_CollisionObject_setUserData(lua_State *L)
{
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_remove(L, 1);
	return object->setUserData(L);
}

int w_CollisionObject_getUserData(lua_State *L)
{
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_remove(L, 1);
	return object->getUserData(L);
}

int w_CollisionObject_setCallback(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_remove(L, 1);
	return object->setCallback(L);
}

static const luaL_Reg w_CollisionObject_functions[] =
{
	{ "getTransform", w_CollisionObject_getTransform },
	{ "setTransform", w_CollisionObject_setTransform },
	{ "setUserData", w_CollisionObject_setUserData },
	{ "getUserData", w_CollisionObject_getUserData },
	{ "setCallback", w_CollisionObject_setCallback },
	{ 0, 0 }
};

extern "C" int luaopen_bt_collisionobject(lua_State *L)
{
	return luax_register_type(L, &CollisionObject::type, w_CollisionObject_functions, nullptr);
}

}
}
}