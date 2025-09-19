#ifndef COMMON_H
#define COMMON_H

#include "Colored_printf.h"
#include <errno.h>
#include <assert.h>
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>

#define __PRINT_LINE__() fprintf(stderr, "Error found, file " __FILE__ ", line %d\n", __LINE__)

enum User_error_code
{
    NO_ERROR,                    ///< Code 0
    UNKNOWN_OPTION,              ///< Code 1
    NOT_ENOUGH_OPTION_ARGUMENTS, ///< Code 2
    NO_INPUT_FILE,               ///< Code 3
    NO_OUTPUT_FILE,              ///< Code 4
    __INVALID_ERROR,             ///< Code 5
};

struct User_error
{
    char **data;
    size_t str_cnt;
    User_error_code code;

    bool is_valid;

    //User_error (User_error &) = delete;
    User_error &operator= (User_error &) = delete;
};

errno_t construct_User_error(User_error *error_ptr, User_error_code code,
                             size_t str_cnt, ...);

void destruct_User_error(User_error *error_ptr);

struct Config
{
    FILE *input_stream,
         *output_stream;
    bool is_help;

    bool is_valid;

    //Config (Config &) = delete;
    Config& operator=(Config &) = delete;
};

errno_t destruct_Config(Config *config_ptr);

#endif
