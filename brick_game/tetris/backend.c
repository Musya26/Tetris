#include "backend.h" //сегается!!!!!!!
                     //тесты переделать!!!
                     //курсор (?)
#include <math.h> ////////////скорость сделано, надо проверить!!!!
#include <stdio.h>
#include <stdlib.h> //мейк доделать

int getScore(void) { // считывание очков
  FILE *file = NULL;
  int score = 0;
  if ((file = fopen("max_score.txt", "r"))) {
    fscanf(file, "%d", &score);
    fclose(file);
  }

  return score;
}

void setScore(int score) { /// записать очки
  FILE *file = NULL;
  if ((file = fopen("max_score.txt", "w"))) {
    fprintf(file, "%d", score);
    fclose(file);
  }
}

GameInfo_t *create_next_figure(GameInfo_t *tetr, int blocks[7][3][3]) {
  // srand(7);
  // srand(time(NULL));
  int fnum = rand() % 7;
  // printf("\n");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      tetr->next[i][j] = blocks[fnum][i][j]; //////////????????????????
    }
  }
  return tetr;
}

GameInfo_t *create_game(GameInfo_t *tetr, int blocks[7][3][3]) { //
  tetr->level = 0;
  tetr->lines = 0;
  tetr->score = 0;
  tetr->max_score = getScore();
  tetr->action = Pause;
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      tetr->field[i][j] = 0;
    }
  }
  create_next_figure(tetr, blocks);
  tetr->speed = 999999973;
  return tetr;
} //
  ///
void get_info_from_user(GameInfo_t *tetr) {
  if (tetr->action != Pause) {
    int ch = getch();

    switch (ch) {
    case 'e':
      tetr->action = Action;
      break;
    case 'a':
      tetr->action = Left;
      break;
    case 'd':
      tetr->action = Right;
      break;
    case 's':
      tetr->action = Down;
      break;
    case ' ':
      if (tetr->action == Start)
        tetr->action = Pause;
      else
        tetr->action = Start;
      break;
    case 'q':
      tetr->action = Terminate;
      break;
    default:
      tetr->action = Start;
      break;
    }
  } else {
    int ch = getch();
    switch (ch) {
    case ' ':
      tetr->action = Start;
      break;
    }
  }
}

int line_is_full(GameInfo_t *tetr, int i) {
  int res = 1;
  for (int j = 0; j < 10; j++) {
    if (tetr->field[i][j] == 0)
      res = 0;
  }
  return res;
}

void delete_line(GameInfo_t *tetr, int n) {
  for (int i = n; i > 0; i--) {
    for (int j = 0; j < 10; j++) {
      tetr->field[i][j] = tetr->field[i - 1][j];
    }
  }
  for (int j = 0; j < 10; j++) {
    tetr->field[0][j] = 0;
  }
}

int collision_right(
    Current figure) { ////нужно добавить столкновение с фигурой!!!!!!!!!!!!!!!
  int res = 0;
  int figure_length = 0;
  for (int i = 0; i < 3; i++) { // Определение длины фигуры
    int k = 0;
    for (int j = 0; j < 3; j++) {
      if (figure.shape[j][i] == 1) {
        k = 1;
      }
    }
    if (k == 1) {
      figure_length++;
    }
  }
  if (figure.position[0] == (10 - figure_length)) ///////////!!!!!!!!!!!!!!
    res = 1;
  return res;
}

int is_collision(GameInfo_t *tetr, Current figure) {
  int res = 0;
  int figure_height = 0;

  for (int i = 0; i < 3; i++) { // Определение высоты фигуры
    int k = 0;
    for (int j = 0; j < 3; j++) {
      if (figure.shape[i][j] == 1) {
        k = 1;
      }
    }
    if (k == 1) {
      figure_height++;
    }
  }
  for (int i = 2; i >= 0; i--) { // Проверка столкновения с другими фигурами
    for (int j = 0; j < 3; j++) {
      if ((figure.shape[i][j] == 1) &&
          tetr->field[i + figure.position[1] + 1][j + figure.position[0]] ==
              1) {
        res = 1; // Столкновение с другой фигурой на поле
      }
    }
  }
  if (figure.position[1] == (20 - figure_height))
    res = 1; // Столкновение с нижней границей поля
  return res;
}

