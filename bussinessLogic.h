#ifndef BUSSINESSLOGIC_H
#define BUSSINESSLOGIC_H

#define PLUS 1
#define MINUS 2
#define MULTIPLY 3
#define DIVIDE 4

#define EMPTY 0
#define ERROR 12345e-98

struct action_obj{
    double memory;
    double number;
    int sign;
};

double action_in_calc_memory (action_obj calcObject);

#endif // BUSSINESSLOGIC_H
