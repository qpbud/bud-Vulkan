#include "commandPool/intelCpu/CommandPool.hpp"

namespace bud::vk::intelCpu {

VkResult CommandPool::Entry::createCommandPool(
    VkDevice device,
    const VkCommandPoolCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkCommandPool* pCommandPool) {
    auto& deviceInternal = static_cast<Device&>(*device);
    Allocator allocator{pAllocator, VK_SYSTEM_ALLOCATION_SCOPE_OBJECT};
    *pCommandPool = &allocator.construct<CommandPool>(deviceInternal, *pCreateInfo, allocator);
    return VK_SUCCESS;
}

CommandPool::CommandPool(
    Device& device,
    const VkCommandPoolCreateInfo& commandPoolCreateInfo,
    const Allocator& allocator)
    : CommandPoolCommon(device, commandPoolCreateInfo, allocator) {}

void CommandPool::trim(VkCommandPoolTrimFlags flags) {}

void CommandPool::reset(VkCommandPoolResetFlags flags) {}

}
