#ifndef SORTER_H
#define SORTER_H

#include "Common.h"
#include "Line.h"

errno_t make_sort(size_t *lines_cnt, One_line **lines,
                  size_t text_len, char const *text);

errno_t make_rev_sort(size_t *lines_cnt, One_line **lines, size_t text_len, char const *text);

#endif
