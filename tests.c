#include <check.h>    
#include <curses.h>   
#include <stdlib.h>   
#include <stdio.h>    //проверка на коллизион
#include "tests.h"  //проверка на движения 


GameInfo_t* create_g (GameInfo_t* tetr){//
    tetr->level=0;
    tetr->lines=0;
    tetr->score=0;
    // tetr->max_score=getScore();
    tetr->action=Pause;
    for(int i=0; i<20; i++){
        for(int j=0; j<10; j++){
            tetr->field[i][j]=0;
        }
    }
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
    case KEY_ENTER:
      return Start;
    case Terminate:
      return Terminate;
      return Pause;
    default:
      return NOP;
  }
}

void delete_line(GameInfo_t *tetr, int n){
    for(int i=n; i>0; i--){
        for(int j=0; j<10; j++){
        tetr->field[i][j]=tetr->field[i-1][j];
        }
    }
    for(int j=0; j<10; j++){
    tetr->field[0][j]=0;}
}

void update_score(GameInfo_t *tetr){
 switch (tetr->lines)
        {
        case 1:
            tetr->score =100; 
            break;
        case 2:
            tetr->score =300; 
            break;
        case 3:
            tetr->score =700; 
            break;
        case 4:
            tetr->score =1500; 
            break;    
        case 5:
            tetr->score =3100; 
            break;             
        case 6:
            tetr->score =6300; 
            break;             
        case 7:
            tetr->score =12700; 
            break;             
        case 8:
            tetr->score =25500; 
            break;                              /////вот тут добавить еще!!!!!!!!!!!!
        // default:
        //     break;
        }   

}

START_TEST(test_update_score) {//тест на повышение уровня
  GameInfo_t *tetr = calloc(1, sizeof(GameInfo_t));
create_g(tetr);
tetr->lines++;
update_score(tetr);
ck_assert_int_eq(tetr->score ,100);
tetr->lines++;
update_score(tetr);
ck_assert_int_eq(tetr->score ,300);
tetr->lines++;
update_score(tetr);
ck_assert_int_eq(tetr->score ,700);
tetr->lines++;
update_score(tetr);
ck_assert_int_eq(tetr->score ,1500);
tetr->lines++;
update_score(tetr);
ck_assert_int_eq(tetr->score ,3100);
tetr->lines++;
update_score(tetr);
ck_assert_int_eq(tetr->score ,6300);
tetr->lines++;
update_score(tetr);
ck_assert_int_eq(tetr->score ,12700);
// }
free(tetr);
}
END_TEST


START_TEST(test_signal_delete) {//тест на удаление строк
  GameInfo_t *tetr = calloc(1, sizeof(GameInfo_t));
create_g(tetr);
for(int i=0; i<10;i++){
  tetr->field[19][i]=1;//заполнение одной строки
}
delete_line(tetr,19);
for(int i=0; i<10;i++){
  ck_assert_int_eq(tetr->field[19][i],0 );//заполнение одной строки
}
free(tetr);
}
END_TEST

START_TEST(test_signalAction_pause) {//тест на сигнал паузы  проходит
  GameInfo_t *tetr = calloc(1, sizeof(GameInfo_t));
   tetr->action = Start;

  create_g(tetr);
  ck_assert_int_eq(tetr->action, Pause);
free(tetr);
}
END_TEST

START_TEST(test_signalAction_Start) {//тест на сигнал паузы  проходит
  GameInfo_t *tetr = calloc(1, sizeof(GameInfo_t));
  create_g(tetr);
   tetr->action = Start;

  // create_g(tetr);
  ck_assert_int_eq(tetr->action, Start);
free(tetr);
}
END_TEST

START_TEST(test_signalAction_action) {//тест на сигнал паузы  проходит
  GameInfo_t *tetr = calloc(1, sizeof(GameInfo_t));
  create_g(tetr);
   tetr->action = Action;

  // create_g(tetr);
  ck_assert_int_eq(tetr->action, Action);
free(tetr);
}
END_TEST



START_TEST(test_getUserAction1) {
   GameInfo_t *tetr = calloc(1, sizeof(GameInfo_t));
  tetr->action = getUserAction(NOP);
  ck_assert_int_eq(tetr->action, NOP);
  free(tetr);
}
END_TEST

START_TEST(test_getUserAction2){
 GameInfo_t *tetr = calloc(1, sizeof(GameInfo_t));
  tetr->action = getUserAction(KEY_LEFT);
  ck_assert_int_eq(tetr->action, Left);
free(tetr);
}
END_TEST

START_TEST(test_getUserAction3){
 GameInfo_t *tetr = calloc(1, sizeof(GameInfo_t));
   tetr->action = getUserAction(KEY_RIGHT);
  ck_assert_int_eq(tetr->action, Right);
free(tetr);
}
END_TEST

START_TEST(test_getUserAction4){
 GameInfo_t *tetr = calloc(1, sizeof(GameInfo_t));
  tetr->action = getUserAction(KEY_DOWN);
  ck_assert_int_eq(tetr->action, Down);
free(tetr);
}
END_TEST

START_TEST(test_getUserAction5){
 GameInfo_t *tetr = calloc(1, sizeof(GameInfo_t));
  tetr->action= getUserAction(Terminate);
  ck_assert_int_eq(tetr->action, Terminate);
free(tetr);
}
END_TEST

Suite *signalAction_suite(void) {
  Suite *s;
  TCase *tc_core;

  s = suite_create("Fsm");                     

  tc_core = tcase_create("Core");      

  // Добавление тестов в core тест-кейс
  tcase_add_test(tc_core, test_signalAction_pause);
  tcase_add_test(tc_core, test_signalAction_action);
  tcase_add_test(tc_core, test_signalAction_Start);
  tcase_add_test(tc_core, test_signal_delete);
   tcase_add_test(tc_core, test_update_score);
  tcase_add_test(tc_core, test_getUserAction1);
  tcase_add_test(tc_core, test_getUserAction2);
  tcase_add_test(tc_core, test_getUserAction3);
  tcase_add_test(tc_core, test_getUserAction4);
  tcase_add_test(tc_core, test_getUserAction5);

  // Добавление других тестов...

  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = signalAction_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
