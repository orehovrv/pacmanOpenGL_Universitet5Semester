#ifndef ENTITY_H
#define ENTITY_H

#include "DOT.h"
#include "MAZE.h"

class ENTITY {
    private:
        DOT point;    //позиция существа
        char dir;     //направление движения
        double speed; //скорость движения

    public:
        ENTITY();
        char get_dir();           //получение направления
        void set_dir(char);       //установка нового направления
        void new_dir(DOT, MAZE&); //генерация нового направления
        DOT  get_point();         //получения координат
        void set_point(DOT);      //установка новых координат
        void rand_pos(MAZE&);     //генерация новых координат на основе лабиринта
        double get_speed();       //получение скорости
        void   set_speed(double); //установка новой скорости
        void motion(MAZE&);       //метод для автоматического движения
        bool center();            //проверка находится ли объект в центре клетки лабиринта
};

#endif // ENTITY_H
