#include "Line.h"
#include <stdlib.h>
#include <ctype.h>

errno_t split_text(size_t *const lines_cnt, struct One_line **const lines,
                   size_t const text_len, char const *const text)
{
    assert(lines_cnt); assert(lines); assert(text);

#undef FINAL_CODE
#define FINAL_CODE

    *lines_cnt = 0;
    for (size_t i = 0; i < text_len; ++i)
    {
        if (text[i] == '\n')
        {
            ++*lines_cnt;
        }
    }
    ++*lines_cnt;

    *lines = (One_line *)calloc(*lines_cnt, sizeof(One_line));
    if (!*lines)
    {
        PRINT_LINE();
        perror("calloc failed");
        CLEAR_RESOURCES();
        return errno;
    }

    *lines_cnt = 0;
    (*lines)[*lines_cnt].beg = text;
    for (size_t i = 0; i < text_len; ++i)
    {
        if (text[i] == '\n')
        {
            (*lines)[*lines_cnt].end = text + i;
            ++*lines_cnt;
            (*lines)[*lines_cnt].beg = text + i + 1;
        }
    }
    (*lines)[*lines_cnt].end = text + text_len;
    ++*lines_cnt;

    CLEAR_RESOURCES();
    return 0;
}

static int my_cmp(struct One_line const *const str1_ptr, struct One_line const *const str2_ptr)
{
    assert(str1_ptr); assert(str2_ptr);

    char const *pos1 = str1_ptr->beg,
               *pos2 = str2_ptr->beg;

#undef FINAL_CODE
#define FINAL_CODE

    while (pos1 != str1_ptr->end and
           pos2 != str2_ptr->end)
    {
        char c1 = (char)tolower((int)*pos1),
             c2 = (char)tolower((int)*pos2);
        if (!isalpha(c1)) { ++pos1; continue; }
        if (!isalpha(c2)) { ++pos2; continue; }

        if      (c1 < c2) { CLEAR_RESOURCES(); return -1; }
        else if (c2 < c1) { CLEAR_RESOURCES(); return 1; }
        else { ++pos1; ++pos2; }
    }

    if (pos2 != str2_ptr->end) { CLEAR_RESOURCES(); return -1; }
    else
    {
        if (pos1 != str1_ptr->end) { CLEAR_RESOURCES(); return 1; }
        else { CLEAR_RESOURCES(); return 0; }
    }
}

int my_q_cmp(void const *const str1_ptr, void const *const str2_ptr)
{
    assert(str1_ptr); assert(str2_ptr);

#undef FINAL_CODE
#define FINAL_CODE

    CLEAR_RESOURCES();
    return my_cmp((struct One_line const *)str1_ptr, (struct One_line const *)str2_ptr);
}

int my_rev_cmp(struct One_line const *const str1_ptr, struct One_line const *const str2_ptr)
{
    assert(str1_ptr); assert(str2_ptr);

    char const *pos1 = str1_ptr->end - 1,
               *pos2 = str2_ptr->end - 1;

#undef FINAL_CODE
#define FINAL_CODE

    while (pos1 != str1_ptr->beg - 1 and
           pos2 != str2_ptr->beg - 1)
    {
        char c1 = (char)tolower((int)*pos1),
             c2 = (char)tolower((int)*pos2);
        if (!isalpha(c1)) { --pos1; continue; }
        if (!isalpha(c2)) { --pos2; continue; }

        if      (c1 < c2) { CLEAR_RESOURCES(); return -1; }
        else if (c1 > c2) { CLEAR_RESOURCES(); return 1; }
        else { --pos1; --pos2; }
    }

    if (pos2 != str2_ptr->beg - 1) { CLEAR_RESOURCES(); return -1; }
    else
    {
        if (pos1 != str1_ptr->beg - 1) { CLEAR_RESOURCES(); return 1; }
        else { CLEAR_RESOURCES(); return 0; }
    }
}

void swap_One_line(struct One_line *const ptr1, struct One_line *const ptr2)
{
    assert(ptr1); assert(ptr2);

    struct One_line temp_obj = *ptr1;

#undef FINAL_CODE
#define FINAL_CODE

    *ptr1 = *ptr2;
    *ptr2 = temp_obj;
    CLEAR_RESOURCES();
}

void my_sort(size_t const arr_len, struct One_line *const arr,
             int (*const cmp)(struct One_line const *, struct One_line const *))
{
    assert(arr); assert(cmp);

#undef FINAL_CODE
#define FINAL_CODE

    for (size_t sorted_size = 1; sorted_size < arr_len; ++sorted_size)
    {
        for (One_line *new_elem = arr + sorted_size; new_elem != arr; --new_elem)
        {
            if (cmp(new_elem - 1, new_elem) <= 0) { break; } //TODO - too much nesting

            swap_One_line(new_elem - 1, new_elem);
        }
    }

    CLEAR_RESOURCES();
}
