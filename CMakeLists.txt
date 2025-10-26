cmake_minimum_required(VERSION 3.20)
set(CMAKE_POLICY_VERSION_MINIMUM  3.50)

# Build tool integration in VSCode/Zed.
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
endif()

# Project information
set(PROJECT_NAME GimbalAutoPropSample)
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES C)
set(CMAKE_C_STANDARD 17)

option(SAVE_INTERMEDIATE OFF)

# Do we want or need to save intermediates?
if(NOT MSVC AND SAVE_INTERMEDIATE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -save-temps")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps")
elseif(MSVC AND SAVE_INTERMEDIATE)

endif()

# Add executable test.
add_executable(${PROJECT_NAME}
    gimbal_autoprop_sample/src/main.c
    gimbal_autoprop_sample/src/sample_object.c
)

# Include libgimbal.
add_subdirectory(libs/gimbal)

# Includes/linkage.
target_include_directories(${PROJECT_NAME} PRIVATE gimbal_autoprop_sample/include)
target_link_libraries(${PROJECT_NAME} PRIVATE libGimbal)