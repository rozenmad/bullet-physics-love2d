#ifndef LOVE_PHYSICS3D_BT_WRAP_SPHERESHAPE_H
#define LOVE_PHYSICS3D_BT_WRAP_SPHERESHAPE_H

// LOVE
#include "../../love_luapi/runtime.h"
#include "SphereShape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

SphereShape *luax_checksphereshape(lua_State *L, int idx);
extern "C" int luaopen_bt_sphereshape(lua_State *L);

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_WRAP_SPHERESHAPE_H
