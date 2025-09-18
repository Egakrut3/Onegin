#include "Option_manager.h"
#include <string.h>

enum Option
{
    IN_OPTION,
    __OPTIONS_COUNT,
};

static errno_t set_in_config(User_error *const error_ptr, Config *const config_ptr,
                             char const *const **const str_ptr,
                             char const *const *const end_str)
{
    assert(error_ptr and !error_ptr->is_valid and
           config_ptr and !config_ptr->is_valid and
           str_ptr and *str_ptr and end_str and
           *str_ptr != end_str and !strcmp(**str_ptr, "--in"));

    if (++*str_ptr == end_str)
    {
        return construct_User_error(error_ptr, NOT_ENOUGH_OPTION_ARGUMENTS, 1, "--in");
    }

    if (fopen_s(&config_ptr->input_stream, **str_ptr, "r"))
    {
        perror("fopen_s failed");
        return 1;
    }

    return construct_User_error(error_ptr, NO_ERROR, 0);
}

static char const *const flag_option_arr[__OPTIONS_COUNT] = {
       "--in",
};

static errno_t (*const set_option_arr[__OPTIONS_COUNT])(User_error *const, Config *const,
                                                       char const *const **const,
                                                       char const *const *const) = {
       &set_in_config,
};

static errno_t select_option_setter(User_error *const error_ptr, Config *const config_ptr,
                                    char const *const **const str_ptr,
                                    char const *const *const end_str,
                                    bool *const used_options)
{
    assert(error_ptr and !error_ptr->is_valid and
           config_ptr and !config_ptr->is_valid and
           str_ptr and *str_ptr and end_str and
           *str_ptr != end_str and
           used_options);

    for (size_t i = 0; i < __OPTIONS_COUNT; ++i)
    {
        if (strcmp(**str_ptr, flag_option_arr[i]))
        {
            continue;
        }

        used_options[i] = true;
        return set_option_arr[i](error_ptr, config_ptr, str_ptr, end_str);
    }

    return construct_User_error(error_ptr, UNKNOWN_OPTION, 1, **str_ptr);
}

errno_t set_config(User_error *const error_ptr, Config *const config_ptr,
                   size_t const argc, char const *const *const argv)
{
    assert(error_ptr and !error_ptr->is_valid and
           config_ptr and !config_ptr->is_valid and
           argc > 0 and argv);

    char const *const *const end_str = argv + argc;

    assert(end_str);

    bool used_options[__OPTIONS_COUNT] = {};
    for (char const *const *str = argv + 1; str != end_str; ++str)
    {
        assert(str and *str);

        errno_t ret_err = select_option_setter(error_ptr, config_ptr, &str, end_str, used_options);
        if (ret_err)
        {
            return ret_err;
        }

        if (error_ptr->code != NO_ERROR)
        {
            error_ptr->is_valid = true;
            return 0;
        }

        error_ptr->is_valid = false;
    }

    if (!used_options[IN_OPTION])
    {
        return construct_User_error(error_ptr, NO_INPUT_FILE, 0);
    }

    config_ptr->is_valid = true;
    return construct_User_error(error_ptr, NO_ERROR, 0);
}
