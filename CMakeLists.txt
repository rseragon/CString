cmake_minimum_required(VERSION 3.15...3.22.2)

project(CString VERSION 0.2
                       DESCRIPTION "A simple string library for C"
                       LANGUAGES C)

# default
option(BUILD_SHARED_LIB "Build a shared library" OFF)

if(BUILD_SHARED_LIB STREQUAL ON)
  add_library(${PROJECT_NAME} SHARED ${CMAKE_SOURCE_DIR}/src/String.c)
else()
  add_library(${PROJECT_NAME} STATIC ${CMAKE_SOURCE_DIR}/src/String.c)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include/)

target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)

# Debug flag
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# Valgrind > sans
#set (CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address -g")
#set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")

# Run tests only if standalone project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
  enable_testing()
  add_subdirectory(tests)
endif()

