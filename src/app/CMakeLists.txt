add_library(anti_cheat_app STATIC
        manager.cpp
)

target_include_directories(anti_cheat_app PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(anti_cheat_app
        PUBLIC
        absl::status
        absl::statusor
        PRIVATE
        spdlog::spdlog
        anti_cheat::common
        anti_cheat::target
)

add_library(anti_cheat::app ALIAS anti_cheat_app)