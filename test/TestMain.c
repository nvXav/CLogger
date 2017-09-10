#include "CLogger.h"

int main(int argc, char **argv)
{
    set_save_log("", "");
    CLOGPRINT("Print test %% %s of number %d", "y", 22);
    CLOGWARN("Warning test %% %s of number %d", "y", 22);
    CLOGERROR("Error test %% %s of number %d", "y", 22);

    return 0;
}
