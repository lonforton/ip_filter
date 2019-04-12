cmake_minimum_required(VERSION 3.2)

set(Boost_ARCHITECTURE "-x32")

if (NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
   set(ENV{TRAVIS_BUILD_NUMBER} "1")
endif()

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(ip_filter main.cpp)
add_executable(unit_tests unit_tests.cpp)

set_target_properties(ip_filter unit_tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
)

set_target_properties(unit_tests PROPERTIES    
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(unit_tests
    ${Boost_LIBRARIES}
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

enable_testing()

add_test(NAME ip_filter_test COMMAND unit_tests)