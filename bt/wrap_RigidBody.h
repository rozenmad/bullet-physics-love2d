#ifndef LOVE_PHYSICS3D_BT_WRAP_RIGIDBODY_H
#define LOVE_PHYSICS3D_BT_WRAP_RIGIDBODY_H

// LOVE
#include "../love_luapi/runtime.h"
#include "../love_luapi/Exception.h"
#include "RigidBody.h"

namespace love
{
namespace physics3d
{
namespace bt
{

RigidBody *luax_checkrigidbody(lua_State *L, int idx);
extern "C" int luaopen_bt_rigidbody(lua_State *L);

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_WRAP_RIGIDBODY_H
