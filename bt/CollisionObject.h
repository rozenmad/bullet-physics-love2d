#ifndef LOVE_PHYSICS3D_BT_COLLISIONOBJECT_H
#define LOVE_PHYSICS3D_BT_COLLISIONOBJECT_H

#include "common/Object.h"
#include "common/runtime.h"
#include "common/Reference.h"

#include "btBulletDynamicsCommon.h"
#include "Shape.h"

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

	static love::Type type;

	struct ContactCallback {
		Reference *reference = nullptr;
		lua_State *L = nullptr;

		int report(World *world, ContactPair &pair, bool swapbody = false);
	};

	CollisionObject(btCollisionObject *collision_object, Shape *shape);
	virtual ~CollisionObject();
	
	void getTransform(btScalar *a16) const;
	void setTransform(btScalar *a16);

	int setUserData(lua_State *L);
	int getUserData(lua_State *L);

	int setCallbacks(lua_State *L);

	bool isStatic() const;
	bool isKinematic() const;
	bool isStaticOrKinematic() const;

	void activate(bool force) const;
	bool isActive() const;

	void setAnisotropicFriction(btVector3 const &anisotropicFriction);
	 
	void setContactProcessingThreshold(btScalar value);
	 
	void setRestitution(btScalar value);
	void setFriction(btScalar value);
	void setRollingFriction(btScalar value);
	void setSpinningFriction(btScalar value);
	void setContactStiffnessAndDamping(btScalar stiffness, btScalar damping);

	void setHitFraction(btScalar value);

	void setCcdSweptSphereRadius(btScalar value);

	void setCcdMotionThreshold(btScalar value);

	const btVector3 &getAnisotropicFriction() const;
	bool hasAnisotropicFriction() const;

	Shape *getCollisionShape();
	
	btScalar getContactProcessingThreshold() const;

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

protected:
	btCollisionObject *collision_object;
	World *world;

	UserData *userdata;
	ContactCallback contact_beg, contact_ong, contact_end;

	StrongRef<Shape> shape_reference;
};

} // bt
} // physics3d
} // love

#endif // LOVE_PHYSICS3D_BT_COLLISIONOBJECT_H
