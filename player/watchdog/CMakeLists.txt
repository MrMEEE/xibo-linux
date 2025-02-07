project(xibo-watchdog)

find_package(Boost 1.83 EXACT REQUIRED program_options)

add_executable(${PROJECT_NAME}
    main.cpp
    ProcessWatcher.cpp
    ProcessWatcher.hpp
)

target_link_libraries(${PROJECT_NAME}
    config
    Boost::program_options
)

