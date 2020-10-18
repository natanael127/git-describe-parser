#ifdef _TEST_MODULE
    #include <stdio.h>
#endif /* _TEST_MODULE */
#include "git_describe_parser.h"

// Define _GIT_DESCRIPTION_STR and _GIT_COMMIT_HASH_STR in building time
// Define _TEST_MODULE for building the executable in order to test module in a standalone mode

#ifdef _TEST_MODULE
int main(void)
{
    printf("Raw data:\n");
    printf(_GIT_DESCRIPTION_STR "\n");
    printf(_GIT_COMMIT_HASH_STR "\n");

    return 0;
}
#endif /* _TEST_MODULE */
