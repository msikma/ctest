#ifndef GAME_STATE_H
#define GAME_STATE_H

typedef struct game_state_obj {
  int loop_state;
  int player_lives;
} game_state_obj;

extern game_state_obj game_state;

void initialize_game_state();

#endif
