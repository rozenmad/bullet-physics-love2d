#include "wrap_RaycastHit.h"

namespace love
{
namespace physics3d
{
namespace bt
{

RaycastHit *luax_checkraycasthit(lua_State *L, int idx) {
	return luax_checktype<RaycastHit>(L, idx);
}

int w_RaycastHit_getPosition(lua_State *L) {
	RaycastHit *raycast_hit = luax_checkraycasthit(L, 1);
	lua_pushnumber(L, raycast_hit->position.x());
	lua_pushnumber(L, raycast_hit->position.y());
	lua_pushnumber(L, raycast_hit->position.z());
	return 3;
}

int w_RaycastHit_getNormal(lua_State *L) {
	RaycastHit *raycast_hit = luax_checkraycasthit(L, 1);
	lua_pushnumber(L, raycast_hit->normal.x());
	lua_pushnumber(L, raycast_hit->normal.y());
	lua_pushnumber(L, raycast_hit->normal.z());
	return 3;
}

int w_RaycastHit_getDistance(lua_State *L) {
	RaycastHit *raycast_hit = luax_checkraycasthit(L, 1);
	lua_pushnumber(L, raycast_hit->distance);
	return 1;
}

int w_RaycastHit_getHitFraction(lua_State *L) {
	RaycastHit *raycast_hit = luax_checkraycasthit(L, 1);
	lua_pushnumber(L, raycast_hit->hit_fraction);
	return 1;
}

int w_RaycastHit_getCollisionObject(lua_State *L) {
	RaycastHit *raycast_hit = luax_checkraycasthit(L, 1);
	luax_pushtype(L, raycast_hit->object);
	return 1;
}

static const luaL_Reg w_RaycastHit_functions[] =
{
	{ "getPosition", w_RaycastHit_getPosition },
	{ "getNormal", w_RaycastHit_getNormal },
	{ "getDistance", w_RaycastHit_getDistance },
	{ "getHitFraction", w_RaycastHit_getHitFraction },
	{ "getCollisionObject", w_RaycastHit_getCollisionObject },
	{ 0, 0 }
};

extern "C" int luaopen_bt_raycasthit(lua_State *L) {
	return luax_register_type(L, &RaycastHit::type, w_RaycastHit_functions, nullptr);
}

}
}
}