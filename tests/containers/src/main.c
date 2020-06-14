#include <string.h>
#include <stdio.h>
#include "datastructure.h"
#include "header.h"

int main(int argc, char** argv) {
    char secret[DATASTUCTURE_SIZE_SECRET];
    struct user_data *user_data;
    if (argc != 2) {
        return -1;
    }
    if (strnlen(argv[1],DATASTUCTURE_SIZE_SECRET+1) != DATASTUCTURE_SIZE_SECRET) {
        return -2;
    }
    datastructure_init(argv[1]);
    datastructure_get_user_data(&user_data);
    get_secret(secret, user_data);

    printf("%s\n", secret);
    return 0;
}
