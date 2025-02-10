cmake_minimum_required(VERSION 3.16)

# Set the project name and version
project(ops2 VERSION 1.0 LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set default char type to unsigned
add_compile_definitions(CHAR_UNSIGNED)

# Add the main executable target
add_executable(ops2
    src/ops2.cpp
)

find_package(curl CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

# Link SDL2 to your executable
target_link_libraries(ops2 PRIVATE SDL2::SDL2 SDL2::SDL2main CURL::libcurl)

# Precompiled headers for Windows/MSVC
if (MSVC)
    target_compile_options(ops2 PRIVATE /W4 /WX /MP /Zi /Od /bigobj)
    target_link_options(ops2 PRIVATE /SUBSYSTEM:WINDOWS /INCREMENTAL)
endif()
