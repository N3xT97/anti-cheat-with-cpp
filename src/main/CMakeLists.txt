add_executable(anti_cheat_with_cpp
        main.cpp
)

target_link_libraries(anti_cheat_with_cpp
        PRIVATE
        spdlog::spdlog
        anti_cheat::common
        anti_cheat::app
)