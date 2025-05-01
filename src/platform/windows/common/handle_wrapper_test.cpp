#include "handle_wrapper.h"

#include <gtest/gtest.h>
#include <windows.h>

struct HandleCloser {
  void operator()(HANDLE handle) const { ::CloseHandle(handle); }
};

using WindowsHandle = common::HandleWrapper<HANDLE, HandleCloser>;

TEST(HandleWrapperTest, ValidHandle) {
  HANDLE event_handle = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
  ASSERT_NE(event_handle, nullptr);

  WindowsHandle wrapper(event_handle);
  EXPECT_TRUE(wrapper.is_valid());
  EXPECT_EQ(wrapper.get(), event_handle);
}

TEST(HandleWrapperTest, MoveHandle) {
  HANDLE event_handle = ::CreateEvent(nullptr, FALSE, FALSE, nullptr);
  ASSERT_NE(event_handle, nullptr);

  WindowsHandle wrapper1(event_handle);
  EXPECT_TRUE(wrapper1.is_valid());

  WindowsHandle wrapper2(std::move(wrapper1));
  EXPECT_TRUE(wrapper2.is_valid());
  EXPECT_FALSE(wrapper1.is_valid());
}
