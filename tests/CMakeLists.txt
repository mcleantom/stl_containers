enable_testing()
find_package(GTest CONFIG REQUIRED)

file(GLOB TESTS_SRC CONFIGURE_DEPENDS "*.cpp")
add_executable(
    stl_containers_tests
    ${TESTS_SRC}
)
target_link_libraries(
    stl_containers_tests
    PRIVATE
    GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main
    stl_containers
)
add_dependencies(
    stl_containers_tests
    stl_containers
)

add_test(
    NAME
    stl_containers_tests
    COMMAND
    ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)