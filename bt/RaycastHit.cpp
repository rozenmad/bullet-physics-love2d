#include "RaycastHit.h"

namespace love
{
namespace physics3d
{
namespace bt
{

love::Type RaycastHit::type("btRaycastHit", &Object::type);

RaycastHit::RaycastHit(btCollisionWorld::AllHitsRayResultCallback &ray_callback, int i, btVector3 const &origin) {
	position = ray_callback.m_hitPointWorld[i];
    normal = ray_callback.m_hitNormalWorld[i];
    distance = origin.distance(position);
    hit_fraction = ray_callback.m_closestHitFraction;
    object = ((UserData*)ray_callback.m_collisionObjects[i]->getUserPointer())->obj;
}

RaycastHit::~RaycastHit() {
}

} // bt
} // physics3d
} // love
