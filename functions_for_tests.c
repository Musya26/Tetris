#include <curses.h> 

GameInfo_t* create_game (GameInfo_t* tetr, int blocks[7][3][3]){//
    //GameInfo_t* tetr =(GameInfo_t*)malloc(sizeof(GameInfo_t)); ///вот тут добавить !!!!!!!!!!!!!
    tetr->level=0;
    tetr->lines=0;
    tetr->score=0;
    tetr->max_score=getScore();
    tetr->action=Pause;
    for(int i=0; i<20; i++){
        for(int j=0; j<10; j++){
            tetr->field[i][j]=0;
        }
    }
    create_next_figure(tetr, blocks) ;
    tetr->speed=999999973;
    return tetr;
}//

int getUserAction(int userInput) {
  switch (userInput) {
    case KEY_LEFT:
      return Left;
    case KEY_RIGHT:
      return Right;
    case KEY_DOWN:
      return Down;
    case KEY_ENTER://////////?!!!1!!!!!!!!!!!!!!!!
      return Start;
    case Terminate:
      return Terminate;
    // case P_KEY:
    // case WACS_S3	:
      return Pause;
    // case SPACE:
    //   return Action; !!!!!!!!!!!!!!!!!!!!!!!!!
    default:
      return NOP;
  }
}
