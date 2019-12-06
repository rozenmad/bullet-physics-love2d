#include "wrap_World.h"
#include "wrap_RigidBody.h"
#include "wrap_CollisionObject.h"

namespace love
{
namespace physics3d
{
namespace bt
{

World *luax_checkworld(lua_State *L, int idx)
{
	return luax_checktype<World>(L, idx);
}

int w_World_update(lua_State *L)
{
	World *world = luax_checkworld(L, 1);
	float time_step = (float)luaL_checknumber(L, 2);
	int max_sub_steps = (int)luaL_optnumber(L, 3, 1.0);

	if( lua_isnoneornil(L, 4) ) {
		luax_catchexcept(L, [&](){ world->update(time_step, max_sub_steps); });
	} else {
		float fixed_time_step = (float)luaL_checknumber(L, 4);
		luax_catchexcept(L, [&](){ world->update(time_step, max_sub_steps, fixed_time_step); });
	}
	return 0;
}

int w_World_addRigidBody(lua_State *L)
{
	World *world = luax_checkworld(L, 1);
	RigidBody *rbody = luax_checkrigidbody(L, 2);
	world->addRigidBody(rbody);
	return 0;
}

int w_World_addCollisionObject(lua_State *L)
{
	World *world = luax_checkworld(L, 1);
	CollisionObject *object = luax_checkcollisionobject(L, 2);
	world->addCollisionObject(object);
	return 0;
}

static const luaL_Reg w_World_functions[] =
{
	{ "update", w_World_update },
	{ "addRigidBody", w_World_addRigidBody },
	{ "addCollisionObject", w_World_addCollisionObject },
	{ 0, 0 }
};

extern "C" int luaopen_bt_world(lua_State *L)
{
	return luax_register_type(L, &World::type, w_World_functions, nullptr);
}

}
}
}