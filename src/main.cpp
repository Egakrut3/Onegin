#include "Common.h"
#include "Option_manager.h"
#include "User_error_handler.h"
#include "File_input.h"
#include "Line.h"
#include <stdlib.h>

#define SET_CONFIG(cur_config, argc, argv) do                           \
{                                                                       \
    User_error cur_error = {nullptr, 0, __INVALID_ERROR, false};        \
    if (set_config(&cur_error, &cur_config, argc, argv))                \
    {                                                                   \
        destruct_User_error(&cur_error);                                \
                                                                        \
        if (destruct_Config(&cur_config)) { return 0; }                 \
                                                                        \
        return 0;                                                       \
    }                                                                   \
                                                                        \
    if (handle_User_error(&cur_error))                                  \
    {                                                                   \
        destruct_User_error(&cur_error);                                \
                                                                        \
        if (destruct_Config(&cur_config)) { return 0; }                 \
                                                                        \
        return 0;                                                       \
    }                                                                   \
                                                                        \
    destruct_User_error(&cur_error);                                    \
} while (false)

static errno_t make_sort(Config const *const config_ptr, size_t *const lines_cnt, One_line **const lines,
                  size_t const text_len, char const *const text)
{
    assert(lines_cnt); assert(lines); assert(text);

    if (split_text(lines_cnt, lines, text_len, text)) { return 1; }

#ifdef _DEBUG

    printf("\n\n%zd\n", *lines_cnt);
    for (size_t i = 0; i < *lines_cnt; ++i)
    {
        printf("%td ", (*lines)[i].beg - text);
    }

#endif

    qsort(*lines, *lines_cnt, sizeof(One_line), my_q_cmp);
    for (size_t i = 0; i < *lines_cnt; ++i)
    {
        fwrite((*lines)[i].beg, sizeof(char), (*lines)[i].end - (*lines)[i].beg,
               config_ptr->output_stream);
        fputc('\n', config_ptr->output_stream);
    }

#ifdef _DEBUG

    printf("\n\n%zd\n", *lines_cnt);
    for (size_t i = 0; i < *lines_cnt; ++i)
    {
        printf("%td ", (*lines)[i].beg - text);
    }

#endif

    return 0;
}

static errno_t make_rev_sort(Config const *const config_ptr, size_t *const lines_cnt, One_line **const lines,
                      size_t const text_len, char const *const text)
{
    assert(lines_cnt); assert(lines); assert(text);

    if (split_text(lines_cnt, lines, text_len, text)) { return 1; }

#ifdef _DEBUG

    printf("\n\n%zd\n", *lines_cnt);
    for (size_t i = 0; i < *lines_cnt; ++i)
    {
        printf("%td ", (*lines)[i].beg - text);
    }

#endif

    my_sort(*lines_cnt, *lines, &my_rev_cmp);
    for (size_t i = 0; i < *lines_cnt; ++i)
    {
        fwrite((*lines)[i].beg, sizeof(char), (*lines)[i].end - (*lines)[i].beg,
               config_ptr->output_stream);
        fputc('\n', config_ptr->output_stream);
    }

#ifdef _DEBUG

    printf("\n\n%zd\n", *lines_cnt);
    for (size_t i = 0; i < *lines_cnt; ++i)
    {
        printf("%td ", (*lines)[i].beg - text);
    }

#endif

    return 0;
}

int main(int const argc, char const *const *const argv)
{
    Config cur_config = {nullptr, nullptr, false, false};
    SET_CONFIG(cur_config, argc, argv);
    if (cur_config.is_help)
    {
        if (destruct_Config(&cur_config)) { return 0; }

        return 0;
    }

    size_t text_len = 0;
    char *text = nullptr;
    if (get_all_content(&cur_config, &text_len, &text))
    {
        free(text);

        if (destruct_Config(&cur_config)) { return 0; }

        return 0;
    }

    size_t lines1_cnt = 0;
    One_line *lines1 = nullptr;
    if (make_sort(&cur_config, &lines1_cnt, &lines1, text_len, text))
    {
        free(text);
        free(lines1);

        if (destruct_Config(&cur_config)) { return 0; }

        return 0;
    }

    fputs("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n",
          cur_config.output_stream);
    free(lines1);

    size_t lines2_cnt = 0;
    One_line *lines2 = nullptr;
    if (make_rev_sort(&cur_config, &lines2_cnt, &lines2, text_len, text))
    {
        free(text);
        free(lines2);

        if (destruct_Config(&cur_config)) { return 0; }

        return 0;
    }

    fputs("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n",
          cur_config.output_stream);
    free(lines2);

    fwrite(text, sizeof(char), text_len, cur_config.output_stream);
    free(text);

    if (destruct_Config(&cur_config)) { return 0; }

    colored_printf(RED, BLACK, "\n\n\nCOMMIT GITHUB\n\n");
    return 0;
}
