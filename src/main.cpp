#include "Common.h"
#include "Option_manager.h"
#include "User_error_handler.h"
#include "File_input.h"
#include "Line.h"
#include "Sorter.h"
#include <stdlib.h>

#define SET_CONFIG(cur_config, argc, argv) do                           \
{                                                                       \
    User_error cur_error = {nullptr, 0, __INVALID_ERROR, false};        \
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

    size_t text_len = 0;
    char *text = nullptr;
    if (get_all_content(&cur_config, &text_len, &text))
    {
        free(text);
        if (destruct_Config(&cur_config))
        {
            return 0;
        }

        return 0;
    }

    size_t lines1_cnt = 0;
    One_line *lines1 = nullptr;
    if (make_sort(&lines1_cnt, &lines1, text_len, text))
    {
        free(text);
        free(lines1);
        if (destruct_Config(&cur_config))
        {
            return 0;
        }

        return 0;
    }

    free(lines1);

    size_t lines2_cnt = 0;
    One_line *lines2 = nullptr;
    if (make_rev_sort(&lines2_cnt, &lines2, text_len, text))
    {
        free(text);
        free(lines2);
        if (destruct_Config(&cur_config))
        {
            return 0;
        }

        return 0;
    }

    free(lines2);

    //TODO - put somewhere
    FILE *out_ptr = fopen("Whole_text.txt", "w");
    fwrite(text, sizeof(char), text_len, out_ptr);
    fclose(out_ptr);

    free(text);
    if (destruct_Config(&cur_config))
    {
        return 0;
    }

    printf("\n\n\nCOMMIT GITHUB\n\n");
    return 0;
}
