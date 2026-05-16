#include <stdlib.h>
#include "dynamic_array.h"

DynamicArray da_constructor(int capacity, int element_size) {
	DynamicArray arr;
	arr.capacity = capacity;
	arr.element_size = element_size;
	arr.size = 0;
	arr.data = malloc(capacity*element_size);
	return arr;
}

static void da_resize(DynamicArray* arr) {
	//use realloc to double capacity
	//update capacity
}

void da_free(DynamicArray* arr) {
	//free mem
}

void da_push(DynamicArray* arr, void* element) {
	//check if reaaloc needed
	//get ptr to next element
	//set value at ptr to value at element
	//update size
}

void* da_get(DynamicArray* arr, int index) {
	//return ptr to element at index from element size and start ptr
}

void da_set(DynamicArray* arr, int index, void* element) {
	//use da_get to get ptr to index
	//set value at index to element
}

void da_pop(DynamicArray* arr) {
	//update size
}

void da_remove(DynamicArray* arr, int index) {
	//use da_get tk get ptr to index
	//move everything after one spot back using memmove
	//update size
}

void da_insert(DynamicArray* arr, int index, void* element) {
	//check if reaaloc needed
	//use da_get to get ptr to index
	//move everything including and after one spot foward
	//maybe start at end and end at index
	//use memmove
	//update size
}

void da_foreach(DynamicArray* arr, void (fn*)(void* element) {
	//call function on each element
}
