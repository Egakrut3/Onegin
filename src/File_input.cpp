#include "File_input.h"
#include <sys/types.h>
#include <sys/stat.h>

errno_t get_path_filesize(char const *const path, __int64 *const filesize)
{
#undef FINISH_CODE
#define FINISH_CODE

    assert(path); assert(filesize);

    struct _stat64 buffer = {};
    CHECK_FUNC(_stat64, path, &buffer);
    *filesize = buffer.st_size;

    assert(*filesize > 0);

    CLEAR_RESOURCES();
    return 0;
}

errno_t get_opened_filesize(struct FILE *const cur_file, __int64 *const filesize)
{
#undef FINISH_CODE
#define FINISH_CODE

    assert(cur_file); assert(filesize);

    struct _stat64 buffer = {};
    CHECK_FUNC(_fstat64, fileno(cur_file), &buffer);
    *filesize = buffer.st_size;

    assert(*filesize > 0);

    CLEAR_RESOURCES();
    return 0;
}

errno_t get_all_content(Config const *const config, size_t *const filesize, char **const buffer)
{
#undef FINISH_CODE
#define FINISH_CODE

    assert(config); assert(filesize); assert(buffer);

    __int64 const start_pos = _ftelli64(config->input_stream);
    if (start_pos == -1L)
    {
        PRINT_LINE();
        perror("_ftelli64 failed");
        CLEAR_RESOURCES();
        return errno;
    }

    get_opened_filesize(config->input_stream, (__int64 *)filesize);
    if (*filesize == 0)
    {
        errno = EEMPTY_INP;

        PRINT_LINE();
        fprintf(stderr, "Input file is empty\n");
        CLEAR_RESOURCES();
        return errno;
    }

    rewind(config->input_stream);
    *buffer = (char *)calloc(*filesize, sizeof(char));
    if (!*buffer)
    {
        PRINT_LINE();
        perror("calloc failed");
        if (_fseeki64(config->input_stream, start_pos, SEEK_SET)) //TODO - make clear
        {
            PRINT_LINE();
            perror("_fseeki64 failed");
            return errno;
        }

        return errno;
    }

    if (fread(*buffer, sizeof(char), *filesize, config->input_stream) != *filesize)
    {
        PRINT_LINE();
        perror("fread failed");
        if (_fseeki64(config->input_stream, start_pos, SEEK_SET))
        {
            PRINT_LINE();
            perror("_fseeki64 failed");
            return errno;
        }

        return errno;
    }

    if (_fseeki64(config->input_stream, start_pos, SEEK_SET))
    {
        PRINT_LINE();
        perror("_fseeki64 failed");
        return errno;
    }

    return 0;
}
