#include <stdio.h>
#include <string.h>
#include "bin.h"

const char *get_hash() {
  return GIT_HASH;
}

const char *get_count() {
  return GIT_COUNT;
}

const char *get_branch() {
  return GIT_BRANCH;
}

void print_usage() {
  printf("Usage: %s [options]\r\n", BIN);
  printf("\r\n");
  printf("  /h or /?  Display usage information.\r\n");
  printf("  /v        Display version.\r\n");
}

int parse_args(int argc, char **argv) {
  int a;

  for (a = 1; a < argc; ++a) {
    if (strcmp(argv[a], "/?") == 0) {
      return ARG_USAGE;
    }
    if (strcmp(argv[a], "/h") == 0 || strcmp(argv[a], "/H") == 0) {
      return ARG_USAGE;
    }
    if (strcmp(argv[a], "/v") == 0 || strcmp(argv[a], "/V") == 0) {
      return ARG_VERSION;
    }
  }

  return ARG_NOTHING;
}

void print_version() {
  printf("%s-%s [%s]", get_branch(), get_count(), get_hash());
}
