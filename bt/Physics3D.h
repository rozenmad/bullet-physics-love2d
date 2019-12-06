#ifndef LOVE_PHYSICS3D_BT_PHYSICS3D_H
#define LOVE_PHYSICS3D_BT_PHYSICS3D_H

// LOVE
#include "common/Module.h"
#include "common/runtime.h"
#include "common/Reference.h"

#include "btBulletDynamicsCommon.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class Physics3D : public Module
{
public:
	// Implements Module.
	const char *getName() const;
	virtual ModuleType getModuleType() const { return M_PHYSICS3D; }

	static inline btVector3 parse_btVector3(lua_State *L, int idx);

private:

};

inline btVector3 Physics3D::parse_btVector3(lua_State *L, int idx) {
	btVector3 v;
	if( lua_isnoneornil(L, idx) ) return v;
	
	if( lua_istable(L, idx) ) {
		lua_getfield(L, idx, "x");
		lua_getfield(L, idx, "y");
		lua_getfield(L, idx, "z");
		v.m_floats[2] = (float)luaL_checknumber(L, -1);
		v.m_floats[1] = (float)luaL_checknumber(L, -2);
		v.m_floats[0] = (float)luaL_checknumber(L, -3);
		lua_pop(L, 3);
	} else {
		luaL_error(L, "Argument #%d must be {x, y, z} table.", idx-1);
	}
	return v;
}

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_PHYSICS3D_H
