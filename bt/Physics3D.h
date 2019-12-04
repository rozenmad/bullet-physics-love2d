/**
 * Copyright (c) 2006-2019 LOVE Development Team
 *
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 **/

#ifndef LOVE_PHYSICS3D_BT_PHYSICS3D_H
#define LOVE_PHYSICS3D_BT_PHYSICS3D_H

// LOVE
#include "common/Module.h"
#include "common/runtime.h"
#include "common/Reference.h"
#include "World.h"

struct cpml_vec3 {
	double x;
	double y;
	double z;
};

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
