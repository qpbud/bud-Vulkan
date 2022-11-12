#pragma once

#include <vulkan/vulkan.h>
#include "device/DeviceCommon.hpp"

namespace bud::vk::intelCpu {

class Device : public DeviceCommon {
public:
    static void destroy(VkDevice device, const VkAllocationCallbacks* allocator);
    static void getQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* queue);
    static void getQueue2(VkDevice device, const VkDeviceQueueInfo2* queueInfo, VkQueue* queue);

    Device(PhysicalDevice& physicalDevice, const VkDeviceCreateInfo& deviceCreateInfo, const Allocator& allocator);
};

}
