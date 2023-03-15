#include "wrap_CollisionObject.h"
#include "Physics3D.h"
#include "shapes/wrap_Shape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

CollisionObject *luax_checkcollisionobject(lua_State *L, int idx) {
	return luax_checktype<CollisionObject>(L, idx);
}

int w_CollisionObject_getAnisotropicFriction(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	const btVector3 &v = object->getAnisotropicFriction();
	lua_pushnumber(L, v.x());
	lua_pushnumber(L, v.y());
	lua_pushnumber(L, v.z());
	return 3;
}

int w_CollisionObject_setAnisotropicFriction(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	btVector3 factor = Physics3D::parse_btVector3(L, 2);
	object->setAnisotropicFriction(factor);
	return 0;
}

int w_CollisionObject_hasAnisotropicFriction(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushboolean(L, object->hasAnisotropicFriction());
	return 1;
}

int w_CollisionObject_setContactProcessingThreshold(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	float value = (float)luaL_checknumber(L, 2);
	object->setContactProcessingThreshold(value);
	return 0;
}

int w_CollisionObject_getContactProcessingThreshold(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushnumber(L, object->getContactProcessingThreshold());
	return 1;
}

int w_CollisionObject_isStaticObject(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushboolean(L, object->isStaticObject());
	return 1;
}

int w_CollisionObject_isKinematicObject(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushboolean(L, object->isKinematicObject());
	return 1;
}

int w_CollisionObject_isStaticOrKinematicObject(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushboolean(L, object->isStaticOrKinematicObject());
	return 1;
}

int w_CollisionObject_hasContactResponse(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushboolean(L, object->hasContactResponse());
	return 1;
}

int w_CollisionObject_setCollisionShape(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	Shape *shape = luax_checkshape(L, 2);
	object->setCollisionShape(shape);
	return 0;
}

int w_CollisionObject_getCollisionShape(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	luax_pushtype(L, object->getCollisionShape());
	return 1;
}


int w_CollisionObject_getTransform(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	object->getTransform(L, 2);
	return 0;
}

int w_CollisionObject_setTransform(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	object->setTransform(L, 2);
	return 0;
}

int w_CollisionObject_setUserData(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_remove(L, 1);
	return object->setUserData(L);
}

int w_CollisionObject_getUserData(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_remove(L, 1);
	return object->getUserData(L);
}

int w_CollisionObject_setCallback(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_remove(L, 1);
	return object->setCallback(L);
}

int w_CollisionObject_activate(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	bool force = luax_optboolean(L, 2, false);
	object->activate(force);
	return 0;
}

int w_CollisionObject_isActive(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushboolean(L, object->isActive());
	return 1;
}

int w_CollisionObject_setRestitution(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	float value = (float)luaL_checknumber(L, 2);
	object->setRestitution(value);
	return 0;
}

int w_CollisionObject_setFriction(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	float value = (float)luaL_checknumber(L, 2);
	object->setFriction(value);
	return 0;
}

int w_CollisionObject_setRollingFriction(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	float value = (float)luaL_checknumber(L, 2);
	object->setRollingFriction(value);
	return 0;
}

int w_CollisionObject_setSpinningFriction(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	float value = (float)luaL_checknumber(L, 2);
	object->setSpinningFriction(value);
	return 0;
}

int w_CollisionObject_setContactStiffnessAndDamping(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	float stiffness = (float)luaL_checknumber(L, 2);
	float damping = (float)luaL_checknumber(L, 3);
	object->setContactStiffnessAndDamping(stiffness, damping);
	return 0;
}

int w_CollisionObject_setHitFraction(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	float value = (float)luaL_checknumber(L, 2);
	object->setHitFraction(value);
	return 0;
}

int w_CollisionObject_setCcdSweptSphereRadius(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	float value = (float)luaL_checknumber(L, 2);
	object->setCcdSweptSphereRadius(value);
	return 0;
}

int w_CollisionObject_setCcdMotionThreshold(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	float value = (float)luaL_checknumber(L, 2);
	object->setCcdMotionThreshold(value);
	return 0;
}

int w_CollisionObject_getRestitution(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushnumber(L, object->getRestitution());
	return 1;
}

int w_CollisionObject_getFriction(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushnumber(L, object->getFriction());
	return 1;
}

int w_CollisionObject_getRollingFriction(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushnumber(L, object->getRollingFriction());
	return 1;
}

