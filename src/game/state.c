#include <stddef.h>
#include "state.h"

// Primary game state object.
game_state_obj game_state;

void initialize_game_state() {
  game_state_obj game_state = {
    // Which loop state to transition into after initial setup.
    .loop_state = 0,
    .player_lives = 3
  };
}
