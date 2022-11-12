set(CMAKE_CXX_STANDARD 17)

set(
  INSTANCE_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/instance/Entries.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/instance/Instance.cpp
)
set(
  PHYSICAL_DEVICE_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/physicalDevice/Entries.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/physicalDevice/PhysicalDevice.cpp
)
set(
  DEVICE_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/device/Entries.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/device/DeviceCommon.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/device/intelCpu/Device.cpp
)
set(
  QUEUE_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/queue/Entries.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/queue/QueueCommon.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/queue/intelCpu/Queue.cpp
)

add_library(
  vulkan_BUD
  SHARED
  ${INSTANCE_SOURCE}
  ${PHYSICAL_DEVICE_SOURCE}
  ${DEVICE_SOURCE}
  ${QUEUE_SOURCE}
)

target_include_directories(
  vulkan_BUD PRIVATE
  ${CMAKE_SOURCE_DIR}/third_party/Vulkan-Headers/include
  ${CMAKE_SOURCE_DIR}/src
)
