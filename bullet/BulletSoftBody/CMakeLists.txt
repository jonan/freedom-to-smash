set(
  BULLET_SOFT_BODY_SRCS
  btSoftBody.cpp
  btSoftBodyConcaveCollisionAlgorithm.cpp
  btSoftBodyHelpers.cpp
  btSoftBodyRigidBodyCollisionConfiguration.cpp
  btSoftRigidCollisionAlgorithm.cpp
  btSoftRigidDynamicsWorld.cpp
  btSoftSoftCollisionAlgorithm.cpp
  )

add_library(BulletSoftBody STATIC ${BULLET_SOFT_BODY_SRCS})
