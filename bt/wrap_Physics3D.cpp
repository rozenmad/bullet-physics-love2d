// LOVE
#include "Physics3D.h"

#include "wrap_World.h"
#include "wrap_RigidBody.h"
#include "wrap_Shape.h"
#include "wrap_BoxShape.h"
#include "wrap_TriangleMeshShape.h"
#include "wrap_ContactPoint.h"
#include "wrap_CollisionObject.h"

namespace love
{
namespace physics3d
{
namespace bt
{

#define instance() (Module::getInstance<Physics3D>(Module::M_PHYSICS3D))

int w_newWorld(lua_State *L) {
	World *w;
	float gx = (float)luaL_optnumber(L, 1, 0.0f);
	float gy = (float)luaL_optnumber(L, 2, 0.0f);
	float gz = (float)luaL_optnumber(L, 3, 0.0f);
	luax_catchexcept(L, [&](){ w = new World(gx, gy, gz); });
	luax_pushtype(L, w);
	w->release();
	return 1;
}

int w_newRigidBody(lua_State *L) {
	Shape *shape = luax_checkshape(L, 1);
	float mass = (float)luaL_checknumber(L, 2);
	RigidBody *rbody;
	
	luaL_checktype(L, 3, LUA_TTABLE);
	lua_pushvalue(L, 3);

	luax_catchexcept(L, [&](){ rbody = new RigidBody(shape, mass, L); });
	luax_pushtype(L, rbody);
	rbody->release();
	return 1;
}

int w_newBoxShape(lua_State *L) {
	float bx = (float)luaL_checknumber(L, 1);
	float by = (float)luaL_checknumber(L, 2);
	float bz = (float)luaL_checknumber(L, 3);

	BoxShape *shape;
	luax_catchexcept(L, [&](){ shape = new BoxShape(btVector3(bx, by, bz)); });
	luax_pushtype(L, shape);
	shape->release();
	return 1;
}

int w_newTriangleMeshShape(lua_State *L) {
	if( lua_istable(L, 1) ) {
		TriangleMeshShape *shape;
		luax_catchexcept(L, [&](){ shape = new TriangleMeshShape(L); });
		luax_pushtype(L, shape);
		shape->release();
	} else {
		return luaL_error(L, "First argument must be vertex table.");
	}
	return 1;
}

// List of functions to wrap.
static const luaL_Reg functions[] =
{
	{ "newWorld", w_newWorld },
	{ "newRigidBody", w_newRigidBody },
	{ "newBoxShape", w_newBoxShape },
	{ "newTriangleMeshShape", w_newTriangleMeshShape },
	{ 0, 0 }
};

static const lua_CFunction types[] =
{
	luaopen_bt_world,
	luaopen_bt_rigidbody,
	luaopen_bt_shape,
	luaopen_bt_boxshape,
	luaopen_bt_trianglemeshshape,
	luaopen_bt_contactpoint,
	luaopen_bt_collisionobject,
	0
};

extern "C" int luaopen_love_physics3d(lua_State *L)
{
	Physics3D *instance = instance();
	if (instance == nullptr)
	{
		luax_catchexcept(L, [&](){ instance = new Physics3D(); });
	}
	else
		instance->retain();

	WrappedModule w;
	w.module = instance;
	w.name = "physics3d";
	w.type = &Module::type;
	w.functions = functions;
	w.types = types;

	return luax_register_module(L, w);
}

} // bt
} // physics3d
} // love
