#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "hashmap.h"

size_t mystrlen(const char *str) {
    return strlen(str) + 1;
}

void print_element(const char *key, void *data) {
	printf("(\"%s\", %s)\n", key, (char*)data);
}

void *resolve_collision(void *old_value, void *new_value) {
	(void) old_value;
	return new_value;
}

int resolve_collision_called_count = 0;
void *resolve_collision_2(void *old_value, void *new_value) {
	resolve_collision_called_count++;
	(void) new_value;
	return old_value;
}

int delete_callback_called_count = 0;
void delete_callback(void * data){
	(void) data;
	delete_callback_called_count++;
}

int main() {
	unsigned int key_space = 1024;
	HashMap * hm = create_hashmap(key_space);

	char * string_1 = "Jasper";
	char * string_2 = "Jens";
	char * string_3 = "Newby";
	char * string_4 = "Emil";
	const char * key_1    = "Electrical Engineer";
	const char * key_2    = "Software Engineer";
	const char * key_3    = "Embedded Software Engineer";
	const char * key_4    = "Product Owner";
	const char * key_5    = "Gardener";

	// Insert ("Electrical Engineer" -> "Jasper").
	insert_data(hm, key_1, string_1, resolve_collision);
	assert(memcmp(get_data(hm, key_1), string_1, mystrlen(string_1)) == 0);

	// Insert ("Software Engineer" -> "Jens").
	insert_data(hm, key_2, string_2, resolve_collision);
	assert(memcmp(get_data(hm, key_2), string_2, mystrlen(string_2)) == 0);

	// Insert ("Embedded Software Engineer" -> "Jasper").
	insert_data(hm, key_3, string_1, resolve_collision);
	assert(memcmp(get_data(hm, key_3), string_1, mystrlen(string_1)) == 0);

	// Insert ("Product Owner" -> "Emil").
	insert_data(hm, key_4, string_4, resolve_collision);
	assert(memcmp(get_data(hm, key_4), string_4, mystrlen(string_4)) == 0);

	// Insert ("Embedded Software Engineer" -> "Newby").
	insert_data(hm, key_3, string_3, resolve_collision);
	assert(memcmp(get_data(hm, key_3), string_3, mystrlen(string_3)) == 0);

	// Get data for a not inserted key.
	assert(get_data(hm, key_5) == NULL);

	// Iterate the hash map
	iterate(hm, print_element);

	// Delete key "Software Engineer".
	remove_data(hm, key_2, NULL);
	assert(get_data(hm, key_2) == NULL);
	
	// Delete key "Electrical Engineer".
	remove_data(hm, key_1, NULL);
	assert(get_data(hm, key_1) == NULL);

	// Delete key "Embedded Software Engineer".
	remove_data(hm, key_3, NULL);
	assert(get_data(hm, key_3) == NULL);

	// Delete key "Gardener".
	remove_data(hm, key_5, NULL);
	assert(get_data(hm, key_5) == NULL);

	// Delete the hash map.
	delete_hashmap(hm, NULL); 

	printf("Test 1 succeded!\n\n");


	// Test 2, should test the following points.
	// - Can the hashmap work with keys with the same hash
	// - Are the callbacks actually called?
	// - Does the collision callback actually use the returned value?

	hm = create_hashmap(key_space);
	const char * key_6    = "abc";
	const char * key_7    = "cba";
	const char * key_8    = "bca";
	char * string_5 = "Hajo Kleingeld";

	// Insert ("abc" -> "Jasper").
	insert_data(hm, key_6, string_1, resolve_collision_2);
	assert(memcmp(get_data(hm, key_6), string_1, mystrlen(string_1)) == 0);

	// Insert ("cba" -> "Jens").
	insert_data(hm, key_7, string_2, resolve_collision_2);
	assert(memcmp(get_data(hm, key_7), string_2, mystrlen(string_2)) == 0);

	// Ensure that the key collision callback function was not called yet, as no collisions have occured
	assert(resolve_collision_called_count == 0);

	// Try to overwrite Jasper with newby, this should fail with callback 2
	insert_data(hm, key_6, string_3, resolve_collision_2);
	assert(memcmp(get_data(hm, key_6), string_1, mystrlen(string_1)) == 0);

	// Try to overwrite Jens with newby, this should fail with callback 2
	insert_data(hm, key_7, string_3, resolve_collision_2);
	assert(memcmp(get_data(hm, key_7), string_2, mystrlen(string_2)) == 0);

	// Ensure that the key collision callback function was called.
	assert(resolve_collision_called_count == 2);

	// Insert ("bca" -> "newby")
	insert_data(hm, key_8, string_3, resolve_collision_2);
	assert(memcmp(get_data(hm, key_8), string_3, mystrlen(string_3)) == 0);

	// Insert ("bca" -> "Hajo Kleingeld") and overwrite ("bca" -> "newby")
	insert_data(hm, key_8, string_5, resolve_collision);
	assert(memcmp(get_data(hm, key_8), string_5, mystrlen(string_5)) == 0);

	// Iterate the hash map
	iterate(hm, print_element);

	// Delete key 7 ("cba" -> "Jens")
	remove_data(hm, key_7, delete_callback);
	assert(get_data(hm, key_7) == NULL);

	// Can key 6 and key 8 still be accessed?
	assert(memcmp(get_data(hm, key_6), string_1, mystrlen(string_1)) == 0);
	assert(memcmp(get_data(hm, key_6), string_1, mystrlen(string_1)) == 0);

	// Was the delete callback called?
	assert(delete_callback_called_count == 1);

	// Delete the hash map.
	delete_hashmap(hm, delete_callback);

	// Was the delete callback called?
	assert(delete_callback_called_count == 3);


	return 0;
}
