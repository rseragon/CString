cmake_minimum_required(VERSION 3.14...3.22.2)

project(CString VERSION 0.4
        DESCRIPTION "A simple string library for C"
        LANGUAGES C)

# default
option(BUILD_SHARED_LIB "Build a shared library" OFF)


if(BUILD_SHARED_LIB STREQUAL ON)
    add_library(${PROJECT_NAME} SHARED ${CMAKE_SOURCE_DIR}/src/String.c)
else()
    add_library(${PROJECT_NAME} STATIC ${CMAKE_SOURCE_DIR}/src/String.c)
endif()

target_compile_features(${PROJECT_NAME} PRIVATE c_std_11)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)




# Run tests only if standalone project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_BUILD_TYPE Debug)
    include(CTest) 
    enable_testing()
    # Debug flag
    #set (CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

    # Memory sanitizer hacks
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/src)

    add_subdirectory(tests)
endif()

