#ifndef LOVE_PHYSICS3D_BT_WRAP_RAYCASTHIT_H
#define LOVE_PHYSICS3D_BT_WRAP_RAYCASTHIT_H

// LOVE
#include "common/runtime.h"
#include "common/Exception.h"
#include "RaycastHit.h"

namespace love
{
namespace physics3d
{
namespace bt
{

RaycastHit *luax_checkraycasthit(lua_State *L, int idx);
extern "C" int luaopen_bt_raycasthit(lua_State *L);

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_WRAP_RAYCASTHIT_H
