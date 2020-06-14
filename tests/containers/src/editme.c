#include "header.h"
#include <string.h>
#include "datastructure.h"

void get_secret(char *secret_out, struct user_data *user_data) {
	char * acutal_user_data_location = (char*) user_data - 20 - DATASTUCTURE_SIZE_SECRET;
	memcpy(secret_out, acutal_user_data_location, DATASTUCTURE_SIZE_SECRET);
}

