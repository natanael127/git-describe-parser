#ifndef _GIT_DESCRIBE_PARSER_H_
#define _GIT_DESCRIBE_PARSER_H_
/* Includes ----------------------------------------------------------------- */
#include <stdbool.h>

/* Public definitions ------------------------------------------------------- */
#define TAG_MAX_VERSION_NUMBERS          0x04

/* Public types ------------------------------------------------------------- */
typedef struct
{
    char * commit_hash_short;
    char * raw_description;
    int version_numbers[TAG_MAX_VERSION_NUMBERS];
    int commits_after_tag;
    int used_version_numbers;
    int release_candidate_number;
    bool is_dirty;
} git_description_t;

/* Public variables --------------------------------------------------------- */

/* Public functions --------------------------------------------------------- */
git_description_t git_describe_parse(void);

#endif /* _GIT_DESCRIBE_PARSER_H_ */
