#ifndef LOVE_PHYSICS3D_BT_WRAP_SHAPE_H
#define LOVE_PHYSICS3D_BT_WRAP_SHAPE_H

// LOVE
#include "common/runtime.h"
#include "common/Exception.h"
#include "Shape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

Shape *luax_checkshape(lua_State *L, int idx);
extern "C" int luaopen_bt_shape(lua_State *L);

extern const luaL_Reg w_Shape_functions[];

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_WRAP_SHAPE_H
