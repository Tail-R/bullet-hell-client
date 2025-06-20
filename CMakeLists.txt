cmake_minimum_required(VERSION 3.12)
project(${TARGET_NAME} LANGUAGES C CXX)

# Target Name
set(TARGET_NAME bullet_hell_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Source directories
set(SRC_DIR src)
set(GLAD_SRC external/glad/src/glad.c)

# Source files
set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/logger/logger.cpp
    ${SRC_DIR}/frame/frame_template.cpp
    ${SRC_DIR}/frame/frame_serializer.cpp
    ${SRC_DIR}/socket/socket.cpp
    ${SRC_DIR}/packet_stream/packet_stream.cpp
    ${SRC_DIR}/renderer/renderer.cpp
    ${SRC_DIR}/mesh/mesh.cpp
    ${SRC_DIR}/shader/shader.cpp
    ${SRC_DIR}/texture/texture2d.cpp
    ${GLAD_SRC}
)

# Fetch SDL before defining the target
include(${CMAKE_SOURCE_DIR}/external/FetchSDL.cmake)

# Executable
add_executable(${TARGET_NAME} ${SRC_FILES})

# Include paths
target_include_directories(${TARGET_NAME} PRIVATE
    src
    external/glad/include
    external/glm
)

# Link OS-specific libraries
if(WIN32)
    target_link_libraries(${TARGET_NAME}
        mingw32
        SDL2::SDL2
        ws2_32
    )
elseif(UNIX)
    target_link_libraries(${TARGET_NAME}
        SDL2::SDL2
    )
endif()
