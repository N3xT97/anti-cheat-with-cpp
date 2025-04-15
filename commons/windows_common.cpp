#include "windows_common.h"

WindowsHandle::WindowsHandle()
    : handle(INVALID_HANDLE_VALUE) {
}

WindowsHandle::WindowsHandle(HANDLE h)
    : handle(h) {
}

WindowsHandle::~WindowsHandle() {
    if (is_valid()) {
        CloseHandle(handle);
    }
}

WindowsHandle::WindowsHandle(WindowsHandle&& other) noexcept
    : handle(other.handle) {
    other.handle = INVALID_HANDLE_VALUE;
}

WindowsHandle& WindowsHandle::operator=(WindowsHandle&& other) noexcept {
    if (this != &other) {
        reset();
        handle = other.handle;
        other.handle = INVALID_HANDLE_VALUE;
    }
    return *this;
}

HANDLE WindowsHandle::get() const {
    return handle;
}

bool WindowsHandle::is_valid() const {
    return handle != nullptr && handle != INVALID_HANDLE_VALUE;
}

void WindowsHandle::reset(HANDLE new_handle) {
    if (is_valid()) {
        CloseHandle(handle);
    }
    handle = new_handle;
}
