#ifndef LOVE_PHYSICS3D_BT_COLLISIONOBJECT_H
#define LOVE_PHYSICS3D_BT_COLLISIONOBJECT_H

#include "../love_luapi/Object.h"
#include "../love_luapi/runtime.h"
#include "../love_luapi/Reference.h"
#include "../love_luapi/StringMap.h"

#include "btBulletDynamicsCommon.h"
#include "shapes/Shape.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class CollisionObject;
class ContactPair;

struct UserData
{
	CollisionObject *obj = nullptr;
	Reference *reference = nullptr;
	int timestamp = 0;
};

class CollisionObject : public Object {
public:
	friend class World;

	enum ContactNames {
		START_CONTACT,
		ONGOING_CONTACT,
		END_CONTACT,
		CONTACT_MAX_ENUM,
	};

	static love::Type type;

	struct ContactCallback {
		Reference *reference = nullptr;
		lua_State *L = nullptr;

		int report(World *world, ContactPair &pair);
	};

	void getTransform(lua_State *L, int idx) const;
	void setTransform(lua_State *L, int idx);

	int setUserData(lua_State *L);
	int getUserData(lua_State *L);

	int setCallback(lua_State *L);

	CollisionObject(btCollisionObject *collision_object, Shape *shape);
	virtual ~CollisionObject();

	const btVector3 &getAnisotropicFriction() const;
	void setAnisotropicFriction(btVector3 const &anisotropicFriction);
	bool hasAnisotropicFriction() const;

	void setContactProcessingThreshold(btScalar contactProcessingThreshold);
	btScalar getContactProcessingThreshold() const;

	bool isStaticObject() const;
	bool isKinematicObject() const;
	bool isStaticOrKinematicObject() const;
	
	bool hasContactResponse() const;

	void setCollisionShape(Shape *collisionShape);
	Shape *getCollisionShape();

	void activate(bool force) const;
	bool isActive() const;
	 
	void setRestitution(btScalar value);
	void setFriction(btScalar value);
	void setRollingFriction(btScalar value);
	void setSpinningFriction(btScalar value);
	void setContactStiffnessAndDamping(btScalar stiffness, btScalar damping);

	void setHitFraction(btScalar value);

	void setCcdSweptSphereRadius(btScalar value);

	void setCcdMotionThreshold(btScalar value);

	btScalar getRestitution() const;
	btScalar getFriction() const;
	btScalar getRollingFriction() const;
	btScalar getSpinningFriction() const;
	btScalar getContactStiffness() const;
	btScalar getContactDamping() const;

	btScalar getHitFraction() const;
	 
	btScalar getCcdSweptSphereRadius() const;
	btScalar getCcdMotionThreshold() const;
	btScalar getCcdSquareMotionThreshold() const;
	
	bool canCollideWith(CollisionObject const *other) const;

	static bool getContactConstant(const char *in, ContactNames &out);
	static bool getContactConstant(ContactNames in, const char *&out);
	static std::vector<std::string> getContactConstants(ContactNames);

	btCollisionObject *getCollisionObject() {
		return collision_object;
	}

protected:
	btCollisionObject *collision_object;
	World *world;

	UserData *userdata;
	ContactCallback contacts[3];

	StrongRef<Shape> shape_reference;

	static StringMap<ContactNames, CONTACT_MAX_ENUM>::Entry contactNamesEntries[];
	static StringMap<ContactNames, CONTACT_MAX_ENUM> contactNames;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_COLLISIONOBJECT_H
