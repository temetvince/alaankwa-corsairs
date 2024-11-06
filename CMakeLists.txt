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
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${CMAKE_BINARY_DIR}/raylib-build)
  endif()
endif()

# Fetch entt
set(ENTT_VERSION 3.9.0)
FetchContent_Declare(
  entt
  GIT_REPOSITORY https://github.com/skypjack/entt.git
  GIT_TAG v${ENTT_VERSION}
)
FetchContent_MakeAvailable(entt)

# Automatically find all source and header files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.hpp)
file(GLOB_RECURSE PROJECT_HEADERS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/include/*.h ${CMAKE_SOURCE_DIR}/include/*.hpp)

# Our Project
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PRIVATE ${entt_SOURCE_DIR}/single_include/entt/ ${CMAKE_SOURCE_DIR}/include)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
  # Tell Emscripten to build an example.html file.
  set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on macOS)
if (APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE "-framework IOKit" "-framework Cocoa" "-framework OpenGL")
endif()

file(GLOB_RECURSE ALL_SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.hpp ${CMAKE_SOURCE_DIR}/include/*.h ${CMAKE_SOURCE_DIR}/include/*.hpp)
# Add Clang-Format target
add_custom_target(format
    COMMAND clang-format -i ${ALL_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-format"
)

# Add Clang-Tidy target
add_custom_target(tidy
    COMMAND clang-tidy ${ALL_SOURCE_FILES}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-tidy"
)

# Add Clang-Check target
add_custom_target(check
    COMMAND clang-check ${ALL_SOURCE_FILES} -- -Iinclude
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-check"
)

# Add Clang-Analyzer target
add_custom_target(analyze
    COMMAND clang --analyze ${ALL_SOURCE_FILES} -Iinclude -o reports
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-analyze"
)

# Add Clang-Include-Fixer target
add_custom_target(include-fixer
    COMMAND clang-include-fixer ${ALL_SOURCE_FILES} -- -Iinclude
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-inlcude-fixer"
)
