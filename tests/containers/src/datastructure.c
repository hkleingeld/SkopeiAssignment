#include <string.h>
#include "datastructure.h"

static struct container hidden;

void datastructure_get_user_data(struct user_data **user_data) {
    *user_data = &hidden.user_data;
}    

void datastructure_init(char *init_data) {
    if (strnlen(init_data,DATASTUCTURE_SIZE_SECRET+1) != DATASTUCTURE_SIZE_SECRET) {
        return;
    }
    memcpy(hidden.get_me, init_data, DATASTUCTURE_SIZE_SECRET);
}
