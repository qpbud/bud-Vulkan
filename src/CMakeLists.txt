set(CMAKE_CXX_STANDARD 17)

set(
  INSTANCE_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/instance/Instance.cpp
)
set(
  PHYSICAL_DEVICE_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/physicalDevice/PhysicalDevice.cpp
)
set(
  DEVICE_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/device/DeviceCommon.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/device/intelCpu/Device.cpp
)
set(
  QUEUE_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/queue/QueueCommon.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/queue/intelCpu/Queue.cpp
)
set(
  COMMAND_POOL_SOURCE
  ${CMAKE_CURRENT_SOURCE_DIR}/commandPool/CommandPoolCommon.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/commandPool/intelCpu/CommandPool.cpp
)

add_library(
  vulkan_BUD
  SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/Entries.cpp
  ${INSTANCE_SOURCE}
  ${PHYSICAL_DEVICE_SOURCE}
  ${DEVICE_SOURCE}
  ${QUEUE_SOURCE}
  ${COMMAND_POOL_SOURCE}
)

target_include_directories(
  vulkan_BUD PRIVATE
  ${CMAKE_SOURCE_DIR}/third_party/Vulkan-Headers/include
  ${CMAKE_SOURCE_DIR}/src
)
