#ifndef PHYSICS3D_BT_WRAP_KINEMATICCALLBACK_H
#define PHYSICS3D_BT_WRAP_KINEMATICCALLBACK_H

// LOVE
#include "../../love_luapi/runtime.h"
#include "KinematicCallback.h"

namespace love
{
namespace physics3d
{
namespace bt
{

KinematicCallback *luax_checkkinematiccallback(lua_State *L, int idx);
extern "C" int luaopen_bt_kinematiccallback(lua_State *L);

} // bt
} // physics3d
} // love

#endif // PHYSICS3D_BT_WRAP_KINEMATICCALLBACK_H
