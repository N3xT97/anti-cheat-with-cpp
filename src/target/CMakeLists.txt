add_library(anti_cheat_target STATIC
        manager.cpp
        controller_factory.cpp
)

target_include_directories(anti_cheat_target PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(anti_cheat_target
        PUBLIC
        absl::status
        anti_cheat::windows::process
        PRIVATE
        spdlog::spdlog
)

add_library(anti_cheat::target ALIAS anti_cheat_target)