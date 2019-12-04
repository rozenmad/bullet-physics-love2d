#include "wrap_ContactPoint.h"

namespace love
{
namespace physics3d
{
namespace bt
{

ContactPoint *luax_checkcontactpoint(lua_State *L, int idx)
{
	return luax_checktype<ContactPoint>(L, idx);
}

int w_ContactPoint_getPositionA(lua_State *L) {
	ContactPoint *p = luax_checkcontactpoint(L, 1);
	const btVector3 &v = p->getPositionA();
	lua_pushnumber(L, v.x());
	lua_pushnumber(L, v.y());
	lua_pushnumber(L, v.z());
	return 3;
}

int w_ContactPoint_getPositionB(lua_State *L) {
	ContactPoint *p = luax_checkcontactpoint(L, 1);
	const btVector3 &v = p->getPositionB();
	lua_pushnumber(L, v.x());
	lua_pushnumber(L, v.y());
	lua_pushnumber(L, v.z());
	return 3;
}

int w_ContactPoint_getDistance(lua_State *L) {
	ContactPoint *p = luax_checkcontactpoint(L, 1);
	btScalar distance = p->getDistance();
	lua_pushnumber(L, distance);
	return 1;
}

static const luaL_Reg w_ContactPoint_functions[] =
{
	{ "getPositionA", w_ContactPoint_getPositionA },
	{ "getPositionB", w_ContactPoint_getPositionB },
	{ "getDistance", w_ContactPoint_getDistance },
	{ 0, 0 }
};

extern "C" int luaopen_bt_contactpoint(lua_State *L)
{
	return luax_register_type(L, &ContactPoint::type, w_ContactPoint_functions, nullptr);
}

}
}
}