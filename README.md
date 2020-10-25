# Git Description Parser
This project intends to interpret the current commit of the project and let it available to the *C* code in a easy format. It bases on the tags declared by developer on the git tree.

## Supported tag format
A concatenated string containing the following fields in order:

(Name)(Version Numbers)(Release Candidate)

**Examples:**
- V1.3.5
- VERSION_2.4-RC6

### Name (optional)
A non-numeric sequence.
'-' is a forbidden character to this field.

**Examples:**
- V
- VERSION
- PROJECT_NAME

### Version Numbers (mandatory)
A sequence of positive decimal numbers separated by any non-numeric separator (except '-').
The maximum quantity of numbers in this sequence is given by the definition `TAG_MAX_VERSION_NUMBERS` (default = 4).

**Examples:**
- 1.0.5
- 10,6/7x8

### Release Candidate (optional)
The tag may be a release or even a release candidate. To specify a release candidate, this field must be present.
It must be started by sequence '-rc', which is case insensitive (ie. '-rc' will be the same as '-RC' or '-rC' or '-Rc'), followed by a positive decimal number.

**Examples:**
- \-rc15
- \-Rc2

## Parsed data
The output of the parsing task will be composed by following fields:

### Commit hash
It gives the current commit hash in the short format (7 hex characters).

### Raw description
Raw output of command `git describe --dirty=-dirty`

### Version numbers
Version numbers are available to the array `version_numbers`, while the number of used position is given at `used_version_numbers`

### Release candidate number
The number of release candidate. Negative means it's not a release candidate.

### Number of commits after the nearest tag
How many commits were made after the nearest tag behind it.

### Flag dirty
Signals `false` if working tree clean and `true` if there are uncommited changes in the project files.
