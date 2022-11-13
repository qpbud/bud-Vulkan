#pragma once

#include <vulkan/vulkan.h>
#include "device/intelCpu/Device.hpp"
#include "commandPool/CommandPoolCommon.hpp"

namespace bud::vk::intelCpu {

class CommandPool : public CommandPoolCommon {
public:
    struct Entry {
        static VkResult createCommandPool(
            VkDevice device,
            const VkCommandPoolCreateInfo* pCreateInfo,
            const VkAllocationCallbacks* pAllocator,
            VkCommandPool* pCommandPool);
    };

    CommandPool(
        Device& device,
        const VkCommandPoolCreateInfo& commandPoolCreateInfo,
        const Allocator& allocator);

    void trim(VkCommandPoolTrimFlags flags) override;
    void reset(VkCommandPoolResetFlags flags) override;
};

}
