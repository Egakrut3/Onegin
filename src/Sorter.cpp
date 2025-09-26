#include "Sorter.h"

errno_t make_sort(struct Config const *const config_ptr,
                  size_t *const lines_cnt, struct One_line **const lines,
                  size_t const text_len, char const *const text)
{
    assert(lines_cnt); assert(lines); assert(text);

#undef FINAL_CODE
#define FINAL_CODE

    CHECK_FUNC(split_text, lines_cnt, lines, text_len, text);

#ifdef _DEBUG

    printf("\n\n%zd\n", *lines_cnt);
    for (size_t i = 0; i < *lines_cnt; ++i)
    {
        printf("%td ", (*lines)[i].beg - text);
    }

#endif

    qsort(*lines, *lines_cnt, sizeof(struct One_line), &my_q_cmp);
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

    CLEAR_RESOURCES();
    return 0;
}

errno_t make_rev_sort(struct Config const *const config_ptr,
                      size_t *const lines_cnt, struct One_line **const lines,
                      size_t const text_len, char const *const text)
{
    assert(lines_cnt); assert(lines); assert(text);

#undef FINAL_CODE
#define FINAL_CODE

    CHECK_FUNC(split_text, lines_cnt, lines, text_len, text);

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

    CLEAR_RESOURCES();
    return 0;
}
