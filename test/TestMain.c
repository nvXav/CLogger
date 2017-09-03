#include "CLogger.h"

int main(int argc, char **argv)
{
    CLOGPRINT("This is a %% %s of number %d", "y", 22);
    CLOGWARN("This is a %s of number %d", "y", 22);
    CLOGERROR("This is a %s of number %d", "y", 22);

    return 0;
}
