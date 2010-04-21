INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/bullet)

SET(LinearMath_SRCS
	btAlignedAllocator.cpp
	btConvexHull.cpp
	btGeometryUtil.cpp
	btQuickprof.cpp
	btSerializer.cpp
)

SET(LinearMath_HDRS
	btAabbUtil2.h
	btAlignedAllocator.h
	btAlignedObjectArray.h
	btConvexHull.h
	btDefaultMotionState.h
	btGeometryUtil.h
	btHashMap.h
	btIDebugDraw.h
	btList.h
	btMatrix3x3.h
	btMinMax.h
	btMotionState.h
	btPoolAllocator.h
	btQuadWord.h
	btQuaternion.h
	btQuickprof.h
	btRandom.h
	btScalar.h
	btSerializer.h
	btStackAlloc.h
	btTransform.h
	btTransformUtil.h
	btVector3.h
)

ADD_LIBRARY(LinearMath STATIC ${LinearMath_SRCS} ${LinearMath_HDRS})
