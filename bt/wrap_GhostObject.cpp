#include "wrap_GhostObject.h"

namespace love
{
namespace physics3d
{
namespace bt
{

GhostObject *luax_checkghostobject(lua_State *L, int idx) {
	return luax_checktype<GhostObject>(L, idx);
}

int w_GhostObject_dummy(lua_State *L) {
	return 0;
}

static const luaL_Reg w_GhostObject_functions[] = 
{
	{ "dummy", w_GhostObject_dummy },
	{ 0, 0 }
};

extern "C" int luaopen_bt_ghostobject(lua_State *L) {
	return luax_register_type(L, &GhostObject::type, w_GhostObject_functions, nullptr);
}

} // bt
} // physics3d
} // love
