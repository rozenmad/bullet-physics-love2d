#include "wrap_KinematicCallback.h"
#include "KinematicCallback.h"

namespace love
{
namespace physics3d
{
namespace bt
{

int w_KinematicCallback_getHitNormal(lua_State *L) {
	KinematicCallback *object = luax_checkkinematiccallback(L, 1);
	btVector3 normal = object->getHitNormal();
      lua_pushnumber(L, normal.x());
	lua_pushnumber(L, normal.y());
	lua_pushnumber(L, normal.z());
	return 3;
}

int w_KinematicCallback_getHitPoint(lua_State *L) {
	KinematicCallback *object = luax_checkkinematiccallback(L, 1);
	btVector3 point = object->getHitPoint();
      lua_pushnumber(L, point.x());
	lua_pushnumber(L, point.y());
	lua_pushnumber(L, point.z());
	return 3;
}

int w_KinematicCallback_hasHit(lua_State *L) {
	KinematicCallback *object = luax_checkkinematiccallback(L, 1);
      lua_pushboolean(L, object->hasHit());
	return 1;
}

int w_KinematicCallback_closestHitFraction(lua_State *L) {
	KinematicCallback *object = luax_checkkinematiccallback(L, 1);
      lua_pushnumber(L, object->closestHitFraction());
	return 1;
}

static const luaL_Reg w_KinematicCallback_functions[] = 
{
	{ "getHitNormal", w_KinematicCallback_getHitNormal },
	{ "getHitPoint", w_KinematicCallback_getHitPoint },
	{ "hasHit", w_KinematicCallback_hasHit },
	{ "closestHitFraction", w_KinematicCallback_closestHitFraction },
	{ 0, 0 }
};
      
KinematicCallback *luax_checkkinematiccallback(lua_State *L, int idx) {
      return luax_checktype<KinematicCallback>(L, idx);
}

extern "C" int luaopen_bt_kinematiccallback(lua_State *L) {
      return luax_register_type(L, &KinematicCallback::type, w_KinematicCallback_functions, nullptr);
}

} // bt
} // physics3d
} // love