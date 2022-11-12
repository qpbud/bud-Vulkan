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
    ADD_FUNCTION(vkEnumeratePhysicalDeviceGroups),
    ADD_FUNCTION(vkCreateDevice),
    ADD_FUNCTION(vkDestroyDevice),
    ADD_FUNCTION(vkGetDeviceQueue),
    ADD_FUNCTION(vkGetDeviceQueue2),
    ADD_FUNCTION(vkCreateCommandPool),
    ADD_FUNCTION(vkTrimCommandPool),
    ADD_FUNCTION(vkResetCommandPool),
    ADD_FUNCTION(vkDestroyCommandPool),
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

Instance::Instance(const VkInstanceCreateInfo& instanceCreateInfo, const Allocator& allocator)
    : Object<VkInstance_T>(allocator)
    , m_physicalDevices(&m_allocator)
    , m_physicalDeviceGroupsProperties(&m_allocator) {
    m_physicalDevices.emplace_back(PhysicalDevice::IntelCpu(), m_allocator);

    m_physicalDeviceGroupsProperties.resize(1);
    VkPhysicalDeviceGroupProperties& physicalDeviceGroupProperties = m_physicalDeviceGroupsProperties[0];
    physicalDeviceGroupProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES;
    physicalDeviceGroupProperties.pNext = nullptr;
    physicalDeviceGroupProperties.physicalDeviceCount = 1;
    physicalDeviceGroupProperties.physicalDevices[0] = &m_physicalDevices[0];
    physicalDeviceGroupProperties.subsetAllocation = VK_TRUE;
}

uint32_t Instance::getPhysicalDeviceCount() const {
    return static_cast<uint32_t>(m_physicalDevices.size());
}

PhysicalDevice& Instance::getPhysicalDevice(uint32_t index) {
    return m_physicalDevices[index];
}

uint32_t Instance::getPhysicalDeviceGroupCount() const {
    return static_cast<uint32_t>(m_physicalDeviceGroupsProperties.size());
}

const VkPhysicalDeviceGroupProperties& Instance::getPhysicalDeviceGroupProperties(uint32_t index) const {
    return m_physicalDeviceGroupsProperties[index];
}

}
