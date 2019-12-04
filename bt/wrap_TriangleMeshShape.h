#ifndef LOVE_PHYSICS3D_BT_WRAP_TRIANGLEMESHSHAPE_H
#define LOVE_PHYSICS3D_BT_WRAP_TRIANGLEMESHSHAPE_H

// LOVE
#include "common/runtime.h"
#include "TriangleMeshShape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

TriangleMeshShape *luax_checktrianglemeshshape(lua_State *L, int idx);
extern "C" int luaopen_bt_trianglemeshshape(lua_State *L);

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_WRAP_TRIANGLEMESHSHAPE_H
