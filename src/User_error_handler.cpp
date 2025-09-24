#include "User_error_handler.h"

bool handle_User_error(User_error const *const error_ptr)
{
    assert(error_ptr); assert(error_ptr->is_valid);

    switch (error_ptr->code)
    {
        case NO_ERROR:
            assert(error_ptr->str_cnt == 0); assert(!error_ptr->data);

            return false;

        case UNKNOWN_OPTION:
            assert(error_ptr->str_cnt == 1); assert(error_ptr->data); assert(error_ptr->data[0]);

            printf("\"%s\" option is unknown\n", error_ptr->data[0]);
            return true;

        case NOT_ENOUGH_OPTION_ARGUMENTS:
            assert(error_ptr->str_cnt == 1); assert(error_ptr->data); assert(error_ptr->data[0]);

            printf("\"%s\" option requires more arguments after itself\n", error_ptr->data[0]);
            return true;

        case __INVALID_ERROR:
        default:
            __PRINT_LINE__();
            abort();

            return true;
    }
}
