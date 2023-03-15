#include "CollisionObject.h"
#include "ContactPoint.h"
#include "World.h"
#include "ContactPair.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type CollisionObject::type("btCollisionObject", &Object::type);

int CollisionObject::ContactCallback::report(World *world, ContactPair &pair) 
{
	if( reference != nullptr && L != nullptr ) {
		reference->push(L);
		int contacts = pair.getContactPointsCount();
		lua_createtable(L, contacts, 0);

		int table_index = lua_gettop(L);
		for( int i = 0; i < contacts; i++ ) {
			luax_pushtype(L, pair.getContactPoint(i));
			lua_rawseti(L, table_index, i + 1);
		}
		luax_pushtype(L, pair.getBodyA());
		luax_pushtype(L, pair.getBodyB());

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

	shape_reference.set(shape);
}

CollisionObject::~CollisionObject() {
	if( userdata ) {
		if( userdata->reference ) {
			delete userdata->reference;
		}
		delete userdata;
	}
	for( int i = 0; i < 3; i++ ) {
		if( contacts[i].reference ) {
			delete contacts[i].reference;
			contacts[i].reference = nullptr;
		}
	}
}

void CollisionObject::setAnisotropicFriction(const btVector3 &anisotropicFriction) {
	collision_object->setAnisotropicFriction(anisotropicFriction);
}

const btVector3 &CollisionObject::getAnisotropicFriction() const {
	return collision_object->getAnisotropicFriction();
}

bool CollisionObject::hasAnisotropicFriction() const {
	return collision_object->hasAnisotropicFriction();
}

void CollisionObject::setContactProcessingThreshold(btScalar contactProcessingThreshold) {
	collision_object->setContactProcessingThreshold(contactProcessingThreshold);
}

btScalar CollisionObject::getContactProcessingThreshold() const {
	return collision_object->getContactProcessingThreshold();
}

bool CollisionObject::isStaticObject() const {
	return collision_object->isStaticObject();
}
 
bool CollisionObject::isKinematicObject() const {
	return collision_object->isKinematicObject();
}
 
bool CollisionObject::isStaticOrKinematicObject() const {
	return collision_object->isStaticOrKinematicObject();
}

bool CollisionObject::hasContactResponse() const {
	return collision_object->hasContactResponse();
}

void CollisionObject::setCollisionShape(Shape *collisionShape) {
	shape_reference.set(collisionShape);
}

Shape *CollisionObject::getCollisionShape() {
	return shape_reference.get();
}

void CollisionObject::getTransform(lua_State *L, int idx) const {
	btScalar a16[16];
	auto &t = collision_object->getWorldTransform();
	t.getOpenGLMatrix(a16);
	if( lua_istable(L, idx) ) {
		for( int i = 0; i < 16; i++ ) {
			lua_pushnumber(L, a16[i]);
			lua_rawseti(L, idx, i+1);
		}
	}
}

void CollisionObject::setTransform(lua_State *L, int idx) {
	btScalar a16[16];
	if( lua_istable(L, idx) ) {
		for( int i = 0; i < 16; i++ ) {
			lua_rawgeti(L, idx, i+1);
			a16[i] = (float)luaL_checknumber(L, -1);
			lua_pop(L, 1);
		}
	}
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
	const char *callbackname = lua_tostring(L, 1);
	lua_remove(L, 1);
	CollisionObject::ContactNames name;
	if (!CollisionObject::getContactConstant(callbackname, name))
		return luax_enumerror(L, "contact name", CollisionObject::getContactConstants(name), callbackname);

	ContactCallback &callback = contacts[name];

	if( callback.reference ) {
		delete callback.reference;
		callback.reference = nullptr;
	}

	if( !lua_isnoneornil(L, 1) ) {
		lua_pushvalue(L, 1);
		callback.reference = luax_refif(L, LUA_TFUNCTION);
		callback.L = L;
	}
	return 0;
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

bool CollisionObject::getContactConstant(const char *in, ContactNames &out)
{
	return contactNames.find(in, out);
}

bool CollisionObject::getContactConstant(ContactNames in, const char *&out)
{
	return contactNames.find(in, out);
}

std::vector<std::string> CollisionObject::getContactConstants(ContactNames)
{
	return contactNames.getNames();
}

StringMap<CollisionObject::ContactNames, CollisionObject::CONTACT_MAX_ENUM>::Entry CollisionObject::contactNamesEntries[] =
{
	{ "start",   START_CONTACT   },
	{ "ongoing", ONGOING_CONTACT },
	{ "end",     END_CONTACT     },
};

StringMap<CollisionObject::ContactNames, CollisionObject::CONTACT_MAX_ENUM> CollisionObject::contactNames(CollisionObject::contactNamesEntries, sizeof(CollisionObject::contactNamesEntries));

} // bt
} // physics3d
} // love
