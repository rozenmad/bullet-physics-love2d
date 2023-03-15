#include "wrap_TriangleMeshShape.h"
#include "wrap_Shape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

TriangleMeshShape *luax_checktrianglemeshshape(lua_State *L, int idx) {
	return luax_checktype<TriangleMeshShape>(L, idx);;
}

int w_TriangleMeshShape_dummy(lua_State *L) {
	return 0;
}

static const luaL_Reg w_TriangleMeshShape_functions[] =
{
	{ "dummy", w_TriangleMeshShape_dummy },
	{ 0, 0 }
};

extern "C" int luaopen_bt_trianglemeshshape(lua_State *L) {
	return luax_register_type(L, &TriangleMeshShape::type, w_Shape_functions, w_TriangleMeshShape_functions, nullptr);
}

}
}
}