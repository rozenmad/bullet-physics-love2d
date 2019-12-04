#include "wrap_BoxShape.h"
#include "wrap_Shape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

BoxShape *luax_checkboxshape(lua_State *L, int idx)
{
	BoxShape *shape = luax_checktype<BoxShape>(L, idx);
	//if (!w->isValid())
	//	luaL_error(L, "Attempt to use destroyed world.");
	return shape;
}

int w_BoxShape_dummy(lua_State *L) {
	return 0;
}

static const luaL_Reg w_BoxShape_functions[] =
{
	{ "dummy", w_BoxShape_dummy },
	{ 0, 0 }
};

extern "C" int luaopen_bt_boxshape(lua_State *L)
{
	return luax_register_type(L, &BoxShape::type, w_Shape_functions, w_BoxShape_functions, nullptr);
}

}
}
}