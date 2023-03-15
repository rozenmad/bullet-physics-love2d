#include "wrap_SphereShape.h"
#include "wrap_Shape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

SphereShape *luax_checksphereshape(lua_State *L, int idx) {
	return luax_checktype<SphereShape>(L, idx);
}

int w_SphereShape_dummy(lua_State *L) {
	return 0;
}

static const luaL_Reg w_SphereShape_functions[] = 
{
	{ "dummy", w_SphereShape_dummy },
	{ 0, 0 }
};

extern "C" int luaopen_bt_sphereshape(lua_State *L) {
	return luax_register_type(L, &SphereShape::type, w_Shape_functions, w_SphereShape_functions, nullptr);
}

} // bt
} // physics3d
} // love