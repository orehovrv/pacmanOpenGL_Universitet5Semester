#include <stdlib.h>
#include <stdio.h>

#include "MAZE.h"

MAZE::MAZE() { //конструктор класса
    mass = NULL;
    h = w = 0;
}

MAZE::~MAZE() { //декструктор класса
    if(mass) {
        for(int i = 0; i < h; i++)
            if(mass[i]) free(mass[i]);
        free(mass);
    }
}

bool MAZE::create(char *way) { //создание лабиринта на основе данных из файла
    FILE *file;
    if((file = fopen(way, "rb")) == NULL) //открытие файла
        return 0;

    unsigned char i, j;

    fread(&h, 1, 1, file); //считывание размеров лабиринта и количества монет
    fread(&w, 1, 1, file);
    fread(&count, 1, 4, file);

    mass = (char**)malloc(h * sizeof(char*)); //выделение памяти под матрицу
    for(i = 0; i < h; i++)
        mass[i] = (char*)calloc(w, sizeof(char));

    for(i = 0; i < h; i++) //считывание лабиринта
        for(j = 0; j < w; j++)
            fread(&mass[i][j], 1, 1, file);

    for(i = 0; i < 5; i++) //считывание позиций
        fread(&pos[i], 1, 16, file);

    return 1;
}

char MAZE::check_value(unsigned char i, unsigned char j) { //возврат значение лабиринта
    return mass[i][j];
}

void MAZE::change_value(unsigned char i, unsigned char j, char value) { //замена значение лабиринта
    mass[i][j] = value;
}

DOT MAZE::get_size() { //возврат размеров лабиринта
    DOT size;
    size.x = h;
    size.y = w;
    return size;
}

char MAZE::count_napr(DOT point) { //проверка в скольких новых направлениях может двигаться объект с координатами point
    char count = 0;
    for(char i = 0; i < 4; i++)
        if(!check_wall(point, i))
            count++;
    return count;
}

bool MAZE::check_wall(DOT point, char dir) { //проверка есть ли стена для объекта с координатами point в направлении dir
    int i, j;
    i = point.x / 25;
    j = point.y / 25;

    switch(dir){
        case 0: if(mass[j-1][i] != 0) return 0; break;
        case 1: if(mass[j][i+1] != 0) return 0; break;
        case 2: if(mass[j+1][i] != 0) return 0; break;
        case 3: if(mass[j][i-1] != 0) return 0; break;
    }
    return 1;
}

unsigned int MAZE::get_count() { //метод возвращает максимальное количество монет в лабиринте
    return count;
}

void MAZE::gen_berry() { //метод генерирует в случайном месте ягодку
    char i, j, temp;
    while((temp = mass[i = rand() % h][j = rand() % w]) != 3);
    mass[i][j] = 4;
}

DOT MAZE::get_pos(char i) { //метод возвращает одну из изначальных позиций
    return pos[i];
}
