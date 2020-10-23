/* Includes ----------------------------------------------------------------- */
#ifdef _TEST_MODULE
    #include <stdio.h>
#endif /* _TEST_MODULE */
#include "git_describe_parser.h"

/* Private definitions ------------------------------------------------------ */
// Define _GIT_DESCRIPTION_STR and _GIT_COMMIT_HASH_STR in building time
// Define _TEST_MODULE for building the executable 
// in order to test module in a standalone mode
#define INVALID_INTEGER_RESULT      -1

/* Private types ------------------------------------------------------------ */

/* Private variables -------------------------------------------------------- */

/* Private functions - prototypes ------------------------------------------- */

/* Private functions - implementation --------------------------------------- */
#ifdef _TEST_MODULE
int main(void)
{
    printf("Raw data:\n");
    printf(_GIT_DESCRIPTION_STR "\n");
    printf(_GIT_COMMIT_HASH_STR "\n");

    return 0;
}
#endif /* _TEST_MODULE */

/* Public functions --------------------------------------------------------- */
git_description_t git_describe_parse(void)
{
    // Dummy initialization of struct variables
    git_description_t result = {
        .commit_hash_short          = _GIT_COMMIT_HASH_STR,
        .raw_description            = _GIT_DESCRIPTION_STR,
        .commits_after_tag          = INVALID_INTEGER_RESULT,
        .used_version_numbers       = INVALID_INTEGER_RESULT,
        .release_candidate_number   = INVALID_INTEGER_RESULT,
        .is_dirty                   = false,
    };
    for (int counter = 0; counter < TAG_MAX_VERSION_NUMBERS; counter++) {
        result.version_numbers[counter] = INVALID_INTEGER_RESULT;
    }

    return result;
}
