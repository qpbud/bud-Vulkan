#pragma once

#include <vulkan/vulkan.h>
#include "device/DeviceCommon.hpp"

namespace bud::vk::intelCpu {

class Device : public DeviceCommon {
public:
    struct Entry {
        static void destroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator);
        static void getDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue* pQueue);
        static void getDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2* pQueueInfo, VkQueue* pQueue);
    };

    Device(PhysicalDevice& physicalDevice, const VkDeviceCreateInfo& deviceCreateInfo, const Allocator& allocator);
};

}
