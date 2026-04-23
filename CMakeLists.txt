cmake_minimum_required(VERSION 3.20)

project(QRTC C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# --- PLATFORM / COMPILER -------------------------------------------------------

if (WIN32)

    message(STATUS "Building QRTC on Windows")

    if (MSVC)
        if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
            message(STATUS "Compiler: Clang-cl (version ${CMAKE_C_COMPILER_VERSION})")
        else ()
            message(STATUS "Compiler: MSVC (version ${MSVC_VERSION})")
        endif()
    else ()
        message(FATAL_ERROR "Unsupported compiler on Windows: ${CMAKE_C_COMPILER_ID}")
    endif()

elseif (APPLE)

    message(STATUS "Building QRTC on macOS")

    if (CMAKE_C_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Compiler: Clang (version ${CMAKE_C_COMPILER_VERSION})")
    else ()
        message(FATAL_ERROR "Unsupported compiler on macOS: ${CMAKE_C_COMPILER_ID}")
    endif()

elseif (UNIX)

    message(STATUS "Building QRTC on Unix/Linux")

    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
        message(STATUS "Compiler: GCC (version ${CMAKE_C_COMPILER_VERSION})")
    elseif (CMAKE_C_COMPILER_ID STREQUAL "Clang")
        message(STATUS "Compiler: Clang (version ${CMAKE_C_COMPILER_VERSION})")
    else ()
        message(FATAL_ERROR "Unsupported compiler on Unix/Linux: ${CMAKE_C_COMPILER_ID}")
    endif()

else ()
    message(FATAL_ERROR "Unsupported platform: ${CMAKE_SYSTEM_NAME}")
endif()

# --- BUILD OPTIONS -------------------------------------------------------------

option(QRTC_BUILD_SHARED_LIB "Build QRTC as a shared library" OFF)

# --- SOURCES -------------------------------------------------------------------

set(QRTC_SOURCES
    src/color.c
    src/hit_record.c
    src/hittable.c
    src/hittable_list.c
    src/sphere.c
)

# --- LIBRARY -------------------------------------------------------------------

add_library(qrtc STATIC ${QRTC_SOURCES})

target_include_directories(qrtc PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)

# --- CONFIG DEFINES ------------------------------------------------------------

target_compile_definitions(qrtc PRIVATE
    $<$<OR:$<CONFIG:Release>,$<CONFIG:MinSizeRel>>:QRTC_DISABLE_ASSERT>
)

# --- FILE PATH STRIPPING -------------------------------------------------------

if (MSVC AND NOT CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(qrtc PRIVATE
        /d1trimfile:${CMAKE_SOURCE_DIR}/
    )

elseif (MSVC AND CMAKE_C_COMPILER_ID STREQUAL "Clang")
    target_compile_options(qrtc PRIVATE
        /clang:-ffile-prefix-map=${CMAKE_SOURCE_DIR}/=
    )

else()
    target_compile_options(qrtc PRIVATE
        -ffile-prefix-map=${CMAKE_SOURCE_DIR}/=
    )
endif()

# --- EXAMPLE -------------------------------------------------------------------

add_executable(example1 examples/example1.c)

target_link_libraries(example1 PRIVATE qrtc m)