int w_CollisionObject_getSpinningFriction(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushnumber(L, object->getSpinningFriction());
	return 1;
}

int w_CollisionObject_getContactStiffness(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushnumber(L, object->getContactStiffness());
	return 1;
}

int w_CollisionObject_getContactDamping(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushnumber(L, object->getContactDamping());
	return 1;
}

int w_CollisionObject_getHitFraction(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushnumber(L, object->getHitFraction());
	return 1;
}

int w_CollisionObject_getCcdSweptSphereRadius(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushnumber(L, object->getCcdSweptSphereRadius());
	return 1;
}

int w_CollisionObject_getCcdMotionThreshold(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushnumber(L, object->getCcdMotionThreshold());
	return 1;
}

int w_CollisionObject_getCcdSquareMotionThreshold(lua_State *L) {
	CollisionObject *object = luax_checkcollisionobject(L, 1);
	lua_pushnumber(L, object->getCcdSquareMotionThreshold());
	return 1;
}

int w_CollisionObject_canCollideWith(lua_State *L) {
	CollisionObject *object1 = luax_checkcollisionobject(L, 1);
	CollisionObject *object2 = luax_checkcollisionobject(L, 2);
	lua_pushboolean(L, object1->canCollideWith(object2));
	return 1;
}

static const luaL_Reg w_CollisionObject_functions[] =
{
	{ "getAnisotropicFriction", w_CollisionObject_getAnisotropicFriction },
	{ "setAnisotropicFriction", w_CollisionObject_setAnisotropicFriction },
	{ "hasAnisotropicFriction", w_CollisionObject_hasAnisotropicFriction },

	{ "setContactProcessingThreshold", w_CollisionObject_setContactProcessingThreshold },
	{ "getContactProcessingThreshold", w_CollisionObject_getContactProcessingThreshold },

	{ "isStaticObject", w_CollisionObject_isStaticObject },
	{ "isKinematicObject", w_CollisionObject_isKinematicObject },
	{ "isStaticOrKinematicObject", w_CollisionObject_isStaticOrKinematicObject },

	{ "getTransform", w_CollisionObject_getTransform },
	{ "setTransform", w_CollisionObject_setTransform },
	{ "setUserData", w_CollisionObject_setUserData },
	{ "getUserData", w_CollisionObject_getUserData },
	{ "setCallback", w_CollisionObject_setCallback },
	{ "activate", w_CollisionObject_activate },
	{ "isActive", w_CollisionObject_isActive },
	{ "setRestitution", w_CollisionObject_setRestitution },
	{ "setFriction", w_CollisionObject_setFriction },
	{ "setRollingFriction", w_CollisionObject_setRollingFriction },
	{ "setSpinningFriction", w_CollisionObject_setSpinningFriction },
	{ "setContactStiffnessAndDamping", w_CollisionObject_setContactStiffnessAndDamping },
	{ "setHitFraction", w_CollisionObject_setHitFraction },
	{ "setCcdSweptSphereRadius", w_CollisionObject_setCcdSweptSphereRadius },
	{ "setCcdMotionThreshold", w_CollisionObject_setCcdMotionThreshold },
	{ "getCollisionShape", w_CollisionObject_getCollisionShape },
	{ "getRestitution", w_CollisionObject_getRestitution },
	{ "getFriction", w_CollisionObject_getFriction },
	{ "getRollingFriction", w_CollisionObject_getRollingFriction },
	{ "getSpinningFriction", w_CollisionObject_getSpinningFriction },
	{ "getContactStiffness", w_CollisionObject_getContactStiffness },
	{ "getContactDamping", w_CollisionObject_getContactDamping },
	{ "getHitFraction", w_CollisionObject_getHitFraction },
	{ "getCcdSweptSphereRadius", w_CollisionObject_getCcdSweptSphereRadius },
	{ "getCcdMotionThreshold", w_CollisionObject_getCcdMotionThreshold },
	{ "getCcdSquareMotionThreshold", w_CollisionObject_getCcdSquareMotionThreshold },
	{ "canCollideWith", w_CollisionObject_canCollideWith },
	{ 0, 0 }
};

extern "C" int luaopen_bt_collisionobject(lua_State *L) {
	return luax_register_type(L, &CollisionObject::type, w_CollisionObject_functions, nullptr);
}

}
}
}