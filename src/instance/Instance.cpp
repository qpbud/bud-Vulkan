#include "instance/Instance.hpp"
#include "device/DeviceCommon.hpp"

namespace bud::vk {

#define ADD_FUNCTION(name, real) \
    {#name, reinterpret_cast<PFN_vkVoidFunction>(real)}

const std::unordered_map<std::string_view, PFN_vkVoidFunction> Instance::s_globalCommands{
    ADD_FUNCTION(vkEnumerateInstanceVersion, &Instance::Entry::enumerateInstanceVersion),
    // ADD_FUNCTION(vkEnumerateInstanceExtensionProperties),
    // ADD_FUNCTION(vkEnumerateInstanceLayerProperties),
    ADD_FUNCTION(vkCreateInstance, &Instance::Entry::createInstance),
};

#undef ADD_FUNCTION

PFN_vkVoidFunction Instance::Entry::getInstanceProcAddr(VkInstance instance, const char* pName) {
    if (std::string_view(pName) == "vkGetInstanceProcAddr") {
        return reinterpret_cast<PFN_vkVoidFunction>(&Instance::Entry::getInstanceProcAddr);
    }
    if (!instance) {
        return s_globalCommands.at(pName);
    }
    auto& instanceInternal = static_cast<Instance&>(*instance);
    return instanceInternal.getProcAddr(pName);
}

VkResult Instance::Entry::enumerateInstanceVersion(uint32_t* pApiVersion) {
    *pApiVersion = VK_API_VERSION_1_3;
    return VK_SUCCESS;
}

VkResult Instance::Entry::createInstance(
    const VkInstanceCreateInfo* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkInstance* pInstance) {
    Allocator allocator{pAllocator, VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE};
    *pInstance = &allocator.construct<Instance>(*pCreateInfo, allocator);
    return VK_SUCCESS;
}

void Instance::Entry::destroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator) {
    if (instance != VK_NULL_HANDLE) {
        auto& instanceInternal = static_cast<Instance&>(*instance);
        Allocator allocator = instanceInternal.getAllocator();
        allocator.destruct(instanceInternal);
    }
}

Instance::Instance(const VkInstanceCreateInfo& instanceCreateInfo, const Allocator& allocator)
    : Object<VkInstance_T>(allocator)
    , m_dispatchableCommands()
    , m_physicalDevices(&m_allocator)
    , m_physicalDeviceGroupsProperties(&m_allocator) {
#define ADD_FUNCTION(name, real) \
    m_dispatchableCommands.insert(std::make_pair(#name, reinterpret_cast<PFN_vkVoidFunction>(real)))

    ADD_FUNCTION(vkGetDeviceProcAddr, vkGetDeviceProcAddr),
    ADD_FUNCTION(vkDestroyInstance, &Instance::Entry::destroyInstance),
    ADD_FUNCTION(vkEnumeratePhysicalDevices, &PhysicalDevice::Entry::enumeratePhysicalDevices),
    ADD_FUNCTION(vkGetPhysicalDeviceProperties, &PhysicalDevice::Entry::getPhysicalDeviceProperties),
    ADD_FUNCTION(vkGetPhysicalDeviceProperties2, &PhysicalDevice::Entry::getPhysicalDeviceProperties2),
    ADD_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties, &PhysicalDevice::Entry::getPhysicalDeviceQueueFamilyProperties),
    ADD_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties2, &PhysicalDevice::Entry::getPhysicalDeviceQueueFamilyProperties),
    ADD_FUNCTION(vkEnumeratePhysicalDeviceGroups, &PhysicalDevice::Entry::enumeratePhysicalDeviceGroups),
    ADD_FUNCTION(vkCreateDevice, &DeviceCommon::Entry::createDevice),
    ADD_FUNCTION(vkDestroyDevice, vkDestroyDevice),
    ADD_FUNCTION(vkGetDeviceQueue, vkGetDeviceQueue),
    ADD_FUNCTION(vkGetDeviceQueue2, vkGetDeviceQueue2),
    ADD_FUNCTION(vkCreateCommandPool, vkCreateCommandPool),
    ADD_FUNCTION(vkTrimCommandPool, vkTrimCommandPool),
    ADD_FUNCTION(vkResetCommandPool, vkResetCommandPool),
    ADD_FUNCTION(vkDestroyCommandPool, vkDestroyCommandPool),

#undef ADD_FUNCTION

    m_physicalDevices.emplace_back(PhysicalDevice::IntelCpu(), *this, m_allocator);

    m_physicalDeviceGroupsProperties.resize(1);
    VkPhysicalDeviceGroupProperties& physicalDeviceGroupProperties = m_physicalDeviceGroupsProperties[0];
    physicalDeviceGroupProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_GROUP_PROPERTIES;
    physicalDeviceGroupProperties.pNext = nullptr;
    physicalDeviceGroupProperties.physicalDeviceCount = 1;
    physicalDeviceGroupProperties.physicalDevices[0] = &m_physicalDevices[0];
    physicalDeviceGroupProperties.subsetAllocation = VK_TRUE;
}

PFN_vkVoidFunction Instance::getProcAddr(std::string_view name) const {
    return m_dispatchableCommands.at(name);
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
