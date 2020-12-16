cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
option(BUILD_COVERAGE "Build coverage" OFF)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.23.278.tar.gz"
  SHA1 "35fa55bc1dfcf9f4d7264f8bb26cd1759ce1ae07"
)

project(Go_game)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

add_library(Go_game STATIC
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/Button.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/MainMenu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/Table.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/TableStone.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/for_mainmenu.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/math_functions.cpp
)
add_executable(tests
  ${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp
)

add_executable(start_game
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/source.cpp
)

target_include_directories(Go_game
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(tests
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_include_directories(start_game
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(Go_game    sfml-network
                                 sfml-graphics
                                 sfml-window
                                 sfml-system)
target_link_libraries(tests GTest::gtest_main Go_game
                                 sfml-network
                                 sfml-graphics
                                 sfml-window
                                 sfml-system)
target_link_libraries(start_game sfml-network
                                 sfml-graphics
                                 sfml-window
                                 sfml-system
                                 Go_game
)

enable_testing()
add_test(NAME unit_tests COMMAND tests)
if(BUILD_COVERAGE)
  function(ENABLE_PROJECT_COVERAGE PROJECT)
    target_compile_options(${PROJECT} PRIVATE --coverage)
    target_link_libraries(${PROJECT} --coverage)
    add_coverage(${PROJECT})
  endfunction()

  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
  find_package(codecov)

  enable_project_coverage(Go_game)
  enable_project_coverage(tests)
  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
  coverage_evaluate()
endif()