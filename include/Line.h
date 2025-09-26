#ifndef LINE_H
#define LINE_H

#include "Common.h"

struct One_line
{
    char const *beg,
               *end;
};

errno_t split_text(size_t *const lines_cnt, struct One_line **const lines,
                   size_t const text_len, char const *const text);

int my_q_cmp(void const *str1_ptr, void const *str2_ptr);

int my_rev_cmp(struct One_line const *str1_ptr, struct One_line const *str2_ptr);

void swap_One_line(struct One_line *ptr1, struct One_line *ptr2);

void my_sort(size_t arr_len, struct One_line *arr,
             int (*cmp)(struct One_line const *, struct One_line const *));

#endif
