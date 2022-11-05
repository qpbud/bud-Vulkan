if(CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
  cmake_minimum_required(VERSION 3.21)
elseif(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")
  cmake_minimum_required(VERSION 3.12)
endif()

project(
  qp-Vulkan
  VERSION 0.1
  LANGUAGES CXX
)

add_subdirectory(src)
