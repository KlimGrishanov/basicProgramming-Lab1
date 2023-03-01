#include "bussinessLogic.h"

double action_in_calc_memory (action_obj calcObject) {
    double res = EMPTY;
    if (calcObject.sign == PLUS) {
        res = calcObject.memory + calcObject.number;
    } else if (calcObject.sign == MINUS) {
        res = calcObject.memory - calcObject.number;
    } else if (calcObject.sign == MULTIPLY) {
        res = calcObject.memory * calcObject.number;
    } else if (calcObject.sign == DIVIDE){
        res = calcObject.memory / calcObject.number;
    }
    return res;
}
