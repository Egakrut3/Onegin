#ifndef COMMON_H
#define COMMON_H

#include <errno.h>
#include <assert.h>
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>

enum User_error_code
{
    NO_ERROR,
    UNKNOWN_OPTION,
    NOT_ENOUGH_OPTION_ARGUMENTS,
    NO_INPUT_FILE,
    __INVALID_ERROR,
};

struct User_error
{
    size_t str_cnt;
    char **data;
    User_error_code code;

    bool is_valid;

    User_error (User_error &) = delete;
    User_error &operator= (User_error &) = delete;
};

errno_t construct_User_error(User_error *error_ptr, User_error_code code,
                             size_t str_cnt, ...);

void destruct_User_error(User_error *error_ptr);

struct Config
{
    FILE *input_stream;

    bool is_valid;

    Config (Config &) = delete;
    Config& operator=(Config &) = delete;
};

errno_t destruct_Config(Config *config_ptr);

#endif
