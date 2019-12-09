# bullet-physics-love2d-module

Module Bullet Physics for love2d engine, in development.

__Types and Functions:__
##### World
``` lua
local world = love.physics3d.newWorld(gx, gy, gz)
world:update(timeStep, maxSubSteps, fixedTimeStep)
world:update(timeStep, maxSubSteps)
tableofRaycastHit   = world:raycast(vec3Origin, vec3Direction, maxDistance)
world:addRigidBody(rbody)
world:addCharacterController(character)

world:removeRigidBody(rbody)
world:removeCharacterController(character)
```

##### CollisionObject (Base class for RigidBody and GhostObject)
``` lua
local collision_object 
collision_object:getTransform(table)
collision_object:setTransform(table)
collision_object:setUserData(table)
collision_object:getUserData(table)
collision_object:setCallback(function(tableofContactPoint, bodyA, bodyB) end)
collision_object:activate(force)
collision_object:isActive()
collision_object:setAnisotropicFriction(vec3Factor)
collision_object:setContactProcessingThreshold(value)
collision_object:setRestitution(value)
collision_object:setFriction(value)
collision_object:setRollingFriction(value)
collision_object:setSpinningFriction(value)
collision_object:setContactStiffnessAndDamping(stiffness, damping)
collision_object:setHitFraction(value)
collision_object:setCcdSweptSphereRadius(value)
collision_object:setCcdMotionThreshold(value)
shape               = collision_object:getCollisionShape()
xf, yf, zf          = collision_object:getAnisotropicFriction()
boolean             = collision_object:hasAnisotropicFriction()
value               = collision_object:getContactProcessingThreshold()
value               = collision_object:getRestitution()
value               = collision_object:getFriction()
value               = collision_object:getRollingFriction()
value               = collision_object:getSpinningFriction()
value               = collision_object:getContactStiffness()
value               = collision_object:getContactDamping()
value               = collision_object:getHitFraction()
value               = collision_object:getCcdSweptSphereRadius()
value               = collision_object:getCcdMotionThreshold()
value               = collision_object:getCcdSquareMotionThreshold()
boolean             = collision_object:canCollideWith()
```

##### RigidBody
``` lua
local rbody = love.physics3d.newRigidBody(shape, mass, matrix)
rbody:setDamping(lin, ang)
rbody:applyForce(vec3LinDamping, vec3AngDamping)
rbody:setAngularFactor(vec3Factor)
rbody:setLinearFactor(vec3Factor)
rbody:setKinematic(boolean)
rbody:setLinearVelocity(x, y, z) -- need fix: change to parse vec3
xv, yv, zv          = rbody:getLinearVelocity()
```

##### GhostObject
``` lua
love.physics3d.newGhostObject(shape)
```

##### Shapes
``` lua
love.physics3d.newBoxShape(halfSizeX, halfSizeY, halfSizeZ)
love.physics3d.newCapsuleShape(radius, height)
love.physics3d.newTriangleMeshShape(vertices, indices)
```

##### CharacterController
``` lua
local character_controller = love.physics.newCharacterController(ghost_object)
character_controller:jump(vec3)
character_controller:setWalkDirection(vec3)
character_controller:setGravity(vec3)
character_controller:setUp(vec3)
character_controller:setMaxJumpHeight(value)
character_controller:setMaxPenetrationDepth(value)
value               = character_controller:getMaxPenetrationDepth()
boolean             = character_controller:onGround()
```

__Others:__
##### ContactPoint
``` lua
x, y, z             = point:getPositionA()
x, y, z             = point:getPositionB()
value               = point:getDistance()
```

##### RaycastHit
``` lua
x, y, z             = hit:getPosition()
x, y, z             = hit:getNormal()
value               = hit:getDistance()
value               = hit:getHitFraction()
collision_body      = hit:getCollisionObject()
```
