#include <vulkan/vulkan.h>
#include "instance/Instance.hpp"

VKAPI_ATTR VkResult VKAPI_CALL vkCreateInstance(
    const VkInstanceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkInstance* pInstance) {
    *pInstance = &bud::vk::Instance::create(*pCreateInfo);
    return VK_SUCCESS;
}
