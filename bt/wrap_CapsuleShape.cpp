#include "wrap_CapsuleShape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

CapsuleShape *luax_checkcapsuleshape(lua_State *L, int idx) {
	return luax_checktype<CapsuleShape>(L, idx);
}

int w_CapsuleShape_dummy(lua_State *L) {
	return 0;
}

static const luaL_Reg w_CapsuleShape_functions[] = 
{
	{ "dummy", w_CapsuleShape_dummy },
	{ 0, 0 }
};

extern "C" int luaopen_bt_capsuleshape(lua_State *L) {
	return luax_register_type(L, &CapsuleShape::type, w_CapsuleShape_functions, nullptr);
}

} // bt
} // physics3d
} // love