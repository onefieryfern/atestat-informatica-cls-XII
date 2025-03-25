cmake_minimum_required(VERSION 3.30)
project(atestat_informatica_cls_XII)

set(CMAKE_CXX_STANDARD 23)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_executable(atestat_informatica_cls_XII src/main.cpp
        src/sort.cpp
        src/sort.h
        src/rectangle.cpp
        src/rectangle.h
        src/graphing.cpp
        src/graphing.h
        src/render.cpp
        src/render.h
        src/constants.h)

target_include_directories(atestat_informatica_cls_XII PRIVATE src/)

# Link to the actual SDL3 library.
target_link_libraries(atestat_informatica_cls_XII PRIVATE SDL3::SDL3)
