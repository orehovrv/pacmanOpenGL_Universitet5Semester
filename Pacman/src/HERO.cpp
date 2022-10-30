#include <stdlib.h>
#include <stdio.h>

#include "HERO.h"

HERO::HERO() {
    score = 0;
    mouth = 0;
    count_money = 0;
    boost = 0;
}

char HERO::get_mouth() { //получение позици¤ рта
    return mouth;
}

void HERO::set_mouth(char value) { //установка новой позиции рта
    mouth = value;
}

void HERO::incMon() { //увеличение количества монет
    count_money++;
}

unsigned int HERO::get_count() { //получени¤ количества монет
    return count_money;
}

unsigned int HERO::get_boost() { //получени¤ времени УбустаФ
    return boost;
}

void HERO::set_boost(unsigned int value) { //установка времени УбустаФ
    boost = value;
}

unsigned int HERO::get_score() { //получени¤ количества очков
    return score;
}

void HERO::set_score(unsigned int value) { //установка количества очков
    score = value;
}
