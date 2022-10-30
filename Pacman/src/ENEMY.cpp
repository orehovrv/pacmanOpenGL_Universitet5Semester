#include "ENEMY.h"

ENEMY::ENEMY() {
    type = 1;
}

void ENEMY::set_type(bool value) { //получение типа
    type = value;
}

bool ENEMY::get_type() { //установка типа
    return type;
}

