#ifndef ANTI_CHEAT_PLATFORM_WINDOWS_COMMON_HANDLE_WRAPPER_H
#define ANTI_CHEAT_PLATFORM_WINDOWS_COMMON_HANDLE_WRAPPER_H

namespace platform::windows::common {

template <typename HandleType, typename CloseFunc>
class HandleWrapper final {
 public:
  HandleWrapper() = delete;
  explicit HandleWrapper(HandleType handle);

  HandleWrapper(HandleWrapper&& other);
  HandleWrapper& operator=(HandleWrapper&& other);

  HandleWrapper(const HandleWrapper&) = delete;
  HandleWrapper& operator=(const HandleWrapper&) = delete;

  ~HandleWrapper();

  HandleType get() const;
  [[nodiscard]] bool is_valid() const;

 private:
  void close();

  HandleType raw_;
  CloseFunc close_func_;
};
}  // namespace platform::windows::common

#include "handle_wrapper.inl"

#endif  // ANTI_CHEAT_PLATFORM_WINDOWS_COMMON_HANDLE_WRAPPER_H
