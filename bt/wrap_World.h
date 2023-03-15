#ifndef LOVE_PHYSICS3D_BT_WRAP_WORLD_H
#define LOVE_PHYSICS3D_BT_WRAP_WORLD_H

// LOVE
#include "../love_luapi/runtime.h"
#include "../love_luapi/Exception.h"
#include "World.h"

namespace love
{
namespace physics3d
{
namespace bt
{

World *luax_checkworld(lua_State *L, int idx);
extern "C" int luaopen_bt_world(lua_State *L);

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_WRAP_WORLD_H
