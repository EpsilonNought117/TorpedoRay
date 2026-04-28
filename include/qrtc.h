#ifndef QRTC_H
#define QRTC_H

#if defined(__GNUC__)
    #define _GNU_SOURCE
#endif

// C Standard Headers
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>

/****************************************************************************************************/
/**************************   COMPILER, OS and CPU-ISA SPECIFIC HEADERS   ***************************/
/****************************************************************************************************/

#if defined(_WIN32)

    #if defined(_MSC_VER)
    
        #define WIN32_LEAN_AND_MEAN
        #include <Windows.h>

        /* Thread-local storage */
        #define THREAD_LOCAL __declspec(thread)

        #if defined(_M_X64) || defined(_M_AMD64)
        
            #include <immintrin.h>
            #include <intrin.h>

        #elif defined(_M_ARM64) || defined(_M_ARM64EC)
        
            /* TODO */

        #else
            #error "Unsupported CPU ISA on Windows!"
        #endif
    
    #else
        #error "Unknown Compiler on Windows!"
    #endif

    #if defined(QRTC_BUILD_SHARED_LIB)

        #define QRTC_API __declspec(dllexport)
    
    #elif defined(QRTC_SHARED)
    
        #define QRTC_API __declspec(dllimport)

    #else
        #define QRTC_API
    #endif

#elif defined(__linux__) || defined(__linux)   || \
      defined(__unix__)  || defined(__unix)    || \
      defined(__APPLE__) || defined(__MACH__)

    #if defined(__GNUC__) || defined(__clang__)

        #include <pthread.h>

        /* Thread-local storage */
        #define THREAD_LOCAL __thread
        
        #if defined(__x86_64__)  || defined(__amd64__)  || \
            defined(__x86_64)    || defined(__amd64)
        
            #include <cpuid.h>
            #include <immintrin.h>
        
        #elif defined(__aarch64__) || defined(__arm64__)
        
            #include <arm_acle.h>
            #include <arm_neon.h>
        
        #else
            #error "Unsupported CPU ISA on Linux/Unix/macOS!"
        #endif

    #else
        #error "Unknown Compiler on Linux/Unix/macOS!"
    #endif

    #if defined(QRTC_BUILD_SHARED_LIB)

        #define QRTC_API __attribute__((visibility("default")))
    
    #else
        #define QRTC_API
    #endif

#else
    #error "Unknown Platform!"
#endif

/* ==========================================================================
 * Always-enabled assertion
 * ========================================================================== */

#define QRTC_ALWAYS_ASSERT(expr)                            \
    do                                                      \
    {                                                       \
        if (!(expr))                                        \
        {                                                   \
            fprintf(                                        \
                stderr,                                     \
                "\n\nQRTC ASSERTION FAILED!\n"              \
                "ASSERTION: %s\n"                           \
                "FILE: %s\nLINE: %d\n",                     \
                #expr, __FILE__, __LINE__                   \
            );                                              \
            fprintf(stderr, "ABORTING PROGRAM ...\n\n");    \
            exit(EXIT_FAILURE);                             \
        }                                                   \
    } while (0)


/* ==========================================================================
 * Debug-only assertions
 * ========================================================================== */

#ifndef QRTC_DISABLE_ASSERT
    #define QRTC_ASSERT(expr)   QRTC_ALWAYS_ASSERT(expr)
#else
    #define QRTC_ASSERT(expr)   do { /* nothing */ } while (0)
#endif

/* ==========================================================================
 * Error logging
 * ========================================================================== */

#define QRTC_LOG_ERR(msg) fprintf(stderr, "QRTC ERROR: %s\n", msg)

#endif // QRTC_HPP