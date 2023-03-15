#ifndef LOVE_PHYSICS3D_BT_WRAP_CAPSULESHAPE_H
#define LOVE_PHYSICS3D_BT_WRAP_CAPSULESHAPE_H

// LOVE
#include "../../love_luapi/runtime.h"
#include "CapsuleShape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

CapsuleShape *luax_checkcapsuleshape(lua_State *L, int idx);
extern "C" int luaopen_bt_capsuleshape(lua_State *L);

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_WRAP_CAPSULESHAPE_H
