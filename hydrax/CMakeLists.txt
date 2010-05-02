set(
  Hydrax_SRCS
  Modules/ProjectedGrid/ProjectedGrid.cpp
  Modules/RadialGrid/RadialGrid.cpp
  Modules/SimpleGrid/SimpleGrid.cpp
  Modules/Module.cpp
  Noise/FFT/FFT.cpp
  Noise/Perlin/Perlin.cpp
  Noise/Noise.cpp
  CfgFileManager.cpp
  DecalsManager.cpp
  Enums.cpp
  GodRaysManager.cpp
  GPUNormalMapManager.cpp
  Help.cpp
  Hydrax.cpp
  Image.cpp
  MaterialManager.cpp
  Mesh.cpp
  Prerequisites.cpp
  RttManager.cpp
  TextureManager.cpp
  )

add_library(Hydrax STATIC ${Hydrax_SRCS})
