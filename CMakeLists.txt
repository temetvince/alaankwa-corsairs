cmake_minimum_required(VERSION 3.11)

project(main)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
include(FetchContent)

# Fetch raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG HEAD
  DOWNLOAD_EXTRACT_TIMESTAMP OFF
)
FetchContent_MakeAvailable(raylib)

# Fetch entt
FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG HEAD
)
FetchContent_MakeAvailable(entt)

# Automatically find all source and header files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/include/*.h ${CMAKE_SOURCE_DIR}/include/*.hpp)

# Add Executable
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

# Include Paths
target_include_directories(${PROJECT_NAME} PRIVATE 
    ${entt_SOURCE_DIR}/single_include/entt 
    ${CMAKE_SOURCE_DIR}/include 
    ${raylib_SOURCE_DIR}/src
)

# Link Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Tools Integration
file(GLOB_RECURSE ALL_SOURCE_FILES CONFIGURE_DEPENDS 
    ${CMAKE_SOURCE_DIR}/src/*.cpp 
    ${CMAKE_SOURCE_DIR}/src/*.hpp 
    ${CMAKE_SOURCE_DIR}/include/*.h 
    ${CMAKE_SOURCE_DIR}/include/*.hpp
)

# Clang-Format
add_custom_target(format ALL
    COMMAND clang-format -i ${ALL_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-format"
)

# Clang-Tidy
add_custom_target(tidy ALL
    COMMAND clang-tidy ${ALL_SOURCE_FILES} -- -I${raylib_SOURCE_DIR}/src -I${entt_SOURCE_DIR}/single_include/entt -I${CMAKE_SOURCE_DIR}/include
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-tidy"
)

# Clang-Check
add_custom_target(check ALL
    COMMAND clang-check ${ALL_SOURCE_FILES} -- -I${raylib_SOURCE_DIR}/src -I${entt_SOURCE_DIR}/single_include/entt -I${CMAKE_SOURCE_DIR}/include
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-check"
)

# Clang-Analyzer
add_custom_target(analyze ALL
    COMMAND clang --analyze ${ALL_SOURCE_FILES} -I${raylib_SOURCE_DIR}/src -I${entt_SOURCE_DIR}/single_include/entt -I${CMAKE_SOURCE_DIR}/include
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-analyze"
)

# Link Tools to Build
add_dependencies(${PROJECT_NAME} format tidy check analyze)
