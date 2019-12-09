#include "wrap_Shape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

Shape *luax_checkshape(lua_State *L, int idx) {
	return luax_checktype<Shape>(L, idx);
}

int w_Shape_setMargin(lua_State *L) {
	Shape *shape = luax_checkshape(L, 1);
	float margin = (float)luaL_checknumber(L, 2);
	shape->setMargin(margin);
	return 0;
}

static const luaL_Reg w_Shape_functions[] =
{
	{ "setMargin", w_Shape_setMargin },
	{ 0, 0 }
};

extern "C" int luaopen_bt_shape(lua_State *L) {
	return luax_register_type(L, &Shape::type, w_Shape_functions, nullptr);
}

}
}
}