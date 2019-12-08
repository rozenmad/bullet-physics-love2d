# bullet-physics-love2d-module

Module Bullet Physics for love2d engine, in development.

__Types and Functions:__
##### World
``` lua
local world = love.physics3d.newWorld(gx, gy, gz)
world:update()
world:raycast()
world:addRigidBody()
world:addCollisionObject()
world:addCharacterController()
```

##### CollisionObject (Base class for RigidBody and GhostObject)
``` lua
local collision_object 
collision_object:getTransform()
collision_object:setTransform()
collision_object:setUserData()
collision_object:getUserData()
collision_object:setCallback()
collision_object:activate()
collision_object:isActive()
collision_object:setAnisotropicFriction()
collision_object:setContactProcessingThreshold()
collision_object:setRestitution()
collision_object:setFriction()
collision_object:setRollingFriction()
collision_object:setSpinningFriction()
collision_object:setContactStiffnessAndDamping()
collision_object:setHitFraction()
collision_object:setCcdSweptSphereRadius()
collision_object:setCcdMotionThreshold()
collision_object:getAnisotropicFriction()
collision_object:hasAnisotropicFriction()
collision_object:getContactProcessingThreshold()
collision_object:getRestitution()
collision_object:getFriction()
collision_object:getRollingFriction()
collision_object:getSpinningFriction()
collision_object:getContactStiffness()
collision_object:getContactDamping()
collision_object:getHitFraction()
collision_object:getCcdSweptSphereRadius()
collision_object:getCcdMotionThreshold()
collision_object:getCcdSquareMotionThreshold()
collision_object:canCollideWith()
```

##### RigidBody
``` lua
local rbody = love.physics3d.newRigidBody(shape, mass, matrix)
rbody:setDamping()
rbody:applyForce()
rbody:setAngularFactor()
rbody:setLinearFactor()
rbody:setKinematic()
rbody:getLinearVelocity()
rbody:setLinearVelocity()
```

##### GhostObject
``` lua
love.physics3d.newGhostObject(shape)
```

##### Shapes
``` lua
love.physics3d.newBoxShape(half_size_vec3)
love.physics3d.newCapsuleShape(radius, height)
love.physics3d.newTriangleMeshShape(vertices, indices)
```

##### CharacterController
``` lua
local character_controller = love.physics.newCharacterController(ghost_object)
character_controller:jump()
character_controller:setWalkDirection()
character_controller:setGravity()
character_controller:setUp()
character_controller:setMaxJumpHeight()
character_controller:setMaxPenetrationDepth()
character_controller:getMaxPenetrationDepth()
character_controller:onGround()
```

__Others:__
##### ContactPoint
``` lua
point:getPositionA()
point:getPositionB()
point:getDistance()
```

##### RaycastHit
``` lua
hit:getPosition()
hit:getNormal()
hit:getDistance()
hit:getHitFraction()
hit:getCollisionObject()
```
