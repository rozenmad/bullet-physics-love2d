#ifndef LOVE_PHYSICS3D_BT_WRAP_BOXSHAPE_H
#define LOVE_PHYSICS3D_BT_WRAP_BOXSHAPE_H

// LOVE
#include "common/runtime.h"
#include "common/Exception.h"
#include "BoxShape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

BoxShape *luax_checkboxshape(lua_State *L, int idx);
extern "C" int luaopen_bt_boxshape(lua_State *L);

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_WRAP_BOXSHAPE_H
