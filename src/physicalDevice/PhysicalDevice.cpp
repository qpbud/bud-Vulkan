#include <cstring>
#include "instance/Instance.hpp"
#include "physicalDevice/PhysicalDevice.hpp"

namespace bud::vk {

VkResult PhysicalDevice::Entry::enumeratePhysicalDevices(
    VkInstance instance,
    uint32_t* pPhysicalDeviceCount,
    VkPhysicalDevice* pPhysicalDevices) {
    auto& instanceInternal = static_cast<bud::vk::Instance&>(*instance);
    uint32_t physicalDeviceCount = instanceInternal.getPhysicalDeviceCount();
    if (!pPhysicalDevices) {
        *pPhysicalDeviceCount = physicalDeviceCount;
        return VK_SUCCESS;
    }
    if (*pPhysicalDeviceCount > physicalDeviceCount) {
        *pPhysicalDeviceCount = physicalDeviceCount;
    }
    for (uint32_t i = 0; i < *pPhysicalDeviceCount; i++) {
        pPhysicalDevices[i] = &instanceInternal.getPhysicalDevice(i);
    }
    if (*pPhysicalDeviceCount < physicalDeviceCount) {
        return VK_INCOMPLETE;
    }
    return VK_SUCCESS;
}

void PhysicalDevice::Entry::getPhysicalDeviceProperties(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties* pProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    *pProperties = physicalDeviceInternal.getProperties().properties;
}

void PhysicalDevice::Entry::getPhysicalDeviceProperties2(
    VkPhysicalDevice physicalDevice,
    VkPhysicalDeviceProperties2* pProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    *pProperties = physicalDeviceInternal.getProperties();
}

void PhysicalDevice::Entry::getPhysicalDeviceQueueFamilyProperties(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties* pQueueFamilyProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    uint32_t queueFamilyCount = physicalDeviceInternal.getQueueFamilyCount();
    if (!pQueueFamilyProperties) {
        *pQueueFamilyPropertyCount = queueFamilyCount;
        return;
    }
    if (*pQueueFamilyPropertyCount > queueFamilyCount) {
        *pQueueFamilyPropertyCount = queueFamilyCount;
    }
    for (uint32_t i = 0; i < *pQueueFamilyPropertyCount; i++) {
        pQueueFamilyProperties[i] = physicalDeviceInternal.getQueueFamilyProperties(i).queueFamilyProperties;
    }
}

void PhysicalDevice::Entry::getPhysicalDeviceQueueFamilyProperties2(
    VkPhysicalDevice physicalDevice,
    uint32_t* pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2* pQueueFamilyProperties) {
    auto& physicalDeviceInternal = static_cast<bud::vk::PhysicalDevice&>(*physicalDevice);
    uint32_t queueFamilyCount = physicalDeviceInternal.getQueueFamilyCount();
    if (!pQueueFamilyProperties) {
        *pQueueFamilyPropertyCount = queueFamilyCount;
        return;
    }
    if (*pQueueFamilyPropertyCount > queueFamilyCount) {
        *pQueueFamilyPropertyCount = queueFamilyCount;
    }
    for (uint32_t i = 0; i < *pQueueFamilyPropertyCount; i++) {
        pQueueFamilyProperties[i] = physicalDeviceInternal.getQueueFamilyProperties(i);
    }
}

VkResult PhysicalDevice::Entry::enumeratePhysicalDeviceGroups(
    VkInstance instance,
    uint32_t* pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties* pPhysicalDeviceGroupProperties) {
    auto& instanceInternal = static_cast<bud::vk::Instance&>(*instance);
    uint32_t physicalDeviceGroupCount = instanceInternal.getPhysicalDeviceGroupCount();
    if (!pPhysicalDeviceGroupProperties) {
        *pPhysicalDeviceGroupCount = physicalDeviceGroupCount;
    }
    if (*pPhysicalDeviceGroupCount > physicalDeviceGroupCount) {
        *pPhysicalDeviceGroupCount = physicalDeviceGroupCount;
    }
    for (uint32_t i = 0; i < physicalDeviceGroupCount; i++) {
        pPhysicalDeviceGroupProperties[i] = instanceInternal.getPhysicalDeviceGroupProperties(i);
    }
    if (*pPhysicalDeviceGroupCount < physicalDeviceGroupCount) {
        return VK_INCOMPLETE;
    }
    return VK_SUCCESS;
}

template<>
PhysicalDevice::PhysicalDevice(IntelCpu, Instance& instance, const Allocator& allocator)
    : Object<VkPhysicalDevice_T>(allocator)
    , m_instance(instance)
    , m_variant(IntelCpu())
    , m_physicalDeviceProperties()
    , m_queueFamiliesProperties(&m_allocator) {
    m_physicalDeviceProperties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    m_physicalDeviceProperties.pNext = nullptr;
    VkPhysicalDeviceProperties& properties = m_physicalDeviceProperties.properties;
    properties.apiVersion = VK_API_VERSION_1_3;
    properties.driverVersion = 1;
    properties.vendorID = 0x8086; // intel
    properties.deviceID = 5; // i5
    properties.deviceType = VK_PHYSICAL_DEVICE_TYPE_CPU;
    std::strcpy(properties.deviceName, "12th Gen Intel(R) Core(TM) i5-12500H");

    m_queueFamiliesProperties.resize(1);
    VkQueueFamilyProperties2& queueFamilyProperties2 = m_queueFamiliesProperties[0];
    queueFamilyProperties2.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
    queueFamilyProperties2.pNext = nullptr;
    VkQueueFamilyProperties& queueFamilyProperties = queueFamilyProperties2.queueFamilyProperties;
    queueFamilyProperties.queueFlags = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT;
    queueFamilyProperties.queueCount = 4;
    queueFamilyProperties.timestampValidBits = 0; // current not support
    queueFamilyProperties.minImageTransferGranularity = {1, 1, 1};
}

const VkPhysicalDeviceProperties2& PhysicalDevice::getProperties() const {
    return m_physicalDeviceProperties;
}

uint32_t PhysicalDevice::getQueueFamilyCount() const {
    return static_cast<uint32_t>(m_queueFamiliesProperties.size());
}

const VkQueueFamilyProperties2& PhysicalDevice::getQueueFamilyProperties(uint32_t index) const {
    return m_queueFamiliesProperties[index];
}

Instance& PhysicalDevice::getInstance() {
    return m_instance;
}

}
