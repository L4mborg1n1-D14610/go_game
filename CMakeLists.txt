cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_COVERAGE "Build coverage" OFF)

# include("tools/gate/cmake/HunterGate.cmake")

# HunterGate(
#  URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
#  SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"
# )

project(Go_game)
string(APPEND CMAKE_CXX_FLAGS " -pedantic -Werror -Wall -Wextra")
string(APPEND CMAKE_CXX_FLAGS " -Wno-unused-command-line-argument")
string(APPEND CMAKE_CXX_FLAGS " -Wshadow -Wnon-virtual-dtor")

# hunter_add_package(GTest)
# hunter_add_package(SFML)
# find_package(GTest CONFIG REQUIRED)
# find_package(SFML COMPONENTS graphics CONFIG REQUIRED)

find_package (SFML REQUIRED system window graphics network audio)
include_directories(${SFML_INCLUDE_DIR})

add_executable(Go_game
  ${CMAKE_CURRENT_SOURCE_DIR}/sources/source.cpp
)
target_include_directories(Go_game
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(space_impact ${SFML_LIBRARIES})
# target_link_libraries(tests GTest::gtest_main Go_game)
# target_link_libraries(start_game PUBLIC sfml-graphics)
# target_link_libraries(start_game PUBLIC Go_game)

# enable_testing()
# add_test(NAME unit_tests COMMAND tests)

# if(BUILD_COVERAGE)
#  function(ENABLE_PROJECT_COVERAGE PROJECT)
#    target_compile_options(${PROJECT} PRIVATE --coverage)
#    target_link_libraries(${PROJECT} --coverage)
#    add_coverage(${PROJECT})
#  endfunction()

#  set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
#  list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#  find_package(codecov)

#  enable_project_coverage(Go_game)
#  enable_project_coverage(tests)
#  list(APPEND LCOV_REMOVE_PATTERNS "'${PROJECT_SOURCE_DIR}/tests/*'")
#  coverage_evaluate()
# endif() 

