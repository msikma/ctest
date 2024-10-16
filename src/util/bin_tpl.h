#ifndef VERSION_H
#define VERSION_H

#define ARG_NOTHING 1
#define ARG_VERSION 2
#define ARG_USAGE 3

const char *get_branch();
const char *get_count();
const char *get_hash();
int parse_args(int argc, char **argv);
void print_usage();
void print_version();

#define GIT_HASH "%%GIT_HASH%%"
#define GIT_COUNT "%%GIT_COUNT%%"
#define GIT_BRANCH "%%GIT_BRANCH%%"
#define GIT_VERSION "%%GIT_VERSION%%"
#define GIT_DATE "%%GIT_DATE%%"
#define BIN "%%BIN%%"

#endif
