#ifndef LOVE_PHYSICS3D_BT_WRAP_COLLISIONOBJECT_H
#define LOVE_PHYSICS3D_BT_WRAP_COLLISIONOBJECT_H

// LOVE
#include "common/runtime.h"
#include "common/Exception.h"
#include "CollisionObject.h"

namespace love
{
namespace physics3d
{
namespace bt
{

CollisionObject *luax_checkcollisionobject(lua_State *L, int idx);
extern "C" int luaopen_bt_collisionobject(lua_State *L);

extern const luaL_Reg w_CollisionObject_functions[];

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_WRAP_COLLISIONOBJECT_H
