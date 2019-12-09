#include "wrap_World.h"
#include "wrap_RigidBody.h"
#include "wrap_CollisionObject.h"
#include "wrap_CharacterController.h"
#include "wrap_RaycastHit.h"
#include "Physics3D.h"

namespace love
{
namespace physics3d
{
namespace bt
{

World *luax_checkworld(lua_State *L, int idx) {
	return luax_checktype<World>(L, idx);
}

int w_World_update(lua_State *L) {
	World *world = luax_checkworld(L, 1);
	float time_step = (float)luaL_checknumber(L, 2);
	int max_sub_steps = (int)luaL_optnumber(L, 3, 1.0);

	if( lua_isnoneornil(L, 4) ) {
		world->update(time_step, max_sub_steps);
	} else {
		float fixed_time_step = (float)luaL_checknumber(L, 4);
		world->update(time_step, max_sub_steps, fixed_time_step);
	}
	return 0;
}

int w_World_raycast(lua_State *L) {
	World *world = luax_checkworld(L, 1);
	btVector3 origin = Physics3D::parse_btVector3(L, 2);
	btVector3 direction = Physics3D::parse_btVector3(L, 3);
	float max_distance = (float)luaL_checknumber(L, 4);
	return world->raycast(L, origin, direction, max_distance, 0);
}

int w_World_addRigidBody(lua_State *L) {
	World *world = luax_checkworld(L, 1);
	RigidBody *rbody = luax_checkrigidbody(L, 2);
	world->addRigidBody(rbody);
	return 0;
}

int w_World_addCharacterController(lua_State *L) {
	World *world = luax_checkworld(L, 1);
	CharacterController *object = luax_checkcharactercontroller(L, 2);
	world->addCharacterController(object);
	return 0;
}

int w_World_removeRigidBody(lua_State *L) {
	World *world = luax_checkworld(L, 1);
	CollisionObject *object = luax_checkrigidbody(L, 2);
	world->removeRigidBody(object);
	return 0;
}

int w_World_removeCharacterController(lua_State *L) {
	World *world = luax_checkworld(L, 1);
	CharacterController *object = luax_checkcharactercontroller(L, 2);
	world->removeCharacterController(object);
	return 0;
}

static const luaL_Reg w_World_functions[] =
{
	{ "update", w_World_update },
	{ "raycast", w_World_raycast },
	{ "addRigidBody", w_World_addRigidBody },
	{ "addCharacterController", w_World_addCharacterController },
	{ "removeRigidBody", w_World_removeRigidBody },
	{ "removeCharacterController", w_World_removeCharacterController },
	{ 0, 0 }
};

extern "C" int luaopen_bt_world(lua_State *L) {
	return luax_register_type(L, &World::type, w_World_functions, nullptr);
}

}
}
}