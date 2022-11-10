#pragma once

#include <vulkan/vulkan.h>
#include "common/Object.hpp"

namespace bud::vk {

class PhysicalDevice : public Object<VkPhysicalDevice_T> {};

}
