/* Includes ----------------------------------------------------------------- */
#ifdef _TEST_MODULE
    #include <stdio.h>
#endif /* _TEST_MODULE */
#include <string.h>
#include <stddef.h>
#include "git_describe_parser.h"

/* Private definitions ------------------------------------------------------ */
// Define _GIT_DESCRIPTION_STR and _GIT_COMMIT_HASH_STR in building time
// Define _TEST_MODULE for building the executable 
// in order to test module in a standalone mode
#define INVALID_INTEGER_RESULT      -1
#define DIRTY_MARKER                "-dirty"

/* Private types ------------------------------------------------------------ */

/* Private variables -------------------------------------------------------- */

/* Private functions - prototypes ------------------------------------------- */
static bool is_number(char this_char);

/* Private functions - implementation --------------------------------------- */
static bool is_number(char this_char)
{
    return (this_char >= '0' && this_char <= '9');
}

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
    // Process variables
    char *str_aux = NULL, str_find_num[3] = "-0";
    bool already_found_number[TAG_MAX_VERSION_NUMBERS];

    // Dummy initialization of struct variables
    git_description_t result = {
        .commit_hash_short          = _GIT_COMMIT_HASH_STR,
        .raw_description            = _GIT_DESCRIPTION_STR,
        .commits_after_tag          = 0,
        .used_version_numbers       = 0,
        .release_candidate_number   = INVALID_INTEGER_RESULT,
        .is_dirty                   = true,
    };
    for (int counter = 0; counter < TAG_MAX_VERSION_NUMBERS; counter++) {
        result.version_numbers[counter] = 0;
        already_found_number[counter] = false;
    }

    // Identifies version numbers
    str_aux = result.raw_description;
    while (*str_aux != '\0' && *str_aux != '-' && result.used_version_numbers <= TAG_MAX_VERSION_NUMBERS) {
        if (is_number(*str_aux)) {
            already_found_number[result.used_version_numbers] = true;
            result.version_numbers[result.used_version_numbers] *= 10;
            result.version_numbers[result.used_version_numbers] += (*str_aux) - '0';
        } else if (already_found_number[result.used_version_numbers] == true) {
            result.used_version_numbers++;
        }
        str_aux++;
    }
    if (already_found_number[result.used_version_numbers] == true) {
        result.used_version_numbers++;
    }

    // Try to find variations of "-rc" for release candidate
    str_aux = NULL;
    if (str_aux == NULL) {
        str_aux = strstr(result.raw_description, "-rc");
    }
    if (str_aux == NULL) {
        str_aux = strstr(result.raw_description, "-rC");
    }
    if (str_aux == NULL) {
        str_aux = strstr(result.raw_description, "-Rc");
    }
    if (str_aux == NULL) {
        str_aux = strstr(result.raw_description, "-RC");
    }

    // If has found any variation of "-rc"
    if (str_aux != NULL) {
        str_aux += strlen("-rc");
        result.release_candidate_number = 0;
        while (is_number(*str_aux)) {
            result.release_candidate_number *= 10; 
            result.release_candidate_number += (*str_aux) - '0';
            str_aux++;
        }
    }

    // Looks for number of commits after tag (sequence '-<number>')
    int counter = 0;
    while (result.commits_after_tag == 0 && counter <= 9) {
        str_find_num[1] = counter + '0';
        str_aux = strstr(result.raw_description, str_find_num);
        if (str_aux != NULL) {
            str_aux += strlen("-");
            while (is_number(*str_aux)) {
                result.commits_after_tag *= 10;
                result.commits_after_tag += (*str_aux) - '0';
                str_aux++;
            }
        }
        counter++;
    }

    // Checks for marker '-dirty'
    result.is_dirty = strstr(result.raw_description, DIRTY_MARKER) != NULL;

    return result;
}
