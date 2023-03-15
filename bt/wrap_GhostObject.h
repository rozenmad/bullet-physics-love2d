#ifndef LOVE_PHYSICS3D_BT_WRAP_GHOSTOBJECT_H
#define LOVE_PHYSICS3D_BT_WRAP_GHOSTOBJECT_H

// LOVE
#include "../love_luapi/runtime.h"
#include "GhostObject.h"

namespace love
{
namespace physics3d
{
namespace bt
{

GhostObject *luax_checkghostobject(lua_State *L, int idx);
extern "C" int luaopen_bt_ghostobject(lua_State *L);

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_WRAP_GHOSTOBJECT_H
