#ifndef FILE_INPUT_H
#define FILE_INPUT_H

#include "Common.h"

errno_t get_all_content(Config const *config, size_t *filesize, char **buffer);

#endif