void update_score(GameInfo_t *tetr) {
  switch (tetr->lines) {
  case 1:
    tetr->score = 100;
    break;
  case 2:
    tetr->score = 300;
    break;
  case 3:
    tetr->score = 700;
    break;
  case 4:
    tetr->score = 1500;
    break;
  case 5:
    tetr->score = 3100;
    break;
  case 6:
    tetr->score = 6300;
    break;
  case 7:
    tetr->score = 12700;
    break;
  case 8:
    tetr->score = 25500;
    break;
  }
  tetr->level = floor(tetr->score / 600);
  switch (tetr->level) {
  case 1:
    tetr->speed = 999999973;
    break;
  case 2:
    tetr->speed = 99999997;
    break;
  case 3:
    tetr->speed = 99999981;
    break;
  case 4:
    tetr->speed = 99999910;
    break;
  case 5:
    tetr->speed = 9999950;
    break;
  case 6:
    tetr->speed = 999967;
    break;
  case 7:
    tetr->speed = 99990;
    break;
  case 8:
    tetr->speed = 99990;
    break;
  case 9:
    tetr->speed = 99990;
    break;
  case 10:
    tetr->speed = 99990;
    break;

  default:
    break;
  }
  if (tetr->max_score < tetr->score) {
    tetr->max_score = tetr->score;
    setScore(tetr->score);
  }
}

void update_lines(GameInfo_t *tetr) {
  for (int i = 0; i < 20; i++) {
    if (line_is_full(tetr, i)) {
      delete_line(tetr, i);
      tetr->lines++;
      update_score(tetr);
    }
  }
}

int move_down(GameInfo_t *tetr, Current *figure) {
  if (!is_collision(tetr, *figure)) {
    figure->position[1]++;
    return 1;
  } else
    return 0;
}

int move_left(Current *figure) {
  if (figure->position[0] > 0) {
    figure->position[0]--;
    return 1;
  } else
    return 0;
}

int move_right(Current *figure) {
  if (!collision_right(*figure)) {
    figure->position[0]++;
    return 1;
  } else
    return 0;
}

void move_down_to_the_end(GameInfo_t *tetr, Current *figure) {
  while (!is_collision(tetr, *figure)) {
    figure->position[1]++;
  }
}

Current *transpose(Current *figure) {
  Current *figure1 = (Current *)malloc(sizeof(Current));
  int new_shape[3][3];

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      new_shape[j][i] = figure->shape[i][j];
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      figure1->shape[i][j] = new_shape[i][j];
    }
  }

  figure1->position[0] = figure->position[0];
  figure1->position[1] = figure->position[1];

  return figure1;
  free(figure1);
}

Current *invert(Current *figure) {
  Current *figure1 = (Current *)malloc(sizeof(Current));
  int new_shape[3][3];
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      new_shape[i][j] = figure->shape[2 - i][j];
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      figure1->shape[i][j] = new_shape[i][j];
    }
  }
  figure1->position[0] = figure->position[0];
  figure1->position[1] = figure->position[1];
  return figure1;
  free(figure1);
}

Current *root(Current *figure) {
  if (figure->count_of_turn % 2 == 0)
    figure = transpose(figure);
  else {
    figure = transpose(figure);
    figure = invert(figure);
  }
  figure->count_of_turn++;
  return figure;
}

Current *calculete(GameInfo_t *tetr, Current *figure) {
  if ((tetr->action != Pause) && (tetr->action != Terminate)) {
    move_down(tetr, figure); // сдвич вниз
    switch (tetr->action) {
    case Left:
      move_left(figure);
      break;
    case Right:
      move_right(figure);
      break;
    case Action:
      figure = root(figure);
      break;
    case Down:
      move_down_to_the_end(tetr, figure);
      break;
    case Start:
    default:
      break;
    } // сдвиг в зависимости от клика
  } else if (tetr->action == Pause) {
    int ch = getch();
    switch (ch) {
    case ' ':
      tetr->action = Pause;
      break;
    }
  } // если пауза
  return figure;
}

GameInfo_t *update_field(GameInfo_t *tetr, Current figure) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (figure.shape[i][j] == 1) {
        tetr->field[i + figure.position[1]][j + figure.position[0]] = 1;
      }
    }
  }
  return tetr;
}

int lines_is_full(Current figure) {
  if (figure.position[1] == 0)
    return 1;
  else
    return 0;
}

Current *create_figure(Current *figure) {
  figure->position[0] = 3;
  figure->position[1] = 0;
  figure->count_of_turn = 0;

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      figure->shape[i][j] = 0;
    }
  }
  return figure;
}

GameInfo_t *updateCurrentState(GameInfo_t *tetr, Current *figure,
                               int blocks[7][3][3]) {
  if (is_collision(tetr, *figure)) {
    if (!lines_is_full(*figure)) {
      tetr =
          update_field(tetr, *figure); // тут перетащить фигуру в поле, некс
                                       // фигура в текущую, новая некст фигура
      figure = create_figure(figure);
      for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
          figure->shape[i][j] = tetr->next[i][j];
        }
      }
      figure->position[0] = 3;
      figure->position[1] = 0;
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          tetr->next[i][j] = 0;
        }
      }
      create_next_figure(tetr, blocks);
      update_lines(tetr);
    } else
      tetr->action = Terminate;
  }
  return tetr;
}
