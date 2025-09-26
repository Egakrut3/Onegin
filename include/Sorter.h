#ifndef SORTER_H
#define SORTER_H

#include "Common.h"
#include "Line.h"

errno_t make_sort(struct Config const *config_ptr,
                  size_t *lines_cnt, struct One_line **lines,
                  size_t text_len, char const *text);

errno_t make_rev_sort(struct Config const *config_ptr,
                      size_t *lines_cnt, struct One_line **lines,
                      size_t text_len, char const *text);

#endif
