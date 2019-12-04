#ifndef LOVE_PHYSICS3D_BT_TRIANGLEMESHSHAPE_H
#define LOVE_PHYSICS3D_BT_TRIANGLEMESHSHAPE_H

#include "common/runtime.h"
#include "btBulletDynamicsCommon.h"
#include "Shape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class TriangleMeshShape : public Shape {
public:
	static love::Type type;

	TriangleMeshShape(lua_State *L);

private:
	btBvhTriangleMeshShape *generate_bvh_trangle_mesh_shape(lua_State *L);
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_TRIANGLEMESHSHAPE_H
