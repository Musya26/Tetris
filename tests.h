#define Start 1
#define Pause 2
#define Terminate 3
#define Left 4
#define Right 5
#define Up 6
#define Down 7
#define Action 8
#define NOP 9

typedef struct{
int position[2];
int shape[3][3];
int count_of_turn; 
int length;
int high;
}Current;

typedef struct {
    int field[20][10];
    int next[3][3];
    int score;
    int max_score;
    int level;
    int lines;                      
    int speed;
    int action;
    int pause;
} GameInfo_t;
