#pragma once

#include <vulkan/vulkan.h>
#include "device/DeviceCommon.hpp"

namespace bud::vk::intelCpu {

class Device : public DeviceCommon {
public:
    Device(PhysicalDevice& physicalDevice, const VkDeviceCreateInfo& deviceCreateInfo, const Allocator& allocator);
};

}
