#include "Common.h"
#include "Option_manager.h"
#include "User_error_handler.h"
#include "File_input.h"

#define SET_CONFIG(cur_config, argc, argv) do                           \
{                                                                       \
    User_error cur_error = {0, nullptr, __INVALID_ERROR, false};        \
    errno_t ret_err = set_config(&cur_error, &cur_config, argc, argv);  \
    if (ret_err)                                                        \
    {                                                                   \
        destruct_User_error(&cur_error);                                \
        if (destruct_Config(&cur_config))                               \
        {                                                               \
            return 0;                                                   \
        }                                                               \
                                                                        \
        return 0;                                                       \
    }                                                                   \
                                                                        \
    if (handle_User_error(&cur_error))                                  \
    {                                                                   \
        destruct_User_error(&cur_error);                                \
        if (destruct_Config(&cur_config))                               \
        {                                                               \
            return 0;                                                   \
        }                                                               \
                                                                        \
        return 0;                                                       \
    }                                                                   \
                                                                        \
    destruct_User_error(&cur_error);                                    \
} while (false)

int main(int const argc, char const *const *const argv)
{
    Config cur_config = {nullptr, false};
    SET_CONFIG(cur_config, argc, argv);

    char *data = nullptr;
    size_t filesize = 0;
    if (get_all_content(&cur_config, &filesize, &data))
    {
        free(data);
        if (destruct_Config(&cur_config))
        {
            return 0;
        }

        return 0;
    }

    printf("%s", data);

    free(data);
    if (destruct_Config(&cur_config))
    {
        return 0;
    }

    printf("\n\n\nCOMMIT GITHUB\n\n");
    return 0;
}
