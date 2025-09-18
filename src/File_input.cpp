#include "File_input.h"

errno_t get_all_content(Config const *const config, size_t *const filesize, char **const buffer)
{
    assert(config and filesize and buffer);

    if (fseek(config->input_stream, 0, SEEK_END))
    {
        perror("fseek failed");
        return 1;
    }

    *filesize = ftell(config->input_stream) + 1;
    if (*filesize == (size_t)-1L)
    {
        perror("ftell failed");
        return 1;
    }

    if (*filesize == 0)
    {
        fprintf(stderr, "Input file is empty\n");
        return 1;
    }

    rewind(config->input_stream);
    *buffer = (char *)calloc(*filesize, sizeof(char));
    if (!*buffer)
    {
        perror("calloc failed");
        return 1;
    }

    if (fread(*buffer, sizeof(char), *filesize - 1, config->input_stream) != *filesize - 1)
    {
        perror("fread failed");
        return 1;
    }

    return 0;
}
