INCLUDE_DIRECTORIES(
	${PROJECT_SOURCE_DIR}/bullet
	${PROJECT_SOURCE_DIR}/bullet/BulletMultiThreaded/vectormath/scalar/cpp
)

ADD_LIBRARY(BulletMultiThreaded STATIC
		PlatformDefinitions.h
		SpuFakeDma.cpp
		SpuFakeDma.h
		SpuDoubleBuffer.h
		SpuLibspe2Support.cpp
		SpuLibspe2Support.h
		btThreadSupportInterface.cpp
		btThreadSupportInterface.h

		Win32ThreadSupport.cpp
		Win32ThreadSupport.h
		PosixThreadSupport.cpp
		PosixThreadSupport.h
		SequentialThreadSupport.cpp
		SequentialThreadSupport.h
		SpuSampleTaskProcess.h
		SpuSampleTaskProcess.cpp

		SpuCollisionObjectWrapper.cpp
		SpuCollisionObjectWrapper.h
		SpuCollisionTaskProcess.h
		SpuCollisionTaskProcess.cpp
		SpuGatheringCollisionDispatcher.h
		SpuGatheringCollisionDispatcher.cpp
		SpuContactManifoldCollisionAlgorithm.cpp
		SpuContactManifoldCollisionAlgorithm.h

		btParallelConstraintSolver.cpp
		btParallelConstraintSolver.h

		SpuNarrowPhaseCollisionTask/Box.h
		SpuNarrowPhaseCollisionTask/boxBoxDistance.cpp
		SpuNarrowPhaseCollisionTask/boxBoxDistance.h
		SpuNarrowPhaseCollisionTask/SpuContactResult.cpp
		SpuNarrowPhaseCollisionTask/SpuContactResult.h
		SpuNarrowPhaseCollisionTask/SpuMinkowskiPenetrationDepthSolver.cpp
		SpuNarrowPhaseCollisionTask/SpuMinkowskiPenetrationDepthSolver.h
		SpuNarrowPhaseCollisionTask/SpuConvexPenetrationDepthSolver.h
		SpuNarrowPhaseCollisionTask/SpuPreferredPenetrationDirections.h
		SpuNarrowPhaseCollisionTask/SpuGatheringCollisionTask.cpp
		SpuNarrowPhaseCollisionTask/SpuGatheringCollisionTask.h
		SpuNarrowPhaseCollisionTask/SpuCollisionShapes.cpp
		SpuNarrowPhaseCollisionTask/SpuCollisionShapes.h

#Some GPU related stuff, mainly CUDA and perhaps OpenCL
		btGpu3DGridBroadphase.cpp
		btGpu3DGridBroadphase.h
		btGpu3DGridBroadphaseSharedCode.h
		btGpu3DGridBroadphaseSharedDefs.h
		btGpu3DGridBroadphaseSharedTypes.h
		btGpuDefines.h
		btGpuUtilsSharedCode.h
		btGpuUtilsSharedDefs.h

#MiniCL provides a small subset of OpenCL
		MiniCL.cpp
		MiniCLTaskScheduler.cpp
		MiniCLTaskScheduler.h
		MiniCLTask/MiniCLTask.cpp
		MiniCLTask/MiniCLTask.h
		../MiniCL/cl.h
		../MiniCL/cl_gl.h
		../MiniCL/cl_platform.h
		../MiniCL/cl_MiniCL_Defs.h
)
