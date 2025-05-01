#ifndef ANTI_CHEAT_PLATFORM_WINDOWS_COMMON_HANDLE_WRAPPER_INL
#define ANTI_CHEAT_PLATFORM_WINDOWS_COMMON_HANDLE_WRAPPER_INL

#include "handle_wrapper.h"

namespace platform::windows::common {
template <typename HandleType, typename CloseFunc>
HandleWrapper<HandleType, CloseFunc>::HandleWrapper(HandleType handle)
    : raw_(handle) {}

template <typename HandleType, typename CloseFunc>
HandleWrapper<HandleType, CloseFunc>::HandleWrapper(HandleWrapper &&other)
    : raw_(other.raw_) {
  other.raw_ = nullptr;
}

template <typename HandleType, typename CloseFunc>
HandleWrapper<HandleType, CloseFunc> &
HandleWrapper<HandleType, CloseFunc>::operator=(HandleWrapper &&other) {
  if (this != &other) {
    this->close();
    this->raw_ = other.raw_;
    other.raw_ = nullptr;
  }
  return *this;
}

template <typename HandleType, typename CloseFunc>
HandleWrapper<HandleType, CloseFunc>::~HandleWrapper() {
  this->close();
}

template <typename HandleType, typename CloseFunc>
HandleType HandleWrapper<HandleType, CloseFunc>::get() const {
  return this->raw_;
}

template <typename HandleType, typename CloseFunc>
bool HandleWrapper<HandleType, CloseFunc>::is_valid() const {
  return this->raw_ != nullptr;
}

template <typename HandleType, typename CloseFunc>
void HandleWrapper<HandleType, CloseFunc>::close() {
  if (this->raw_) {
    this->close_func_(this->raw_);
    this->raw_ = nullptr;
  }
}
}  // namespace platform::windows::common

#endif  // ANTI_CHEAT_PLATFORM_WINDOWS_COMMON_HANDLE_WRAPPER_INL
