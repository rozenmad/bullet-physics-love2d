#include "love_bullet.h"
#include "love_luapi/runtime.h"
#include "love_luapi/Object.h"

#include "bt/wrap_Physics3D.h"

TEST_EXPORT extern "C" int luaopen_love_bullet(lua_State *L)
{
	love::physics3d::bt::luaopen_love_physics3d(L);
	return 1;
}