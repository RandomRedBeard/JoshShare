cmake_minimum_required(VERSION 2.8)
project(DR)

set(JANSSON_WITHOUT_TESTS ON BOOL FORCE)
set(JANSSON_BUILD_DOCS OFF CACHE BOOL "Disable sphinx docs" FORCE)
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/jansson")

set (CMAKE_CXX_STANDARD 17)

include(GNUInstallDirs)
include(CTest)

find_program(MEMORYCHECK_COMMAND valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full --show-leak-kinds=all")

if (MSVC)
    # add_compile_options(/W4 /WX)
else()
    # add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# Math
if (NOT MSVC)
    set(DR_LINKS m)
endif()

if (MSVC)
    add_definitions(-DPDC_NCMOUSE)
    find_library(CURSES pdcurses PATHS "${CMAKE_CURRENT_SOURCE_DIR}/external/lib" NO_DEFAULT_PATH)
else()
    find_package(Curses REQUIRED)
    set(CURSES "${CURSES_CURSES_LIBRARY}")
endif()

# Add links
set(DR_LINKS ${DR_LINKS} ${CURSES} ${JANSSON_LIBRARIES})

include_directories(include)
include_directories("${JANSSON_INCLUDE_DIRS}")

if (MSVC)
    include_directories(external/include/pdcurses)
else()
    include_directories("${CURSES_INCLUDE_PATH}")
endif()

# General binary
file(GLOB DR_SOURCE src/*.cpp)

# Static linkage to avoid DLL hell
add_library(dr_lib STATIC ${DR_SOURCE})
if (MSVC)
    target_compile_definitions(dr_lib PRIVATE -DPDC_DLL_BUILD)
endif()
target_link_libraries(dr_lib ${DR_LINKS})

set(DR_LINKS ${DR_LINKS} dr_lib)

# add_executable(test_point WIN32 tests/test_point.cpp)
# add_executable(test_room WIN32 tests/test_room.cpp)
# add_executable(test_map tests/test_map.cpp)

# target_link_libraries(test_point ${DR_LINKS})
# target_link_libraries(test_room ${DR_LINKS})
# target_link_libraries(test_map ${DR_LINKS})

# add_test(NAME TEST_POINT COMMAND test_point)
# add_test(NAME TEST_ROOM COMMAND test_room)
# add_test(NAME TEST_MAP COMMAND test_map)

add_executable(main main.cpp)
if (MSVC)
    target_compile_definitions(main PRIVATE -DPDC_DLL_BUILD)
endif()
target_link_libraries(main ${DR_LINKS})

add_custom_command(TARGET main POST_BUILD 
               COMMAND ${CMAKE_COMMAND} -E copy_if_different
               "${CMAKE_CURRENT_SOURCE_DIR}/external/lib/pdcurses.dll"              
                $<TARGET_FILE_DIR:main>)
