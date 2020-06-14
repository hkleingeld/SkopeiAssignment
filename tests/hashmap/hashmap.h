#define __HASHMAP_H__
#define MAX_KEY_SIZE = 128;

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
 * Assumption:
 * The hashmap structs are set in stone with the given test sample. This implies:
 * 	--> Data is null terminated (as no data_size is present in the Bucket)
 * 		--> strlen can be used to find the size of this data blob, with a +1 for the NULL termination char
 * 	--> key is null terminated (as no key_size is present in the Bucket)
 *	 	--> strlen can be used to find the size of the key, with a +1 for the NULL termination char
 */

typedef struct Bucket {
	struct Bucket * next;
	char * key;
	void * data;
} Bucket;

typedef struct HashMap {
	Bucket ** buckets;
	size_t size;
} HashMap;  

typedef void * (* ResolveCollisionCallback)(void * old_data, void * new_data);

typedef void (* DestroyDataCallback)(void * data);

extern int hash();
extern HashMap * create_hashmap();
extern void insert_data();
extern void * get_data();
extern void iterate();
extern void remove_data();
extern void delete_hashmap();