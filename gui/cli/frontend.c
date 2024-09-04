#include "frontend.h"

void print_field(GameInfo_t tetr,
                 Current figure) { /// вот тут вважно чтоб поле не было
                                   /// указателем!!!!!!!!!!!!!!
  int sym;
  int new_field[20][10] = {0};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (figure.shape[i][j] == 1) {
        new_field[i + figure.position[1]][j + figure.position[0]] = 1;
      }
    }
  }
  for (int i = 0; i < 20; i++) {   // y
    for (int j = 0; j < 10; j++) { // x
      sym = tetr.field[i][j] || new_field[i][j];
      if (sym == 1) {
        sym = 2;
      } else
        sym = 1;
      attron(COLOR_PAIR(sym));
      mvaddch(i, j, ' ');
      attroff(COLOR_PAIR(sym));
    }
  }
  mvprintw(2, 26, "Score: %d", tetr.score);
  mvprintw(4, 26, "Max score: %d", tetr.max_score);
  mvprintw(6, 26, "Level:%d", tetr.level);
  mvprintw(8, 26, "Next figure: ");
  for (int i = 0; i < 3; i++) { /// обрисовка следующей фигуры
    for (int j = 0; j < 3; j++) {
      sym = tetr.next[i][j];
      if (sym == 1) {
        // sym=2;
        attron(COLOR_PAIR(2));
        mvaddch(10 + i, 26 + j, ' ');
        attroff(COLOR_PAIR(2));
      } else {
        attron(COLOR_PAIR(3));
        mvaddch(10 + i, 26 + j, ' ');
        attroff(COLOR_PAIR(3));
      }
    }
  }
}

int main() {
  struct timespec sp_start, sp_end, ts1, ts2 = {0, 0}; // для времени
  initscr();
  start_color();
  init_pair(1, COLOR_BLUE, COLOR_MAGENTA);
  init_pair(2, COLOR_GREEN, COLOR_GREEN);
  init_pair(3, COLOR_BLACK, COLOR_BLACK);
  cbreak();

  noecho(); // отключает вывод символа

  nodelay(stdscr, TRUE); // отключает задержку при вызове функции гетч
  scrollok(stdscr, TRUE); // отключает возможность скроллинга

  GameInfo_t *tetr = (GameInfo_t *)malloc(sizeof(GameInfo_t));
  int blocks[7][3][3] = {
      {{1, 1, 0}, {0, 1, 0}, {0, 1, 1}},

      {{1, 1, 1}, {0, 0, 0}, {0, 0, 0}},
      {{0, 1, 0}, {1, 1, 1}, {0, 0, 0}}, // треугольник
      {{0, 1, 1}, {0, 1, 0}, {1, 1, 0}}, // z//z
      {{1, 1, 0}, {0, 1, 0}, {0, 1, 0}}, // г
      {{1, 1, 0}, {1, 0, 0}, {1, 0, 0}}, // г
      {{1, 1, 0}, {1, 1, 0}, {0, 0, 0}}  // квардрат
  };
  srand(time(NULL));
  create_game(tetr, blocks);
  Current *figure = (Current *)malloc(sizeof(Current));
  figure = create_figure(figure);
  print_field(*tetr, *figure);    // обрисовка интерфейса
  while (tetr->action != Start) { ///////тут ожидание старта
    get_info_from_user(tetr);
  }
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      figure->shape[i][j] = tetr->next[i][j];
    }
  }
  figure->position[0] = 3;
  figure->position[1] = 0;
  figure->count_of_turn = 0;

  while (tetr->action != Terminate) {
    clock_gettime(CLOCK_MONOTONIC, &sp_start);
    get_info_from_user(tetr); // получение инфы от пользователя
    print_field(*tetr, *figure);
    figure = calculete(tetr, figure); // обновление текущего состояния
    tetr = updateCurrentState(
        tetr, figure,
        blocks); // есть ли столкновение(!)проерка на закрытые линии(если да, то
                 // добавить новую фигуру , старую фигуру пребразовать в поле),
                 // обновление уровней и баллов
    refresh();
    clock_gettime(CLOCK_MONOTONIC, &sp_end);
    if (sp_end.tv_sec - sp_start.tv_sec <= 0 &&
        (ts2.tv_nsec = tetr->speed - (sp_end.tv_nsec - sp_start.tv_nsec)) > 0)
      nanosleep(&ts2, &ts1);
  }
  free(tetr);
  free(figure);
  endwin();
  return 0;
}
