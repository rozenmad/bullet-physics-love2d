#include "wrap_RigidBody.h"
#include "Physics3D.h"

namespace love
{
namespace physics3d
{
namespace bt
{

RigidBody *luax_checkrigidbody(lua_State *L, int idx)
{
	return luax_checktype<RigidBody>(L, idx);
}

int w_RigidBody_getTransform(lua_State *L)
{
	RigidBody *rbody = luax_checkrigidbody(L, 1);
	btScalar a16[16];
	rbody->getTransform(a16);
	int idx = 2;
	if( lua_istable(L, idx) ) {
		for( int i = 0; i < 16; i++ ) {
			lua_pushnumber(L, a16[i]);
			lua_rawseti(L, idx, i+1);
		}
	}
	return 0;
}

int w_RigidBody_setTransform(lua_State *L)
{
	RigidBody *rbody = luax_checkrigidbody(L, 1);
	btScalar a16[16];
	int idx = 2;
	if( lua_istable(L, idx) ) {
		for( int i = 0; i < 16; i++ ) {
			lua_rawgeti(L, idx, i+1);
			a16[i] = (float)luaL_checknumber(L, -1);
			lua_pop(L, 1);
		}
		rbody->setTransform(a16);
	}
	return 0;
}

int w_RigidBody_setDamping(lua_State *L)
{
	RigidBody *rbody = luax_checkrigidbody(L, 1);

	float lin = (float)luaL_checknumber(L, 2);
	float ang = (float)luaL_checknumber(L, 3);
	rbody->setDamping(lin, ang);
	return 0;
}

int w_RigidBody_setRestitution(lua_State *L) {
	RigidBody *rbody = luax_checkrigidbody(L, 1);
	float factor = (float)luaL_checknumber(L, 2);
	rbody->setRestitution(factor);
	return 0;
}

int w_RigidBody_applyForce(lua_State *L) {
	RigidBody *rbody = luax_checkrigidbody(L, 1);

	btVector3 f = Physics3D::parse_btVector3(L, 2);
	btVector3 p = Physics3D::parse_btVector3(L, 3);

	rbody->applyForce(f, p);
	return 0;
}

int w_RigidBody_setAngularFactor(lua_State *L) {
	RigidBody *rbody = luax_checkrigidbody(L, 1);
	btVector3 factor = Physics3D::parse_btVector3(L, 2);

	rbody->setAngularFactor(factor);
	return 0;
}

int w_RigidBody_setLinearFactor(lua_State *L) {
	RigidBody *rbody = luax_checkrigidbody(L, 1);
	btVector3 factor = Physics3D::parse_btVector3(L, 2);

	rbody->setLinearFactor(factor);
	return 0;
}

int w_RigidBody_setKinematic(lua_State *L) {
	RigidBody *rbody = luax_checkrigidbody(L, 1);
	if( lua_isnoneornil(L, 2) ) {
		rbody->setKinematic();
	} else {
		bool enable = (bool)lua_toboolean(L, 2);
		rbody->setKinematic(enable);
	}

	return 0;
}

int w_RigidBody_activate(lua_State *L) {
	RigidBody *rbody = luax_checkrigidbody(L, 1);
	rbody->activate();
	return 0;
}

int w_RigidBody_getLinearVelocity(lua_State *L) {
	RigidBody *rbody = luax_checkrigidbody(L, 1);
	btVector3 const &v = rbody->getLinearVelocity();
	lua_pushnumber(L, v.x());
	lua_pushnumber(L, v.y());
	lua_pushnumber(L, v.z());
	return 3;
}

int w_RigidBody_setLinearVelocity(lua_State *L) {
	RigidBody *rbody = luax_checkrigidbody(L, 1);
	float x = (float)luaL_checknumber(L, 2);
	float y = (float)luaL_checknumber(L, 3);
	float z = (float)luaL_checknumber(L, 4);
	rbody->setLinearVelocity(btVector3(x, y, z));
	return 0;
}

int w_Body_setUserData(lua_State *L)
{
	RigidBody *rbody = luax_checkrigidbody(L, 1);
	lua_remove(L, 1);
	return rbody->setUserData(L);
}

int w_Body_getUserData(lua_State *L)
{
	RigidBody *rbody = luax_checkrigidbody(L, 1);
	lua_remove(L, 1);
	return rbody->getUserData(L);
}

int w_Body_setCallback(lua_State *L) {
	RigidBody *rbody = luax_checkrigidbody(L, 1);
	lua_remove(L, 1);
	return rbody->setCallback(L);
}

static const luaL_Reg w_RigidBody_functions[] =
{
	{ "getTransform", w_RigidBody_getTransform },
	{ "setTransform", w_RigidBody_setTransform },
	{ "setDamping", w_RigidBody_setDamping },
	{ "setRestitution", w_RigidBody_setRestitution },
	{ "applyForce", w_RigidBody_applyForce },
	{ "setAngularFactor", w_RigidBody_setAngularFactor },
	{ "setLinearFactor", w_RigidBody_setLinearFactor },
	{ "setKinematic", w_RigidBody_setKinematic },
	{ "activate", w_RigidBody_activate },
	{ "getLinearVelocity", w_RigidBody_getLinearVelocity },
	{ "setLinearVelocity", w_RigidBody_setLinearVelocity },
	{ "setUserData", w_Body_setUserData },
	{ "getUserData", w_Body_getUserData },
	{ "setCallback", w_Body_setCallback },
	{ 0, 0 }
};

extern "C" int luaopen_bt_rigidbody(lua_State *L)
{
	return luax_register_type(L, &RigidBody::type, w_RigidBody_functions, nullptr);
}

}
}
}