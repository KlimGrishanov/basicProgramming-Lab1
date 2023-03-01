#ifndef BUSSINESSLOGIC_H
#define BUSSINESSLOGIC_H

#include "mainwindow.h"

struct action_obj{
    double memory;
    double number;
    int sign;
};

double action_in_calc_memory (action_obj calcObject);

#endif // BUSSINESSLOGIC_H
