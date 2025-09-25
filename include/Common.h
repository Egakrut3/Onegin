#ifndef COMMON_H
#define COMMON_H

#include "Colored_printf.h"
#include <errno.h>
#include <assert.h>
#include <stdlib.h>
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>

#define EEMPTY_INP 1000

#define PRINT_LINE() fprintf(stderr, "Error found, file " __FILE__ ", line %d\n", __LINE__)

#define CLEAR_RESOURCES()   \
do                          \
{                           \
    FINISH_CODE             \
} while (false)

#define CHECK_FUNC(func, ...)      \
do                                 \
{                                  \
    if (func(__VA_ARGS__))         \
    {                              \
        PRINT_LINE();              \
        perror(#func " failed");   \
        CLEAR_RESOURCES();         \
        return errno;              \
    }                              \
} while (false)

enum User_error_code
{
    NO_ERROR,                    ///< Code 0
    UNKNOWN_OPTION,              ///< Code 1
    NOT_ENOUGH_OPTION_ARGUMENTS, ///< Code 2
    __INVALID_ERROR,             ///< Code 3
};

struct User_error
{
    char                   **data;
    size_t                 str_cnt;
    struct User_error_code code;

    bool                   is_valid;
};

errno_t construct_User_error(struct User_error *error_ptr, struct User_error_code code,
                                                           size_t str_cnt, ...);

void destruct_User_error(struct User_error *error_ptr);

struct Config
{
    struct FILE *input_stream,
                *output_stream;
    bool        is_help;

    bool        is_valid;
};

void destruct_Config(struct Config *config_ptr);

#endif
