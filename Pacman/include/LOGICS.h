#ifndef LOGICS_H
#define LOGICS_H

#include <time.h>

#include "MAZE.h"
#include "HERO.h"
#include "ENEMY.h"

class LOGICS {
    public:
        MAZE maze;          //лабиринт
        HERO pacman;        //пакмен
        ENEMY enemy[4];     //4 призрака
        char regim;         //режим игры (идет/закончилась)
        unsigned int frame; //счетчик кадров с начала игры

        bool gen (char*);  //задание начальных значений дл¤ всего
        void step();       //один шаг логики (сдвиг пакмена и привидений, возможна¤ генераци¤ ¤годы)
        void eat();        //поедание монет и ¤год
        void die_pacman(); //поедание привидени¤ми пакмена или наоборот
};

#endif // LOGICS_H
