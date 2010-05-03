set(
  BULLET_DYNAMICS_SRCS
  Character/btKinematicCharacterController.cpp
  ConstraintSolver/btConeTwistConstraint.cpp
  ConstraintSolver/btContactConstraint.cpp
  ConstraintSolver/btGeneric6DofConstraint.cpp
  ConstraintSolver/btGeneric6DofSpringConstraint.cpp
  ConstraintSolver/btHinge2Constraint.cpp
  ConstraintSolver/btHingeConstraint.cpp
  ConstraintSolver/btPoint2PointConstraint.cpp
  ConstraintSolver/btSequentialImpulseConstraintSolver.cpp
  ConstraintSolver/btSliderConstraint.cpp
  ConstraintSolver/btSolve2LinearConstraint.cpp
  ConstraintSolver/btTypedConstraint.cpp
  ConstraintSolver/btUniversalConstraint.cpp
  Dynamics/btContinuousDynamicsWorld.cpp
  Dynamics/btDiscreteDynamicsWorld.cpp
  Dynamics/btRigidBody.cpp
  Dynamics/btSimpleDynamicsWorld.cpp
  Dynamics/Bullet-C-API.cpp
  Vehicle/btRaycastVehicle.cpp
  Vehicle/btWheelInfo.cpp
  )

add_library(BulletDynamics STATIC ${BULLET_DYNAMICS_SRCS})
