#include "hashmap.h"

int hash(HashMap * hm, char * key) {
	int sum = 0;
	int len = strlen(key) + 1;

	for (int i = 0; i < len; i++) {
		sum = sum + key[i];
	}

	return sum % hm->size;
}

HashMap * create_hashmap(size_t key_size) {
	assert(key_size > 0);

	HashMap * hm = (HashMap *) malloc(sizeof(HashMap));
	assert(hm);

	hm->buckets = calloc(key_size, sizeof(Bucket));
	assert(hm->buckets);

	hm->size  = key_size; 

	return hm;
}

static Bucket* make_bucket(char * key, void * data){
	Bucket * new_bucket = malloc(sizeof(Bucket));
	assert(new_bucket);

	new_bucket->data = malloc(strlen(data)+1);
	assert(new_bucket->data);
	strcpy(new_bucket->data, data);

	new_bucket->key = malloc(strlen(key)+1);
	assert(new_bucket->key);
	strcpy(new_bucket->key, key);

	new_bucket->next = NULL;

	return new_bucket;
}

static void delete_bucket(Bucket * b){
	free(b->data);
	free(b->key);

	b->data = NULL;
	b->key = NULL;
	b->next = NULL;

	free(b);
}

void insert_data(HashMap * hm, char * key, void * data, ResolveCollisionCallback resolve_collision) {
	int hm_index = hash(hm, key);
	Bucket * b = hm->buckets[hm_index];
	Bucket * b_prev = NULL;

	//Bucket does not exist yet, thus we make a new bucket and put it in the pointer array
	if(b == NULL){
		hm->buckets[hm_index] = make_bucket(key,data);
		return;
	}

	//Bucket does exist, check if key is already in our linked list
	while(b != NULL){
		if(strcmp(key, b->key) == 0){
			void* data_to_keep = resolve_collision(b->data,data);
			if(data_to_keep == b->data){
				//No data adjustment, we are done here.
				return;
			}
			else{
				free(b->data);
				b->data = malloc(strlen(data_to_keep)+1);
				assert(b->data);
				strcpy(b->data, data_to_keep);
				//data adjusted, we are done.
				return;
			}
		}

		b_prev = b;
		b = b->next;
	}

	//Key not found, append in linked list.
	b_prev->next = make_bucket(key,data);
}

void * get_data(HashMap * hm, char * key) {
	int hm_index = hash(hm, key);
	Bucket * b = hm->buckets[hm_index];

	while(b != NULL){
		if(strcmp(key, b->key) == 0){
			return b->data;
		}
		b = b->next;
	}

	return NULL;
}

void iterate(HashMap * hm, void (* callback)(char * key, void * data)) {
	for(size_t i = 0; i < hm->size ; i++){
		Bucket * b = hm->buckets[i];

		while(b!=NULL){
			callback(b->key, b->data);
			b = b->next;
		}
	}
}

void remove_data(HashMap * hm, char * key, DestroyDataCallback destroy_data) {
	int hm_index = hash(hm, key);
	Bucket * b = hm->buckets[hm_index];
	Bucket * prev_bucket = NULL;

	while(b != NULL){
		if(strcmp(key, b->key) == 0){
			if(destroy_data!= NULL) destroy_data(b->data);

			if(prev_bucket != NULL){ // there is an item left in the linked list
				prev_bucket->next = b->next;
			}

			if(prev_bucket == NULL){ // no items left in the linked list
				hm->buckets[hm_index] = NULL;
			}

			delete_bucket(b);
			return;
		}
		prev_bucket = b;
		b = b->next;
	}
}

void delete_hashmap(HashMap * hm, DestroyDataCallback destroy_data) {
	for(size_t i = 0; i < hm->size ; i++){
		Bucket * b = hm->buckets[i];
		if(b == NULL){
			continue; // Bucket does not exist, nothing to delete
		}

		Bucket * next_bucket = b->next;

		while(b!=NULL){
			if(destroy_data!= NULL) destroy_data(b->data);
			delete_bucket(b);

			if(next_bucket == NULL){
				break; // no buckets are left in the linked list, time for the next linked list.
			}
			b = next_bucket;
			next_bucket = b->next;
		}
	}
	free(hm->buckets);
	free(hm);
}
