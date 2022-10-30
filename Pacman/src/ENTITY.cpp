#include <stdlib.h>
#include <stdio.h>

#include "ENTITY.h"

ENTITY::ENTITY() { //конструктор класса
    point.y = point.x = 0;
    speed = 1;
    dir = 0;
}

DOT  ENTITY::get_point() { //получение координат
    return point;
}

void ENTITY::rand_pos(MAZE& level) { //генерация новых координат на основе лабиринта
    char temp, i, j;
    DOT size = level.get_size();

    while((temp = level.check_value(i = rand() % (int)size.x, j = rand() % (int)size.y)) != 1);

    point.x = j * scale + 12;
    point.y = i * scale + 12;
}

char ENTITY::get_dir() { //получение направления
    return dir;
}

void ENTITY::motion(MAZE& level) { //метод для автоматического движения
    if(!level.check_wall(point, dir));
        switch(dir){
            case 0: point.y -= speed; break;
            case 1: point.x += speed; break;
            case 2: point.y += speed; break;
            case 3: point.x -= speed; break;
        }
}

void ENTITY::new_dir(DOT pacman, MAZE& level) { //генерация нового направления
    char prev = dir;

         if(point.y > pacman.y && !level.check_wall(point, 0) && dir != 2) dir = 0;
    else if(point.x < pacman.x && !level.check_wall(point, 1) && dir != 3) dir = 1;
    else if(point.y < pacman.y && !level.check_wall(point, 2) && dir != 0) dir = 2;
    else if(point.x > pacman.x && !level.check_wall(point, 3) && dir != 1) dir = 3;
    else while(level.check_wall(point, dir = rand() % 4) || (prev + 2) % 4 == dir);
}

bool ENTITY::center() { //проверка находится ли объект в центре клетки лабиринта
    return (int)(point.x + 13) % 25 == 0 && (int)(point.y + 13) % 25 == 0;
}

void ENTITY::set_dir(char temp) { //установка нового направления
    dir = temp;
}

void ENTITY::set_speed(double value) { //установка новой скорости
    speed = value;
}

double ENTITY::get_speed() { //получение скорости
    return speed;
}

void ENTITY::set_point(DOT temp) { //установка новых координат
    point = temp;
}
