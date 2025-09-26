#include "Common.h"
#include "Option_manager.h"
#include "User_error_handler.h"
#include "File_input.h"
#include "Line.h"
#include "Sorter.h"

int main(int const argc, char const *const *const argv)
{
    assert(argc > 0); assert(argv); assert(*argv);

    struct Config cur_config = {};
    struct User_error cur_error = {};
    size_t text_len = 0;
    char *text = nullptr;
    size_t lines_cnt = 0;
    struct One_line *lines = nullptr;

#undef FINAL_CODE
#define FINAL_CODE                      \
    destruct_Config(&cur_config);       \
    destruct_User_error(&cur_error);    \
    free(text);                         \
    free(lines);

    MAIN_CHECK_FUNC(set_config, &cur_error, &cur_config, argc, argv);
    if (handle_User_error(&cur_error)) { CLEAR_RESOURCES(); return 0; }
    if (cur_config.is_help) { CLEAR_RESOURCES(); return 0; }

    MAIN_CHECK_FUNC(get_all_content, &cur_config, &text_len, &text);

    MAIN_CHECK_FUNC(make_sort, &cur_config, &lines_cnt, &lines, text_len, text);
    fputs("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n",
          cur_config.output_stream);

    MAIN_CHECK_FUNC(make_rev_sort, &cur_config, &lines_cnt, &lines, text_len, text);
    fputs("\n\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n",
          cur_config.output_stream);

    fwrite(text, sizeof(char), text_len, cur_config.output_stream);

    colored_printf(RED, BLACK, "\n\n\nCOMMIT GITHUB\n\n");
    CLEAR_RESOURCES();
    return 0;
}
