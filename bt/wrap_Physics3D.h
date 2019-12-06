#ifndef LOVE_PHYSICS3D_BT_WRAP_PHYSICS3D_H
#define LOVE_PHYSICS3D_BT_WRAP_PHYSICS3D_H

// LOVE
#include "common/config.h"

namespace love
{
namespace physics3d
{
namespace bt
{

extern "C" LOVE_EXPORT int luaopen_love_physics3d(lua_State *L);

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_WRAP_PHYSICS3D_H
