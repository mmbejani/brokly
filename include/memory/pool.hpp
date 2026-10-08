#include <cstdint>

namespace momas::brokly::memory {

enum MemoryType {
  RESIDENT,
  EPHEMERAL
};


class MemoryPool {
public:
  struct MemoryConfig {
    uint64_t buffer_size;
    void* buffer_ptr;
    MemoryType type;
  };

  MemoryPool(const MemoryConfig& config) : config(config), offset(0) {}

  /**
   * @brief Get the Memory object if there is memory for input size, else return `nullptr`
   * 
   * @param count number of float
   * @return float* a pointer to first allocate memory
   */
  template<float>
  [[nodiscard("capture the allocated memory")]]
  float* getMemory(const uint64_t count) {
    const auto float_size = sizeof(float);
    if (offset + float_size * count < config.buffer_size) [[likely]] {
      float* ptr = reinterpret_cast<float*>(offset + (uint8_t*)config.buffer_ptr);
      offset += float_size * count;
      return ptr;
    } 
    return nullptr;
  }

  /**
   * @brief Get the Memory object if there is memory for input size, else return `nullptr`
   * 
   * @tparam T data type
   * @param count number of T
   * @return T* a pointer to first allocate memory
   */
  template<typename T>
  [[nodiscard("capture the allocated memory")]]
  T* getMemory(const uint64_t count) {
    if (offset + sizeof(T) * count < config.buffer_size) [[likely]] {
      T* ptr = reinterpret_cast<T*>(offset + (uint8_t*)config.buffer_ptr);
      offset += sizeof(T) * count;
      return ptr;
    } 
    return nullptr;
  }

private:
  uint64_t offset;
  const MemoryConfig config;
};
} // namespace momas::brokly::memory