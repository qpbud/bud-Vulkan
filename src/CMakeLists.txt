set(CMAKE_CXX_STANDARD 17)

set(
  INSTANCE_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/instance/Entries.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/instance/Instance.cpp
)

add_library(
  vulkan_BUD
  SHARED
  ${INSTANCE_SOURCE}
)

target_include_directories(
  vulkan_BUD PRIVATE
  ${CMAKE_SOURCE_DIR}/third_party/Vulkan-Headers/include
  ${CMAKE_SOURCE_DIR}/src
)
