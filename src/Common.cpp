#include "Common.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

errno_t construct_User_error(User_error *const error_ptr, User_error_code const code,
                             size_t const str_cnt, ...)
{
    assert(error_ptr and !error_ptr->is_valid);

    error_ptr->code = code;
    error_ptr->str_cnt = str_cnt;
    if (!str_cnt)
    {
        error_ptr->data = nullptr;
        error_ptr->is_valid = true;
        return 0;
    }

    error_ptr->data = (char **)calloc(str_cnt, sizeof(char *));
    if (!error_ptr->data)
    {
        perror("calloc failed");
        return 1;
    }

    va_list arg_list = nullptr;
    va_start(arg_list, str_cnt);
    for (size_t i = 0; i < str_cnt; ++i)
    {
        char const *const new_str = va_arg(arg_list, char const *);

        assert(new_str);

        error_ptr->data[i] = strdup(new_str);
        if (!error_ptr->data[i])
        {
            perror("strdup failed");
            return 1;
        }
    }

    va_end(arg_list);
    error_ptr->is_valid = true;
    return 0;
}

void destruct_User_error(User_error *const error_ptr)
{
    assert(error_ptr and error_ptr->is_valid);

    error_ptr->is_valid = false;
    for (size_t i = 0; i < error_ptr->str_cnt; ++i)
    {
        assert(error_ptr->data and error_ptr->data[i]);

        free(error_ptr->data[i]);
    }

    free(error_ptr->data);
    return;
}

errno_t destruct_Config(Config *const config_ptr)
{
    assert(config_ptr);

    config_ptr->is_valid = false;
    if (fclose(config_ptr->input_stream))
    {
        perror("fclose failed");
        return 1;
    }

    return 0;
}
