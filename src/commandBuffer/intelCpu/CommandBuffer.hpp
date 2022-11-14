#pragma once

#include <vulkan/vulkan.h>
#include "CommandBuffer/CommandBufferCommon.hpp"

namespace bud::vk::intelCpu {

class CommandBuffer : public CommandBufferCommon {
public:
    CommandBuffer(CommandPool& commandPool, VkCommandBufferLevel level);

    VkResult reset(VkCommandBufferResetFlags flags) override;
    VkResult begin(const VkCommandBufferBeginInfo& beginInfo) override;
    VkResult end() override;
};

}
