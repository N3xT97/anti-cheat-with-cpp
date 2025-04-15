#pragma once
#include <Windows.h>

class WindowsHandle {
private:
    HANDLE handle;

public:
    WindowsHandle();
    explicit WindowsHandle(HANDLE h);
    ~WindowsHandle();

    // �̵��� ���
    WindowsHandle(WindowsHandle&& other) noexcept;
    WindowsHandle& operator=(WindowsHandle&& other) noexcept;

    // ���� ����
    WindowsHandle(const WindowsHandle&) = delete;
    WindowsHandle& operator=(const WindowsHandle&) = delete;

    // ��ƿ �Լ�
    HANDLE get() const;
    bool is_valid() const;
    void reset(HANDLE new_handle = INVALID_HANDLE_VALUE);
};
