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
        src/Rectangle.cpp
        src/Rectangle.h
        src/RenderWindow.cpp
        src/RenderWindow.h
        src/constants.h
        src/VisualSorter/VisualSorter.cpp
        src/VisualSorter/VisualSorter.h
        src/utility.cpp
        src/utility.h
        src/chart.cpp
        src/chart.h
        src/VisualSorter/cycle_sort.cpp
        src/VisualSorter/quicksort.cpp
        src/VisualSorter/heapsort.cpp
        src/VisualSorter/cocktail_sort.cpp
        src/VisualSorter/comb_sort.cpp
        src/VisualSorter/insertion_sort.cpp
        src/VisualSorter/bubble_sort.cpp
        src/VisualSorter/selection_sort.cpp
        src/config.cpp
        src/config.h)

target_include_directories(atestat_informatica_cls_XII PRIVATE src/)

# Link to the actual SDL3 library.
target_link_libraries(atestat_informatica_cls_XII PRIVATE SDL3::SDL3)
