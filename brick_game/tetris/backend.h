#ifndef TETRIS_H
#define TETRIS_H

#include <stdbool.h>
// #include <ncurses.h>
#include <curses.h>

#define Start 1
#define Pause 2
#define Terminate 3
#define Left 4
#define Right 5
#define Up 6
#define Down 7
#define Action 8
#define NOP 9

typedef struct {
  int position[2];
  int shape[3][3];
  int count_of_turn;
  int length;
  int high;
} Current;

typedef struct {
  int field[20][10];
  int next[3][3];
  int score;
  int max_score;
  int level;
  int lines; //////переделать (???????????)
  int speed;
  int action;
  int pause;
} GameInfo_t;

int getScore(void);

void setScore(int score);

GameInfo_t *create_next_figure(GameInfo_t *tetr, int blocks[7][3][3]);

GameInfo_t *create_game(GameInfo_t *tetr, int blocks[7][3][3]);
///
void get_info_from_user(GameInfo_t *tetr);

int line_is_full(GameInfo_t *tetr, int i);

void delete_line(GameInfo_t *tetr, int n);

int is_collision(GameInfo_t *tetr, Current figure);

Current *invert(Current *figure);

void update_score(GameInfo_t *tetr);

void update_lines(GameInfo_t *tetr);

int move_down(GameInfo_t *tetr, Current *figure);

int move_left(Current *figure);

int move_right(Current *figure);

void move_down_to_the_end(GameInfo_t *tetr, Current *figure);

GameInfo_t *update_field(GameInfo_t *tetr, Current figure);

int lines_is_full(Current figure);

GameInfo_t *updateCurrentState(GameInfo_t *tetr, Current *figure,
                               int blocks[7][3][3]);

Current *create_figure(Current *figure);

Current *calculete(GameInfo_t *tetr, Current *figure);

#endif
