#pragma once

#include <stdexcept>
#include <unordered_map>
#include <string_view>
#include <vulkan/vulkan.h>

namespace bud::vk {

class Except : public std::exception {
    static const std::unordered_map<VkResult, std::string_view> s_res2Str;

    VkResult m_res;
public:
    Except(VkResult res) noexcept : std::exception(), m_res(res) {}

    const char* what() const noexcept override {
        return s_res2Str.at(m_res).data();
    }

    VkResult res() const noexcept {
        return m_res;
    }
};

inline const std::unordered_map<VkResult, std::string_view> Except::s_res2Str{
    {VK_SUCCESS, "VK_SUCCESS"},
    {VK_NOT_READY, "VK_NOT_READY"},
    {VK_TIMEOUT, "VK_TIMEOUT"},
    {VK_EVENT_SET, "VK_EVENT_SET"},
    {VK_EVENT_RESET, "VK_EVENT_RESET"},
    {VK_INCOMPLETE, "VK_INCOMPLETE"},
    {VK_ERROR_OUT_OF_HOST_MEMORY, "VK_ERROR_OUT_OF_HOST_MEMORY"},
    {VK_ERROR_OUT_OF_DEVICE_MEMORY, "VK_ERROR_OUT_OF_DEVICE_MEMORY"},
    {VK_ERROR_INITIALIZATION_FAILED, "VK_ERROR_INITIALIZATION_FAILED"},
    {VK_ERROR_DEVICE_LOST, "VK_ERROR_DEVICE_LOST"},
    {VK_ERROR_MEMORY_MAP_FAILED, "VK_ERROR_MEMORY_MAP_FAILED"},
    {VK_ERROR_LAYER_NOT_PRESENT, "VK_ERROR_LAYER_NOT_PRESENT"},
    {VK_ERROR_INCOMPATIBLE_DRIVER, "VK_ERROR_INCOMPATIBLE_DRIVER"},
    {VK_ERROR_TOO_MANY_OBJECTS, "VK_ERROR_TOO_MANY_OBJECTS"},
    {VK_ERROR_FORMAT_NOT_SUPPORTED, "VK_ERROR_FORMAT_NOT_SUPPORTED"},
    {VK_ERROR_FRAGMENTED_POOL, "VK_ERROR_FRAGMENTED_POOL"},
    {VK_ERROR_UNKNOWN, "VK_ERROR_UNKNOWN"},
    {VK_ERROR_OUT_OF_POOL_MEMORY, "VK_ERROR_OUT_OF_POOL_MEMORY"},
    {VK_ERROR_INVALID_EXTERNAL_HANDLE, "VK_ERROR_INVALID_EXTERNAL_HANDLE"},
    {VK_ERROR_FRAGMENTATION, "VK_ERROR_FRAGMENTATION"},
    {VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS, "VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS"},
    {VK_PIPELINE_COMPILE_REQUIRED, "VK_PIPELINE_COMPILE_REQUIRED"},
};

}
