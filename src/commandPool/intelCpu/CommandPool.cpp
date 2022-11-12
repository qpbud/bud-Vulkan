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

void CommandPool::Entry::trimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) {
    auto& commandPoolInternal = static_cast<CommandPool&>(*commandPool);
    commandPoolInternal.trim(flags);
}

VkResult CommandPool::Entry::resetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) {
    auto& commandPoolInternal = static_cast<CommandPool&>(*commandPool);
    commandPoolInternal.reset(flags);
    return VK_SUCCESS;
}

void CommandPool::Entry::destroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator) {
    if (commandPool != VK_NULL_HANDLE) {
        auto& commandPoolInternal = static_cast<CommandPool&>(*commandPool);
        Allocator allocator = commandPoolInternal.getAllocator();
        allocator.destruct<CommandPool>(commandPoolInternal);
    }
}

CommandPool::CommandPool(
    Device& device,
    const VkCommandPoolCreateInfo& commandPoolCreateInfo,
    const Allocator& allocator)
    : CommandPoolCommon(device, commandPoolCreateInfo, allocator) {}

void CommandPool::trim(VkCommandPoolTrimFlags flags) {}

void CommandPool::reset(VkCommandPoolResetFlags flags) {}

}
