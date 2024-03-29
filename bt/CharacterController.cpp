#include "CharacterController.h"
#include "../love_luapi/Exception.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type CharacterController::type("btCharacterController", &Object::type);

CharacterController::CharacterController(GhostObject *ghost_object, btScalar step_height, btVector3 const &up)
{
	ghost_object_reference.set(ghost_object);
	Shape *shape = ghost_object->getCollisionShape();
	btCollisionShape *bt_shape = shape->getCollisionShape();
	if( !bt_shape->isConvex() ) {
		throw love::Exception("The shape of the character controller must be convex.");
	}	
	kinematic_character_controller = new btKinematicCharacterController(ghost_object->getObject(), (btConvexShape*)bt_shape, step_height, up);
}

CharacterController::~CharacterController() {
    delete kinematic_character_controller;
}

void
CharacterController::setJumpSpeed(btScalar jumpSpeed) {
	kinematic_character_controller->setJumpSpeed(jumpSpeed);
}

btScalar
CharacterController::getJumpSpeed() const {
	return kinematic_character_controller->getJumpSpeed();
}

void
CharacterController::jump(const btVector3 &v) {
	kinematic_character_controller->jump(v);
}

void
CharacterController::applyImpulse(const btVector3 &v) {
	kinematic_character_controller->applyImpulse(v);
}

void 
CharacterController::setWalkDirection(const btVector3 &direction) {
	kinematic_character_controller->setWalkDirection(direction);
}

void 
CharacterController::setGravity(const btVector3 &gravity) {
	kinematic_character_controller->setGravity(gravity);
}

void 
CharacterController::setUp(const btVector3 &up) {
	kinematic_character_controller->setUp(up);
}

void 
CharacterController::setMaxJumpHeight(btScalar value) {
	kinematic_character_controller->setMaxJumpHeight(value);
}

void 
CharacterController::setVelocityForTimeInterval(const btVector3 &velocity, btScalar timeInterval) {
	kinematic_character_controller->setVelocityForTimeInterval(velocity, timeInterval);
}

void
CharacterController::setStepHeight(btScalar h) {
	kinematic_character_controller->setStepHeight(h);
}

btScalar
CharacterController::getStepHeight() const {
	return kinematic_character_controller->getStepHeight();
}

void 
CharacterController::setMaxPenetrationDepth(btScalar value) {
	kinematic_character_controller->setMaxPenetrationDepth(value);
}

btScalar 
CharacterController::getMaxPenetrationDepth() const {
	return kinematic_character_controller->getMaxPenetrationDepth();
}

GhostObject *
CharacterController::getGhostObject() {
	return ghost_object_reference.get();
}

bool 
CharacterController::onGround() const {
	return kinematic_character_controller->onGround();
}

} // bt
} // physics3d
} // love
