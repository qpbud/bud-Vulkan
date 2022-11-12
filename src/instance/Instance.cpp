#include "instance/Instance.hpp"

namespace bud::vk {

#define ADD_FUNCTION(name) \
    {#name, reinterpret_cast<PFN_vkVoidFunction>(name)}

const std::unordered_map<std::string_view, PFN_vkVoidFunction> Instance::s_globalCommands{
    ADD_FUNCTION(vkEnumerateInstanceVersion),
    // ADD_FUNCTION(vkEnumerateInstanceExtensionProperties),
    // ADD_FUNCTION(vkEnumerateInstanceLayerProperties),
    ADD_FUNCTION(vkCreateInstance),
};

const std::unordered_map<std::string_view, PFN_vkVoidFunction> Instance::s_dispatchableCommands{
    ADD_FUNCTION(vkGetInstanceProcAddr),
    ADD_FUNCTION(vkGetDeviceProcAddr),
    ADD_FUNCTION(vkDestroyInstance),
    ADD_FUNCTION(vkEnumeratePhysicalDevices),
    ADD_FUNCTION(vkGetPhysicalDeviceProperties),
    ADD_FUNCTION(vkGetPhysicalDeviceProperties2),
    ADD_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties),
    ADD_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties2),
};

#undef ADD_FUNCTION

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
    m_physicalDevices.emplace_back(PhysicalDevice::Cpu());
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
