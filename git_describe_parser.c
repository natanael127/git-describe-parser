#include <stdio.h>
#include "git_describe_parser.h"

// Define _GIT_DESCRIPTION_STR and _GIT_COMMIT_HASH_STR in building time
// Define _TEST_MODULE for building the executable

#ifdef _TEST_MODULE
int main(void)
{
    printf(_GIT_DESCRIPTION_STR);
    printf(_GIT_COMMIT_HASH_STR);

    return 0;
}
#endif
