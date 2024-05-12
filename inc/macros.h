#pragma once

#include <stdio.h>

#define UNUSED          __attribute__((unused))
#define ALWAYS_INLINE   inline __attribute__((always_inline))

#define STR_IMPL_(x) #x      // stringify argument
#define STR(x) STR_IMPL_(x)  // indirection to expand argument macros

#ifdef WASM
    #define ASSETS_PATH     "/assets/"
#else
    #define ASSETS_PATH     "./assets/"
#endif

// -------------------------------------------
#ifdef DEBUG
    #define LOG_LEVEL   LOG_LEVEL_DEBUG
#else
    #define LOG_LEVEL   LOG_LEVEL_RELEASE
#endif
// -------------------------------------------

// -------------------------------------------
#if LOG_LEVEL == LOG_LEVEL_DEBUG
    #define DEBUG_LOG(...)    printf(__VA_ARGS__)
#elif LOG_LEVEL == LOG_LEVEL_RELEASE
    #define DEBUG_LOG(...)
#else
    #error "Invalid LOG_LEVEL"
#endif
// -------------------------------------------

// Assert macros from: https://github.com/apple/darwin-xnu/blob/main/EXTERNAL_HEADERS/AssertMacros.h

#define check_noerr(err_code)                                                       \
    do                                                                              \
    {                                                                               \
        if ( __builtin_expect(0 != (err_code), 0) )                                 \
        {                                                                           \
            DEBUG_LOG("Error %d at %s:%d\r\n", err_code, __FILE__, __LINE__);       \
        }                                                                           \
    } while ( 0 )

#define require_noerr(err_code, exception_label)                                    \
    do                                                                              \
    {                                                                               \
        if ( __builtin_expect(0 != (err_code), 0) )                                 \
        {                                                                           \
            DEBUG_LOG("Error %d at %s:%d\r\n", err_code, __FILE__, __LINE__);       \
            goto exception_label;                                                   \
        }                                                                           \
    } while ( 0 )

#define require_noerr_msg(err_code, exception_label, ...)                           \
    do                                                                              \
    {                                                                               \
        if ( __builtin_expect(0 != (err_code), 0) )                                 \
        {                                                                           \
            printf(__VA_ARGS__);                                                    \
            DEBUG_LOG("Error %d at %s:%d\r\n", err_code, __FILE__, __LINE__);       \
            goto exception_label;                                                   \
        }                                                                           \
    } while ( 0 )


#define require_noerr_action(err_code, exception_label, action)                     \
    do                                                                              \
    {                                                                               \
        if ( __builtin_expect(0 != (err_code), 0) )                                 \
        {                                                                           \
            {                                                                       \
                action;                                                             \
            }                                                                       \
            DEBUG_LOG("Error %d at %s:%d\r\n", err_code, __FILE__, __LINE__);       \
            goto exception_label;                                                   \
        }                                                                           \
    } while ( 0 )

#define require_noerr_action_msg(err_code, exception_label, action, ...)            \
    do                                                                              \
    {                                                                               \
        if ( __builtin_expect(0 != (err_code), 0) )                                 \
        {                                                                           \
            {                                                                       \
                action;                                                             \
            }                                                                       \
            printf(__VA_ARGS__);                                                    \
            DEBUG_LOG("Error %d at %s:%d\r\n", err_code, __FILE__, __LINE__);       \
            goto exception_label;                                                   \
        }                                                                           \
    } while ( 0 )



#define require(assertion, exception_label)                                     \
    do                                                                          \
    {                                                                           \
        if ( __builtin_expect(!(assertion), 0) )                                \
        {                                                                       \
            DEBUG_LOG("Failed assertion at %s:%d\r\n", __FILE__, __LINE__);     \
            goto exception_label;                                               \
        }                                                                       \
    } while ( 0 )


#define require_msg(assertion, exception_label, ...)                            \
    do                                                                          \
    {                                                                           \
        if ( __builtin_expect(!(assertion), 0) )                                \
        {                                                                       \
            printf(__VA_ARGS__);                                                \
            DEBUG_LOG("Failed assertion at %s:%d\r\n", __FILE__, __LINE__);     \
            goto exception_label;                                               \
        }                                                                       \
    } while ( 0 )


#define require_action(assertion, exceptionLabel, action)                       \
    do                                                                          \
    {                                                                           \
        if ( __builtin_expect(!(assertion), 0) )                                \
        {                                                                       \
            {                                                                   \
                action;                                                         \
            }                                                                   \
            DEBUG_LOG("Failed assertion at %s:%d\r\n", __FILE__, __LINE__);     \
            goto exceptionLabel;                                                \
        }                                                                       \
    } while ( 0 )


#define require_action_msg(assertion, exceptionLabel, action, ...)              \
    do                                                                          \
    {                                                                           \
        if ( __builtin_expect(!(assertion), 0) )                                \
        {                                                                       \
            {                                                                   \
                action;                                                         \
            }                                                                   \
            printf(__VA_ARGS__);                                                \
            DEBUG_LOG("Failed assertion at %s:%d\r\n", __FILE__, __LINE__);     \
            goto exceptionLabel;                                                \
        }                                                                       \
    } while ( 0 )


#define goto_error(exception_label, msg)    \
    do                                      \
    {                                       \
        DEBUG_LOG("%s\r\n", msg);           \
        goto exception_label;               \
    } while ( 0 )

#define FATAL_ERROR(...)                \
    do                                  \
    {                                   \
        printf("FATAL ERROR: ");        \
        printf(__VA_ARGS__);            \
                                        \
        exit(1);                        \
    }                                   \
    while (0)