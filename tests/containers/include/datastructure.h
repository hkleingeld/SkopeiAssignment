#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include "editme.h"

#define DATASTUCTURE_SIZE_SECRET 10

struct container {
    int number;
    char stuff[38];
    char get_me[DATASTUCTURE_SIZE_SECRET];
    char more_stuff[20];
    struct user_data user_data;
    char even_more_stuff[37];
};

void datastructure_get_user_data(struct user_data **user_data);
void datastructure_init(char *init_data);

#endif /* DATASTRUCTURE_H */
