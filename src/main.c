#include "main.h"
#include "lib/game.h"
#include "util/bin.h"

int main(int argc, char **argv) {
  int cmd;

  // Check command line arguments and run commands if necessary.
  // If no arguments were entered, the game boots up.
  cmd = parse_args(argc, argv);

  switch (cmd) {
    case ARG_USAGE:
      print_usage();
      return 0;
    case ARG_VERSION:
      print_version();
      return 0;
  }
  
  return run_game();
}
