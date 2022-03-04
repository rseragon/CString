# Sanitizer library 

include(FetchContent)

FetchContent_Declare(
    Sanitizers
    GIT_REPOSITORY https://github.com/rseragon/sanitizers-cmake
)

FetchContent_MakeAvailable(Sanitizers)

set(Sanitizers_DIR "${CMAKE_BINARY_DIR}/_deps/sanitizers-src/cmake")
list(APPEND CMAKE_MODULE_PATH "${Sanitizers_DIR}")

set(SANITIZE_ADDRESS ON)
set(SANITIZE_LINK_STATIC OFF)

find_package(Sanitizers)

add_executable(testlib utest.c)
add_sanitizers(testlib)

target_compile_features(testlib PRIVATE c_std_11)

target_link_libraries(testlib PRIVATE CString)

add_test(NAME SimpleTest1 COMMAND testlib)
