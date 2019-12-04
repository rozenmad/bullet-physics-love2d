#include "TriangleMeshShape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type TriangleMeshShape::type("btTriangleMeshShape", &Shape::type);

TriangleMeshShape::TriangleMeshShape(lua_State *L) :
	Shape(generate_bvh_trangle_mesh_shape(L))
{

}

static btVector3 get_vertex_from_table(lua_State *L, int table_index) {
	btVector3 vertex;
	if( lua_istable(L, table_index) ) {
		for( int j = 1; j <= 3; j++ ) {
			lua_rawgeti(L, table_index, j);
			vertex.m_floats[j - 1] = (float)luaL_checknumber(L, -1);
			lua_pop(L, 1);
		}
	}
	return vertex;
}

btBvhTriangleMeshShape *TriangleMeshShape::generate_bvh_trangle_mesh_shape(lua_State *L) {
	btTriangleMesh* triangles = new btTriangleMesh();
	
	int *indices = nullptr;
	int length = 0;
	if( lua_istable(L, 2) ) { // indices table
		length = luax_objlen(L, 2);
		indices = new int[length];
		for( int i = 1; i <= length; i++ ) {
			lua_rawgeti(L, 2, i);
			indices[i - 1] = (int)luaL_checkinteger(L, -1);
			lua_pop(L, 1);
		}
	}

	if( indices ) {
		for( int i = 1; i <= length; i += 3 ) {
			lua_rawgeti(L, 1, indices[i-1]);
			btVector3 vertex1 = get_vertex_from_table(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, 1, indices[i+0]);
			btVector3 vertex2 = get_vertex_from_table(L, -1);
			lua_pop(L, 1);
			lua_rawgeti(L, 1, indices[i+1]);
			btVector3 vertex3 = get_vertex_from_table(L, -1);
			lua_pop(L, 1);

			triangles->addTriangle(vertex1, vertex2, vertex3);
		}
		delete [] indices;
		btBvhTriangleMeshShape* triangle_mesh_shape = new btBvhTriangleMeshShape(triangles, true);
		return triangle_mesh_shape;
	}
	return nullptr;
}



} // bt
} // physics3d
} // love