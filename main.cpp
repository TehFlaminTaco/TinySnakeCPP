#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <ctime>
#include "2dArr.cpp"
#include "worm.cpp"

charmap* MAP;
worm* WORM;
HANDLE terminal;
DWORD dump;
COORD zerodCoord = {0,0};
DIR wormDir = NORTH;
int food_x = 0;
int food_y = 0;
int RUN_SPEED = 100;
int SCORE = 0;

void updateTerminal(){
    SetConsoleCursorPosition(terminal, zerodCoord);
    WriteConsoleA(terminal, MAP -> entry, MAP -> size, &dump, NULL);
    std::cout << "Score: " << SCORE;
}

void updateDraw(){
    MAP -> rectangle(true, ' ', 1, 1, MAP -> width - 2, MAP -> height - 2);
    MAP -> set(food_x, food_y, 'a');
    WORM -> drawWorm();
    switch(wormDir){
        case NORTH: MAP -> set(WORM -> x, WORM -> y, '^'); break;
        case EAST : MAP -> set(WORM -> x, WORM -> y, '>'); break;
        case SOUTH: MAP -> set(WORM -> x, WORM -> y, 'v'); break;
        case WEST : MAP -> set(WORM -> x, WORM -> y, '<'); break;
    }
}
void moveFood(){
    food_x = (rand()%(MAP -> width -2))+1;
    food_y = (rand()%(MAP -> height -2))+1;
}

bool wormOnFood(){
    worm* t = WORM;
    while(t!=NULL){
        if (t -> x == food_x && t -> y == food_y){
            return true;
        }
        t = t -> tail;
    }
    return false;
}

void eatFood(){
    if (WORM -> x == food_x && WORM -> y == food_y){
        WORM -> pushTail();
        SCORE++;
        moveFood();
        while(wormOnFood()){
            moveFood();
        }
    }
}

void rotateWorm(){
    if(GetKeyState(VK_UP) & 0x8000 && wormDir!=SOUTH)
        wormDir = NORTH;
    else if(GetKeyState(VK_RIGHT) & 0x8000 && wormDir!=WEST)
        wormDir = EAST;
    else if(GetKeyState(VK_DOWN) & 0x8000 && wormDir!=NORTH)
        wormDir = SOUTH;
    else if(GetKeyState(VK_LEFT) & 0x8000 && wormDir!=EAST)
        wormDir = WEST;
    
}

bool checkWorm(){
    worm* segment = WORM -> tail;
    while(segment!=NULL){
        if(segment -> x == WORM -> x && segment -> y == WORM -> y){
            return true;
        }
        segment = segment -> tail;
    }
    return false;
}

void sleep(double t, void (*f)()){
    long start = clock();
    while(clock()-start<t){
        f();
    }
}

bool loop(){
    if(GetKeyState(VK_ESCAPE) & 0x8000)
        return false;
    WORM -> moveDir(wormDir);
    if(checkWorm())
        return false;
    eatFood();
    updateDraw();
    updateTerminal();
    sleep(RUN_SPEED, rotateWorm);
    return true;
}

int parseInt(char* str){
    int o = 0;
    for(char *inpStr = str; *inpStr; ++inpStr){
        o *= 10;
        o += (*inpStr)-48;
    }
    return o;
}

int main(int argc, char* argv[]){

    int gameWidth = 20;
    int gameHeight = 20;

    if(argc > 1){
        gameWidth = parseInt(argv[1]);
        gameHeight = gameWidth;
    }
    if(argc > 2){
        gameHeight = parseInt(argv[2]);
    }
    if(argc > 3){
        RUN_SPEED = parseInt(argv[3]);
    }

    system("CLS");
    srand(time(NULL));
    terminal = GetStdHandle(STD_OUTPUT_HANDLE);

    MAP = new charmap(gameWidth, gameHeight, ' ');
    WORM = new worm(5, 5, MAP);
    /*for(int i=0; i < 2; i++){
        WORM -> pushTail();
    }*/
    MAP -> rectangle(false, '#', 0, 0, MAP -> width, MAP -> height);
    moveFood();

    while(loop()){}
    system("CLS");
    return 0;
}