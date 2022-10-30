#ifndef ENEMY_H
#define ENEMY_H

#include "ENTITY.h"

class ENEMY : public ENTITY{
    private:
        bool type; //переменная для определения убивает пакмена/умирает от пакмена

    public:
        ENEMY();
        bool get_type();     //получение типа
        void set_type(bool); //установка типа
};

#endif // ENEMY_H
