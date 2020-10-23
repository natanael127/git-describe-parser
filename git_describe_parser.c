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
    git_description_t my_description = git_describe_parse();

    printf("Commit hash: %s\n", my_description.commit_hash_short);
    printf("Raw description: %s\n", my_description.raw_description);
    printf("Version numbers: ");
    for (int counter = 0; counter < my_description.used_version_numbers; counter++) {
        printf("%i.", my_description.version_numbers[counter]);
    }
    printf("\b \n");
    printf("There are %i commits after the last tag\n", my_description.commits_after_tag);
    if (my_description.release_candidate_number < 0) {
        printf("It's a release!\n");
    } else {
        printf("It's just the release candidate #%i\n", my_description.release_candidate_number);
    }
    if (my_description.is_dirty) {
        printf("There are uncommited changes\n");
    } else {
        printf("Working tree clean\n");
    }

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
        .is_dirty                   = true,
    };
    for (int counter = 0; counter < TAG_MAX_VERSION_NUMBERS; counter++) {
        result.version_numbers[counter] = INVALID_INTEGER_RESULT;
    }

    return result;
}
