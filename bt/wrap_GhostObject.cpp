#include "Physics3D.h"
#include "wrap_GhostObject.h"
#include "wrap_CollisionObject.h"
#include "shapes/wrap_Shape.h"
#include "callback/wrap_KinematicCallback.h"

namespace love
{
namespace physics3d
{
namespace bt
{

GhostObject *luax_checkghostobject(lua_State *L, int idx) {
	return luax_checktype<GhostObject>(L, idx);
}

int w_GhostObject_convexSweepTest(lua_State *L) {
	GhostObject *ghost = luax_checkghostobject(L, 1);
	Shape *shape = luax_checkshape(L, 2);

	btTransform tfrom;
	btTransform tto;
	Physics3D::parse_btTransform(L, 3, tto);
	Physics3D::parse_btTransform(L, 4, tfrom);

	KinematicCallback *callback = luax_checkkinematiccallback(L, 5);
	float ccd_penetration = luax_checkfloat(L, 6);

	ghost->convexSweepTest(shape, tfrom, tto, callback, ccd_penetration);
	return 0;
}

static const luaL_Reg w_GhostObject_functions[] = 
{
	{ "convexSweepTest", w_GhostObject_convexSweepTest },
	{ 0, 0 }
};

extern "C" int luaopen_bt_ghostobject(lua_State *L) {
	return luax_register_type(L, &GhostObject::type, w_CollisionObject_functions, w_GhostObject_functions, nullptr);
}

} // bt
} // physics3d
} // love
