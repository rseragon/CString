# CString
A simple dynamic String library for C

**Version**: 0.6

## Building
1. Create a build directory
```
mkdir build && cd build/
```
2. Generate CMake build files
- Static library build
```
cmake ..
```
- Shared library build
```
cmake .. -DBUILD_SHARED_LIB=ON
```
3. Run tests (optional)
- Do it inside the `build/` directory
```
ctest
```
4. Using the library 
	1. add as git submodule (other method are also possible, but this is recommended)
	```
    git add https://github.com/rseragon/CString.git
    ```
    2. Add the sub-directory (in cmake file)
    ```cmake
    add_subdirectory(CString)
    ```
    3. Link the library
    ```cmake
    target_link_libraries(${PROJECT_NAME} PUBLIC CString)
    ```
    4. Include headers
    ```cmake
    target_include_directories(${PROJECT_NAME} PUBLIC ${CSTRING_LIB_HEADERS})
    ```
