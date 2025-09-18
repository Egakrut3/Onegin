#ifndef LINE_H
#define LINE_H

#include "Common.h"

struct One_line
{
    char const *beg;
    char const *end;
};

errno_t split_text(size_t *const lines_cnt, One_line **const lines,
                   size_t const text_len, char const *const text);

int my_q_cmp(void const *str1_ptr, void const *str2_ptr);

int my_rev_cmp(One_line const *str1_ptr, One_line const *str2_ptr);

void swap_One_line(One_line *ptr1, One_line *ptr2);

void my_sort(size_t arr_len, One_line *arr,
             int (*cmp)(One_line const *, One_line const *));

#endif
