#pragma once

#include <vulkan/vulkan.h>
#include "common/Object.hpp"

namespace bud::vk {

class Instance : public VkInstance_T {
public:
    static Instance& create(const VkInstanceCreateInfo& createInfo);
    static void destroy(Instance& instance);

    Instance(const VkInstanceCreateInfo& createInfo);
};

}
