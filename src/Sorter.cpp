#include "Sorter.h"

errno_t make_sort(size_t *const lines_cnt, One_line **const lines,
                  size_t const text_len, char const *const text)
{
    assert(lines_cnt and lines and text);

    int ret_err = split_text(lines_cnt, lines, text_len, text);
    if (ret_err)
    {
        return ret_err;
    }

#ifdef _DEBUG

    printf("\n\n%zd\n", *lines_cnt);
    for (size_t i = 0; i < *lines_cnt; ++i)
    {
        printf("%td ", (*lines)[i].beg - text);
    }

#endif

    qsort(*lines, *lines_cnt, sizeof(One_line), my_q_cmp);
    //TODO - put somewhere
    FILE *out_ptr = fopen("For_srt.txt", "w");
    for (size_t i = 0; i < *lines_cnt; ++i)
    {
        fwrite((*lines)[i].beg, sizeof(char), (*lines)[i].end - (*lines)[i].beg, out_ptr);
        fputc('\n', out_ptr);
    }
    fclose(out_ptr);

#ifdef _DEBUG

    printf("\n\n%zd\n", *lines_cnt);
    for (size_t i = 0; i < *lines_cnt; ++i)
    {
        printf("%td ", (*lines)[i].beg - text);
    }

#endif

    return 0;
}

errno_t make_rev_sort(size_t *const lines_cnt, One_line **const lines,
                      size_t const text_len, char const *const text)
{
    assert(lines_cnt and lines and text);

    int ret_err = split_text(lines_cnt, lines, text_len, text);
    if (ret_err)
    {
        return ret_err;
    }

#ifdef _DEBUG

    printf("\n\n%zd\n", *lines_cnt);
    for (size_t i = 0; i < *lines_cnt; ++i)
    {
        printf("%td ", (*lines)[i].beg - text);
    }

#endif

    my_sort(*lines_cnt, *lines, &my_rev_cmp);
    //TODO - put somewhere
    FILE *out_ptr = fopen("Rev_srt.txt", "w");
    for (size_t i = 0; i < *lines_cnt; ++i)
    {
        fwrite((*lines)[i].beg, sizeof(char), (*lines)[i].end - (*lines)[i].beg, out_ptr);
        fputc('\n', out_ptr);
    }
    fclose(out_ptr);

#ifdef _DEBUG

    printf("\n\n%zd\n", *lines_cnt);
    for (size_t i = 0; i < *lines_cnt; ++i)
    {
        printf("%td ", (*lines)[i].beg - text);
    }

#endif

    return 0;
}
