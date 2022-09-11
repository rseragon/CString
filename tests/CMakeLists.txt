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
set(SANITIZE_MEMORY ON)
set(SANITIZE_LINK_STATIC OFF)

find_package(Sanitizers)

add_executable(NormalTests normal_tests.c)
add_sanitize_address(NormalTests)
target_compile_features(NormalTests PRIVATE c_std_11)
target_link_libraries(NormalTests PRIVATE CString)

add_executable(StartEndTest starts_ends_test.c)
target_compile_features(StartEndTest PRIVATE c_std_11)
target_link_libraries(StartEndTest PRIVATE CString)


add_executable(MemSanTests memsan_tests.c)
add_sanitize_memory(MemSanTests)
target_compile_features(MemSanTests PRIVATE c_std_11)
target_link_libraries(MemSanTests PRIVATE CString)

add_test(NAME MemSanTests COMMAND MemSanTests)
add_test(NAME NormalTest COMMAND NormalTests)
add_test(NAME StartEndTest COMMAND StartEndTest)
