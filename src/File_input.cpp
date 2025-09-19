#include "File_input.h"
#include <sys/types.h>
#include <sys/stat.h>

errno_t get_path_filesize(char const *const path, __int64 *const filesize)
{
    assert(path); assert(filesize);

    struct _stat64 buffer = {}; //TODO - uninitialized variable
    if (_stat64(path, &buffer))
    {
        __PRINT_LINE__();
        perror("_stat64 failed");
        return 1;
    }

    *filesize = buffer.st_size;

    assert(*filesize > 0);

    return 0;
}

errno_t get_opened_filesize(FILE *const cur_file, __int64 *const filesize)
{
    assert(cur_file); assert(filesize);

    struct _stat64 buffer = {};
    if (_fstat64(fileno(cur_file), &buffer))
    {
        __PRINT_LINE__();
        perror("_fstat64 failed");
        return 1;
    }

    *filesize = buffer.st_size;

    assert(*filesize > 0);

    return 0;
}

errno_t get_all_content(Config const *const config, size_t *const filesize, char **const buffer)
{
    assert(config); assert(filesize); assert(buffer);

    __int64 const start_pos = _ftelli64(config->input_stream);
    if (start_pos == -1L)
    {
        __PRINT_LINE__();
        perror("_ftelli64 failed");
        return 1;
    }

    get_opened_filesize(config->input_stream, (__int64 *)filesize);
    if (*filesize == 0)
    {
        __PRINT_LINE__();
        fprintf(stderr, "Input file is empty\n");
        return 1;
    }

    rewind(config->input_stream);
    *buffer = (char *)calloc(*filesize, sizeof(char));
    if (!*buffer)
    {
        __PRINT_LINE__();
        perror("calloc failed");
        if (_fseeki64(config->input_stream, start_pos, SEEK_SET))
        {
            __PRINT_LINE__();
            perror("_fseeki64 failed");
            return 1;
        }

        return 1;
    }

    if (fread(*buffer, sizeof(char), *filesize, config->input_stream) != *filesize)
    {
        __PRINT_LINE__();
        perror("fread failed");
        if (_fseeki64(config->input_stream, start_pos, SEEK_SET))
        {
            __PRINT_LINE__();
            perror("_fseeki64 failed");
            return 1;
        }

        return 1;
    }

    if (_fseeki64(config->input_stream, start_pos, SEEK_SET))
    {
        __PRINT_LINE__();
        perror("_fseeki64 failed");
        return 1;
    }

    return 0;
}
