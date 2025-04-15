#pragma once
#include <Windows.h>

class WindowsHandle {
private:
    HANDLE handle;

public:
    WindowsHandle();
    explicit WindowsHandle(HANDLE h);
    ~WindowsHandle();

    // 이동만 허용
    WindowsHandle(WindowsHandle&& other) noexcept;
    WindowsHandle& operator=(WindowsHandle&& other) noexcept;

    // 복사 금지
    WindowsHandle(const WindowsHandle&) = delete;
    WindowsHandle& operator=(const WindowsHandle&) = delete;

    // 유틸 함수
    HANDLE get() const;
    bool is_valid() const;
    void reset(HANDLE new_handle = INVALID_HANDLE_VALUE);
};
