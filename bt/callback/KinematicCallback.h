#ifndef LOVE_PHYSICS3D_BT_KINEMATICCALLBACK_H
#define LOVE_PHYSICS3D_BT_KINEMATICCALLBACK_H

#include "../../love_luapi/Object.h"
#include "btBulletDynamicsCommon.h"

namespace love
{
namespace physics3d
{
namespace bt
{

class btKinematicClosestNotMeConvexResultCallback : public btCollisionWorld::ClosestConvexResultCallback
{
public:
	btKinematicClosestNotMeConvexResultCallback(btCollisionObject* me, const btVector3& up, btScalar minSlopeDot)
		: btCollisionWorld::ClosestConvexResultCallback(btVector3(0.0, 0.0, 0.0), btVector3(0.0, 0.0, 0.0)), m_me(me), m_up(up), m_minSlopeDot(minSlopeDot)
	{
	}

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject == m_me)
			return btScalar(1.0);

		if (!convexResult.m_hitCollisionObject->hasContactResponse())
			return btScalar(1.0);

		btVector3 hitNormalWorld;
		if (normalInWorldSpace)
		{
			hitNormalWorld = convexResult.m_hitNormalLocal;
		}
		else
		{
			///need to transform normal into worldspace
			hitNormalWorld = convexResult.m_hitCollisionObject->getWorldTransform().getBasis() * convexResult.m_hitNormalLocal;
		}

		btScalar dotUp = m_up.dot(hitNormalWorld);
		if (dotUp < m_minSlopeDot)
		{
			return btScalar(1.0);
		}

		return ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
	}

protected:
	btCollisionObject* m_me;
	const btVector3 m_up;
	btScalar m_minSlopeDot;
};

class KinematicCallback : public Object {
public:
	static love::Type type;

	KinematicCallback(btCollisionObject* me, const btVector3& up, btScalar minSlopeDot) :
		callback(me, up, minSlopeDot)
	{}

	btVector3 getHitNormal() const {
		return callback.m_hitNormalWorld;
	}

	btVector3 getHitPoint() const {
		return callback.m_hitPointWorld;
	}

	bool hasHit() const {
		return callback.hasHit();
	}

	btScalar closestHitFraction() {
		return callback.m_closestHitFraction;
	}

	btKinematicClosestNotMeConvexResultCallback callback;
};

}
}
}


#endif