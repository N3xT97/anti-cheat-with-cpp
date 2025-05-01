include(GoogleTest)

add_library(anti_cheat_windows_common INTERFACE)

target_include_directories(anti_cheat_windows_common INTERFACE
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(anti_cheat_windows_common
        INTERFACE
        absl::status
        absl::statusor
)

add_library(anti_cheat::windows::common ALIAS anti_cheat_windows_common)

add_executable(handle_wrapper_test
        handle_wrapper_test.cpp
)

target_link_libraries(handle_wrapper_test
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        anti_cheat::windows::common
)

gtest_discover_tests(handle_wrapper_test)
#add_test(NAME handle_wrapper_test COMMAND handle_wrapper_test)