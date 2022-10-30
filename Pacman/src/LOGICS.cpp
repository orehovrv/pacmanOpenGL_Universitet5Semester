#include "LOGICS.h"

#include <stdlib.h>
#include <stdio.h>

DOT pos[5];

bool LOGICS::gen(char *way) { //задание начальных значений дл¤ всего
    srand(time(NULL));
    if(!maze.create(way)) //создание лабиринта
        return 0;

    for(char i = 0; i < 5; i++) { //считывание позиций
        pos[i].x = maze.get_pos(i).x * 25 + 12;
        pos[i].y = maze.get_pos(i).y * 25 + 12;
    }

    pacman.rand_pos(maze); //рандомна¤ установка позиции пакмена
    pacman.new_dir(pacman.get_point(), maze); //генераци¤ направлени¤
    pacman.set_score(0); //обнуление переменных
    pacman.set_boost(0);

    for(char i=0; i<4; i++) { //установка позиций привидений
        enemy[i].set_point(pos[i]);
        enemy[i].set_type(1);
        enemy[i].set_speed(1);
    }

    regim = 1;
    frame = 0;
    return 1;
}

void LOGICS::step() { //один шаг логики (сдвиг пакмена и привидений, возможна¤ генераци¤ ¤годы)
    char i;
    pacman.set_mouth(abs((int)pacman.get_point().x % 25 - 12) + abs((int)pacman.get_point().y % 25 - 12)); //установка позоции рта

    if(!maze.check_wall(pacman.get_point(), pacman.get_dir()) || !pacman.center()) //движение пакмена
        pacman.motion(maze);

    for(i = 0; i < 4; i++) { //движение привидений
        if(enemy[i].center()) { //генераци¤ нового направлени¤ движени¤
            if(!(rand() % 3) && maze.count_napr(enemy[i].get_point()) > 2)
                enemy[i].new_dir(pacman.get_point(), maze);
            else if(maze.check_wall(enemy[i].get_point(), enemy[i].get_dir()))
                enemy[i].new_dir(pacman.get_point(), maze);
        }
        enemy[i].motion(maze); //движение привидений
    }
    frame++;
    pacman.set_boost(pacman.get_boost() + 1); //увеличение "буста"

    if(!(frame % 1000) && frame) //генераци¤ ¤годки
        maze.gen_berry();
    if(pacman.get_boost() > 750) { //отмена буста ¤годки
        pacman.set_boost(0);
        for(i = 0; i < 4; i++){
            enemy[i].set_type(1);
            enemy[i].set_speed(1);
        }
    }

    if(pacman.get_boost() > 600 && !(pacman.get_boost() % 30)) //"мигание" привидений под конец "буста"
        for(i = 0; i<4; i++)
            if(enemy[i].get_speed() < 0.8)
                enemy[i].set_type(!enemy[i].get_type());
}

void LOGICS::eat() { //поедание монет и ¤год
    if(pacman.center() && maze.check_value(pacman.get_point().y / 25, pacman.get_point().x / 25) == 1) { //поедание ¤годки
        maze.change_value(pacman.get_point().y / 25, pacman.get_point().x / 25, 3);
        pacman.incMon();
        pacman.set_score(pacman.get_score() + 100);
    }

    if(pacman.center() && maze.check_value(pacman.get_point().y / 25, pacman.get_point().x / 25) == 4) { //поедание ¤годки
        maze.change_value(pacman.get_point().y / 25, pacman.get_point().x / 25, 3);
        for(char i = 0; i < 4; i++){
            enemy[i].set_type(0);
            enemy[i].set_speed(0.5);
            pacman.set_boost(0);
            pacman.set_score(pacman.get_score() + 200);
        }
    }

    if(pacman.get_count() >= maze.get_count()) //конец игры если пакмен съест все монетки
        regim = 0;
}

void LOGICS::die_pacman() { //поедание привидени¤ми пакмена или наоборот
    unsigned int px, py, ex, ey;
    px = (int)pacman.get_point().x;
    py = (int)pacman.get_point().y;
    for(char k = 0; k < 4; k++) {
        ex = (int)enemy[k].get_point().x;
        ey = (int)enemy[k].get_point().y;
        if(enemy[k].get_type()) {
            if((ex-10 <= px && ex+10 >= px && ey == py) || (ey-10 <= py && ey+10 >= py && ex == px)) //смерть пакмена
                regim = 0;
        } else {
            if((ex-10 <= px && ex+10 >= px && ey == py) || (ey-10 <= py && ey+10 >= py && ex == px)) { //поедение привидений пакменом
                pacman.set_score(pacman.get_score() + 300);
                enemy[k].set_point(pos[k]);
                enemy[k].set_type(1);
                enemy[k].set_speed(1);
            }
        }
    }
}
