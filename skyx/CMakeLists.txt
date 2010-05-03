set(
  SKYX_SRCS
  VClouds/DataManager.cpp
  VClouds/Ellipsoid.cpp
  VClouds/FastFakeRandom.cpp
  VClouds/GeometryBlock.cpp
  VClouds/GeometryManager.cpp
  VClouds/VClouds.cpp
  AtmosphereManager.cpp
  CloudsManager.cpp
  ColorGradient.cpp
  GPUManager.cpp
  MeshManager.cpp
  MoonManager.cpp
  Prerequisites.cpp
  SkyX.cpp
  VCloudsManager.cpp
  )

add_library(SkyX STATIC ${SKYX_SRCS})
