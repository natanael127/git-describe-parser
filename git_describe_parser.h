#ifndef _GIT_DESCRIBE_PARSER_H_
#define _GIT_DESCRIBE_PARSER_H_
/* Includes ----------------------------------------------------------------- */
#include <stdbool.h>

/* Public definitions ------------------------------------------------------- */
#define TAG_MAX_VERSION_NUMBERS          0x04

/* Public types ------------------------------------------------------------- */
typedef struct
{
    // Result of 'git rev-parse HEAD'
    char * commit_hash_short;
    // Result of 'git describe --dirty=-dirty'
    char * raw_description;
    // First numbers of tag, separated by any separator, except '-'
    int version_numbers[TAG_MAX_VERSION_NUMBERS];
    int used_version_numbers;
    // Number of commits after the described tag
    int commits_after_tag;
    // Number after symbol '-RC', returns negative if does not exist '-RC'
    int release_candidate_number;
    // 'false' if working tree clean and 'true' if there are uncommited changes
    bool is_dirty;
} git_description_t;

/* Public variables --------------------------------------------------------- */

/* Public functions --------------------------------------------------------- */
git_description_t git_describe_parse(void);

#endif /* _GIT_DESCRIBE_PARSER_H_ */
