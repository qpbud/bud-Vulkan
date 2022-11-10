#include "instance/Instance.hpp"

namespace bud::vk {

Instance& Instance::create(const VkInstanceCreateInfo& instanceCreateInfo, const VkAllocationCallbacks* allocatorCallbacks) {
    Allocator allocator{allocatorCallbacks, VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE};
    return allocator.construct<Instance>(instanceCreateInfo, allocator);
}

void Instance::destroy(Instance& instance) {
    Allocator allocator = instance.getAllocator();
    allocator.destruct(instance);
}

Instance::Instance(const VkInstanceCreateInfo& instanceCreateInfo, Allocator allocator)
    : Object<VkInstance_T>()
    , m_allocator(allocator)
    , m_physicalDevices(&allocator) {
    m_physicalDevices.emplace_back();
}

uint32_t Instance::getPhysicalDeviceCount() const {
    return static_cast<uint32_t>(m_physicalDevices.size());
}

PhysicalDevice& Instance::getPhysicalDevice(uint32_t index) {
    return m_physicalDevices[index];
}

Allocator Instance::getAllocator() const {
    return m_allocator;
}

}
