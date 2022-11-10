#pragma once

#include <memory_resource>
#include <cstdlib>
#include <vulkan/vulkan.hpp>

namespace bud::vk {

class Allocator : public std::pmr::memory_resource {
    static VkAllocationCallbacks s_defaultAllocationCallbacks;
    static void* defaultAllocation(void* userData, size_t size, size_t alignment, VkSystemAllocationScope allocationScope) noexcept;
    static void* defaultReallocationFunction(void* userData, void* original, size_t size, size_t alignment, VkSystemAllocationScope allocationScope) noexcept;
    static void defaultFree(void* userData, void* memory);
    static void defaultInternalAllocation(void* userData, size_t size, VkInternalAllocationType allocationType, VkSystemAllocationScope allocationScope);
    static void defaultInternalFree(void* userData, size_t size, VkInternalAllocationType allocationType, VkSystemAllocationScope allocationScope);

    VkAllocationCallbacks m_allocationCallbacks;
    VkSystemAllocationScope m_systemAllocationScope;
public:
    Allocator(const VkAllocationCallbacks* allocationCallbacks, VkSystemAllocationScope systemAllocationScope)
        : std::pmr::memory_resource()
        , m_allocationCallbacks(allocationCallbacks ? *allocationCallbacks : s_defaultAllocationCallbacks)
        , m_systemAllocationScope(systemAllocationScope) {}

    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        void* p = m_allocationCallbacks.pfnAllocation(m_allocationCallbacks.pUserData, bytes, alignment, m_systemAllocationScope);
        if (m_allocationCallbacks.pfnInternalAllocation) {
            m_allocationCallbacks.pfnInternalAllocation(m_allocationCallbacks.pUserData, bytes, VK_INTERNAL_ALLOCATION_TYPE_EXECUTABLE, m_systemAllocationScope);
        }
        return p;
    }

    void do_deallocate(void* p, std::size_t bytes, std::size_t alignment) override {
        m_allocationCallbacks.pfnFree(m_allocationCallbacks.pUserData, p);
        if (m_allocationCallbacks.pfnInternalFree) {
            m_allocationCallbacks.pfnInternalFree(m_allocationCallbacks.pUserData, bytes, VK_INTERNAL_ALLOCATION_TYPE_EXECUTABLE, m_systemAllocationScope);
        }
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        if (auto otherAllocator = dynamic_cast<const Allocator*>(&other); otherAllocator) {
            return m_allocationCallbacks.pfnAllocation == otherAllocator->m_allocationCallbacks.pfnAllocation;
        }
        return false;
    }

    template<typename T, typename ... Args>
    T& construct(Args&&... args) {
        auto object = static_cast<T*>(do_allocate(sizeof(T), 0));
        new(object) T(std::forward<Args>(args)...);
        return *object;
    }

    template<typename T>
    void destruct(T& object) noexcept {
        object.~T();
        do_deallocate(&object, sizeof(T), 0);
    }
};

inline VkAllocationCallbacks Allocator::s_defaultAllocationCallbacks{
    nullptr,
    &Allocator::defaultAllocation,
    &Allocator::defaultReallocationFunction,
    &Allocator::defaultFree,
    &Allocator::defaultInternalAllocation,
    &Allocator::defaultInternalFree
};

inline void* Allocator::defaultAllocation(void* userData, size_t size, size_t alignment, VkSystemAllocationScope allocationScope) noexcept {
    return std::malloc(size);
}

inline void* Allocator::defaultReallocationFunction(void* userData, void* original, size_t size, size_t alignment, VkSystemAllocationScope allocationScope) noexcept {
    return std::realloc(original, size);
}

inline void Allocator::defaultFree(void* userData, void* memory) {
    std::free(memory);
}

inline void Allocator::defaultInternalAllocation(void* userData, size_t size, VkInternalAllocationType allocationType, VkSystemAllocationScope allocationScope) {}

inline void Allocator::defaultInternalFree(void* userData, size_t size, VkInternalAllocationType allocationType, VkSystemAllocationScope allocationScope) {}

}
