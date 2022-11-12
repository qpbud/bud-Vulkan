#include <cstring>
#include "physicalDevice/PhysicalDevice.hpp"

namespace bud::vk {

template<>
PhysicalDevice::PhysicalDevice(Cpu)
    : Object<VkPhysicalDevice_T>()
    , m_physicalDeviceProperties2()
    , m_queueFamilyProperties2(1) {
    m_physicalDeviceProperties2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    m_physicalDeviceProperties2.pNext = nullptr;
    VkPhysicalDeviceProperties& properties = m_physicalDeviceProperties2.properties;
    properties.apiVersion = VK_API_VERSION_1_3;
    properties.driverVersion = 1;
    properties.vendorID = 0x8086; // intel
    properties.deviceID = 5; // i5
    properties.deviceType = VK_PHYSICAL_DEVICE_TYPE_CPU;
    std::strcpy(properties.deviceName, "12th Gen Intel(R) Core(TM) i5-12500H");

    VkQueueFamilyProperties2& queueFamilyProperties2 = m_queueFamilyProperties2[0];
    queueFamilyProperties2.sType = VK_STRUCTURE_TYPE_QUEUE_FAMILY_PROPERTIES_2;
    queueFamilyProperties2.pNext = nullptr;
    VkQueueFamilyProperties& queueFamilyProperties = queueFamilyProperties2.queueFamilyProperties;
    queueFamilyProperties.queueFlags = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT;
    queueFamilyProperties.queueCount = 4;
    queueFamilyProperties.timestampValidBits = 0; // current not support
    queueFamilyProperties.minImageTransferGranularity = {1, 1, 1};
}

const VkPhysicalDeviceProperties2& PhysicalDevice::getProperties2() const {
    return m_physicalDeviceProperties2;
}

uint32_t PhysicalDevice::getQueueFamilyProperties2Count() const {
    return static_cast<uint32_t>(m_queueFamilyProperties2.size());
}

const VkQueueFamilyProperties2& PhysicalDevice::getQueueFamilyProperties2(uint32_t index) const {
    return m_queueFamilyProperties2[index];
}

}
