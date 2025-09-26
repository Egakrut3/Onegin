#ifndef FILE_INPUT_H
#define FILE_INPUT_H

#include "Common.h"

errno_t get_path_filesize(char const *path, __int64 *filesize);

errno_t get_opened_filesize(FILE *cur_file, __int64 *filesize);

errno_t get_all_content(struct Config const *config, size_t *filesize, char **buffer);

#endif
