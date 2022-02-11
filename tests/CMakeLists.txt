add_executable(testlib utest.c)

target_compile_features(testlib PRIVATE c_std_11)

target_link_libraries(testlib PRIVATE CString)

add_test(NAME SimpleTest1 COMMAND testlib)
