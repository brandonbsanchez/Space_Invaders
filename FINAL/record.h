// -----------------------------------------------------------------------------
// This header file holds a structure that is used for the high score file.
// -----------------------------------------------------------------------------
#include "header.h"

const int NAME_SIZE = 11;   // maximum size hi-score name can be (-1 for '/0')

struct Record{
    char name[NAME_SIZE];
    int score;
};
