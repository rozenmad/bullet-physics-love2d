#ifndef LOVE_PHYSICS3D_BT_WRAP_CONTACTPOINT_H
#define LOVE_PHYSICS3D_BT_WRAP_CONTACTPOINT_H

// LOVE
#include "common/runtime.h"
#include "ContactPoint.h"

namespace love
{
namespace physics3d
{
namespace bt
{

ContactPoint *luax_checkcontactpoint(lua_State *L, int idx);
extern "C" int luaopen_bt_contactpoint(lua_State *L);

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_WRAP_CONTACTPOINT_H
