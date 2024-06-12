cmake_minimum_required(VERSION 3.14)
project(Design_Patterns)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CSS_STANDARD_REQUIRED_ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


file(GLOB_RECURSE PROJECT_SOURCE_FILE
	./src/Registry_TypeErase/Registry_TypeErase.cpp
)

add_executable(Design_Patterns ${PROJECT_SOURCE_FILE})
target_link_libraries(Design_Patterns gtest_main)
