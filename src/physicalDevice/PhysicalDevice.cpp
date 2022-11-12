#include <cstring>
#include "physicalDevice/PhysicalDevice.hpp"

namespace bud::vk {

template<>
PhysicalDevice::PhysicalDevice(IntelCpu, const Allocator& allocator)
    : Object<VkPhysicalDevice_T>(allocator)
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

}
