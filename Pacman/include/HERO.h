#ifndef HERO_H
#define HERO_H

#include "ENTITY.h"

class HERO : public ENTITY {
    private:
        unsigned int score, count_money, boost; //количество очков, количество монет и оставшееся время “поедания” привидений
        char mouth;                             //позиция рта

    public:
        HERO();
        char get_mouth();             //получение позиция рта
        void set_mouth(char);         //установка новой позиции
        unsigned int get_count();     //получения количества монет
        unsigned int get_score();     //получения количества очков
        void set_score(unsigned int); //установка количества очков
        void incMon();                //увеличение количества монет
        unsigned int get_boost();     //получения времени “буста”
        void set_boost(unsigned int); //установка времени “буста”
};

#endif // HERO_H

