#include "CollisionObject.h"
#include "ContactPoint.h"
#include "World.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type CollisionObject::type("btCollisionObject", &Object::type);

int CollisionObject::ContactCallback::report(World *world, 
	btPersistentManifold *manifold, 
	CollisionObject *a, 
	CollisionObject *b) 
{
	if( reference != nullptr && L != nullptr )
	{
		reference->push(L);
		int contacts = manifold->getNumContacts();
		lua_createtable(L, contacts, 0);
		int table_index = lua_gettop(L);
		for( int i = 0; i < contacts; i++ ) {
			ContactPoint *point;
			luax_catchexcept(L, [&](){ point = new ContactPoint(manifold->getContactPoint(i)); });
			luax_pushtype(L, point);
			point->release();
			lua_rawseti(L, table_index, i + 1);
		}
		luax_pushtype(L, a);
		luax_pushtype(L, b);
		lua_call(L, 3, 0);
	}
	return 0;
}

CollisionObject::CollisionObject(btCollisionObject *collision_object, Shape *shape) :
	collision_object(collision_object),
	world(nullptr),
	userdata(new UserData())
{
	userdata->obj = this;
	collision_object->setUserPointer((void*)userdata);

	contact_callback.reference = new Reference();
	shape_reference.set(shape);
}

CollisionObject::~CollisionObject() {
	if( userdata ) {
		if( userdata->reference ) {
			delete userdata->reference;
		}
		delete userdata;
	}
}

Shape *CollisionObject::getCollisionShape() {
	return shape_reference.get();
}

void CollisionObject::getTransform(btScalar *a16) const {
	auto &t = collision_object->getWorldTransform();
	t.getOpenGLMatrix(a16);
}

void CollisionObject::setTransform(btScalar *a16) {
	auto &t = collision_object->getWorldTransform();
	t.setFromOpenGLMatrix(a16);
}

int CollisionObject::setUserData(lua_State *L) {
	love::luax_assert_argc(L, 1, 1);

	if( userdata->reference == nullptr ) {
		userdata->reference = new Reference();
	}
	userdata->reference->ref(L);
	return 0;
}

int CollisionObject::getUserData(lua_State *L) {
	if( userdata != nullptr && userdata->reference != nullptr ) {
		userdata->reference->push(L);
	} else {
		lua_pushnil(L);
	}
	return 1;
}

int CollisionObject::setCallback(lua_State *L) {
	if( contact_callback.reference ) {
		contact_callback.reference->unref();
	}

	luaL_checktype(L, 1, LUA_TFUNCTION);
	lua_pushvalue(L, 1);
	contact_callback.reference = luax_refif(L, LUA_TFUNCTION);
	contact_callback.L = L;
	return 0;
}

bool CollisionObject::isStatic() const {
	return collision_object->isStaticObject();
}
 
bool CollisionObject::isKinematic() const {
	return collision_object->isKinematicObject();
}
 
bool CollisionObject::isStaticOrKinematic() const {
	return collision_object->isStaticOrKinematicObject();
}

void CollisionObject::setAnisotropicFriction(const btVector3 &anisotropicFriction) {
	collision_object->setAnisotropicFriction(anisotropicFriction);
}
 
void CollisionObject::setContactProcessingThreshold(btScalar value) {
	collision_object->setContactProcessingThreshold(value);
}

void CollisionObject::activate(bool force) const {
	collision_object->activate(force);
}
 
bool CollisionObject::isActive() const {
	return collision_object->isActive();
}
 
void CollisionObject::setRestitution(btScalar value) {
	collision_object->setRestitution(value);
}

void CollisionObject::setFriction(btScalar value) {
	collision_object->setFriction(value);
}

void CollisionObject::setRollingFriction(btScalar value) {
	collision_object->setRollingFriction(value);
}

void CollisionObject::setSpinningFriction(btScalar value) {
	collision_object->setSpinningFriction(value);
}

void CollisionObject::setContactStiffnessAndDamping(btScalar stiffness, btScalar damping) {
	collision_object->setContactStiffnessAndDamping(stiffness, damping);
}

void CollisionObject::setHitFraction(btScalar value) {
	collision_object->setHitFraction(value);
}

void CollisionObject::setCcdSweptSphereRadius(btScalar value) {
	collision_object->setCcdSweptSphereRadius(value);
}

void CollisionObject::setCcdMotionThreshold(btScalar value) {
	collision_object->setCcdMotionThreshold(value);
}

const btVector3 &CollisionObject::getAnisotropicFriction() const {
	return collision_object->getAnisotropicFriction();
}

bool CollisionObject::hasAnisotropicFriction() const {
	return collision_object->hasAnisotropicFriction();
}

btScalar CollisionObject::getContactProcessingThreshold() const {
	return collision_object->getContactProcessingThreshold();
}

btScalar CollisionObject::getRestitution() const {
	return collision_object->getRestitution();
}

btScalar CollisionObject::getFriction() const {
	return collision_object->getFriction();
}

btScalar CollisionObject::getRollingFriction() const {
	return collision_object->getRollingFriction();
}

btScalar CollisionObject::getSpinningFriction() const {
	return collision_object->getSpinningFriction();
}

btScalar CollisionObject::getContactStiffness() const {
	return collision_object->getContactStiffness();
}

btScalar CollisionObject::getContactDamping() const {
	return collision_object->getContactDamping();
}

btScalar CollisionObject::getHitFraction() const {
	return collision_object->getHitFraction();
}

btScalar CollisionObject::getCcdSweptSphereRadius() const {
	return collision_object->getCcdSweptSphereRadius();
}

btScalar CollisionObject::getCcdMotionThreshold() const {
	return collision_object->getCcdMotionThreshold();
}

btScalar CollisionObject::getCcdSquareMotionThreshold() const {
	return collision_object->getCcdSquareMotionThreshold();
}

bool CollisionObject::canCollideWith(CollisionObject const *other) const {
	return collision_object->checkCollideWith(other->collision_object);
}

} // bt
} // physics3d
} // love
