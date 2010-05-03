set(
  BULLET_MULTI_THREADED_SRCS
  SpuFakeDma.cpp
  SpuLibspe2Support.cpp
  btThreadSupportInterface.cpp

  Win32ThreadSupport.cpp
  PosixThreadSupport.cpp
  SequentialThreadSupport.cpp
  SpuSampleTaskProcess.cpp

  SpuCollisionObjectWrapper.cpp
  SpuCollisionTaskProcess.cpp
  SpuGatheringCollisionDispatcher.cpp
  SpuContactManifoldCollisionAlgorithm.cpp

  btParallelConstraintSolver.cpp

  SpuNarrowPhaseCollisionTask/boxBoxDistance.cpp
  SpuNarrowPhaseCollisionTask/SpuContactResult.cpp
  SpuNarrowPhaseCollisionTask/SpuMinkowskiPenetrationDepthSolver.cpp
  SpuNarrowPhaseCollisionTask/SpuGatheringCollisionTask.cpp
  SpuNarrowPhaseCollisionTask/SpuCollisionShapes.cpp

  btGpu3DGridBroadphase.cpp

  MiniCL.cpp
  MiniCLTaskScheduler.cpp
  MiniCLTask/MiniCLTask.cpp
  )

add_library(BulletMultiThreaded STATIC ${BULLET_MULTI_THREADED_SRCS})
