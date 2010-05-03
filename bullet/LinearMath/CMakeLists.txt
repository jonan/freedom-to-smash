set(
  LINEAR_MATH_SRCS
  btAlignedAllocator.cpp
  btConvexHull.cpp
  btGeometryUtil.cpp
  btQuickprof.cpp
  btSerializer.cpp
  )

add_library(LinearMath STATIC ${LINEAR_MATH_SRCS})
