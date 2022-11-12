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
        static void trimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags);
        static VkResult resetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags);
        static void destroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator);
    };

    CommandPool(
        Device& device,
        const VkCommandPoolCreateInfo& commandPoolCreateInfo,
        const Allocator& allocator);

    void trim(VkCommandPoolTrimFlags flags) override;
    void reset(VkCommandPoolResetFlags flags) override;
};

}
