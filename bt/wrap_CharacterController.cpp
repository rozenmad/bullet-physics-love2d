#include "wrap_CharacterController.h"
#include "Physics3D.h"

namespace love
{
namespace physics3d
{
namespace bt
{

CharacterController *luax_checkcharactercontroller(lua_State *L, int idx) {
	return luax_checktype<CharacterController>(L, idx);
}

int w_CharacterController_setJumpSpeed(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	float value = (float)luaL_checknumber(L, 2);
	character_controller->setJumpSpeed(value);
	return 0;
}

int w_CharacterController_getJumpSpeed(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	float value = character_controller->getJumpSpeed();
	lua_pushnumber(L, value);
	return 1;
}

int w_CharacterController_jump(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	btVector3 v = Physics3D::parse_btVector3(L, 2);
	character_controller->jump(v);
	return 0;
}

int w_CharacterController_applyImpulse(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	btVector3 v = Physics3D::parse_btVector3(L, 2);
	character_controller->applyImpulse(v);
	return 0;
}

int w_CharacterController_setWalkDirection(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	btVector3 v = Physics3D::parse_btVector3(L, 2);
	character_controller->setWalkDirection(v);
	return 0;
}

int w_CharacterController_setGravity(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	btVector3 v = Physics3D::parse_btVector3(L, 2);
	character_controller->setGravity(v);
	return 0;
}

int w_CharacterController_setUp(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	btVector3 v = Physics3D::parse_btVector3(L, 2);
	character_controller->setUp(v);
	return 0;
}

int w_CharacterController_setMaxJumpHeight(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	float value = (float)luaL_checknumber(L, 2);
	character_controller->setMaxJumpHeight(value);
	return 0;
}

int w_CharacterController_setVelocityForTimeInterval(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	btVector3 v = Physics3D::parse_btVector3(L, 2);
	float timeInterval = (float)luaL_checknumber(L, 3);
	character_controller->setVelocityForTimeInterval(v, timeInterval);
	return 0;
}

int w_CharacterController_setStepHeight(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	float value = (float)luaL_checknumber(L, 2);
	character_controller->setStepHeight(value);
	return 0;
}

int w_CharacterController_getStepHeight(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	float value = character_controller->getStepHeight();
	lua_pushnumber(L, value);
	return 1;
}

int w_CharacterController_onGround(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	lua_pushboolean(L, character_controller->onGround());
	return 1;
}

int w_CharacterController_setMaxPenetrationDepth(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	float value = (float)luaL_checknumber(L, 2);
	character_controller->setMaxPenetrationDepth(value);
	return 0;
}

int w_CharacterController_getMaxPenetrationDepth(lua_State *L) {
	CharacterController *character_controller = luax_checkcharactercontroller(L, 1);
	float value = character_controller->getMaxPenetrationDepth();
	lua_pushnumber(L, value);
	return 1;
}

static const luaL_Reg w_CharacterController_functions[] =
{
	{ "setJumpSpeed", w_CharacterController_setJumpSpeed },
	{ "getJumpSpeed", w_CharacterController_getJumpSpeed },

	{ "jump", w_CharacterController_jump },
	{ "applyImpulse", w_CharacterController_applyImpulse },
	{ "setWalkDirection", w_CharacterController_setWalkDirection },
	{ "setGravity", w_CharacterController_setGravity },
	{ "setUp", w_CharacterController_setUp },
	{ "setMaxJumpHeight", w_CharacterController_setMaxJumpHeight },
	{ "setVelocityForTimeInterval", w_CharacterController_setVelocityForTimeInterval },

	{ "setStepHeight", w_CharacterController_setStepHeight },
	{ "getStepHeight", w_CharacterController_getStepHeight },

	{ "setMaxPenetrationDepth", w_CharacterController_setMaxPenetrationDepth },
	{ "getMaxPenetrationDepth", w_CharacterController_getMaxPenetrationDepth },
	{ "onGround", w_CharacterController_onGround },
	{ 0, 0 }
};

extern "C" int luaopen_bt_charactercontroller(lua_State *L) {
	return luax_register_type(L, &CharacterController::type, w_CharacterController_functions, nullptr);
}

}
}
}