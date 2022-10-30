#ifndef MAZE_H
#define MAZE_H

#include "DOT.h"
#define scale 25

class MAZE {
    private:
        char **mass = 0;    //указатель на массив где хранится массив
        unsigned char h, w; //высота и ширина лабиринта
        unsigned int count; //количество монет в лабиринте
        DOT pos[5];         //начальные позиции для пакмена и привидений

    public:
        MAZE();
        ~MAZE();
        bool create(char*); //создание лабиринта на основе данных из файла
        DOT  get_size();    //получение размеров лабиринта

        bool check_wall(DOT, char);                            //проверка есть ли стена для объекта с координатами DOT в направлении char
        char check_value(unsigned char, unsigned char);        //проверка значения массива с индексом unsigned char и unsigned char
        void change_value(unsigned char, unsigned char, char); //замена значения массива с индексом unsigned char и unsigned char на char
        char count_napr(DOT);     //проверка в скольких новых направлениях может двигаться объект с координатами DOT
        unsigned int get_count(); //метод возвращает максимальное количество монет в лабиринте
        void gen_berry();         //метод генерирует в случайном месте ягодку
        DOT  get_pos(char);       //метод возвращает одну из изначальных позиций
};

#endif // MAZE_H
