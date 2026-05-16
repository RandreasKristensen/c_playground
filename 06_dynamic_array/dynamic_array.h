#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

typedef struct DynamicArray {
	int capacity; //max number of elements
	int element_size; //size of element data type
	int size; //current amount of elements
	void* data; //pointer to array[0]
} DynamicArray;
DynamicArray da_constructor(int capacity, int element_size);
void da_free(DynamicArray* arr);
void da_push(DynamicArray* arr, void* element);
void* da_get(DynamicArray* arr, int index);
void da_set(DynamicArray* arr, int index, void* element);
void da_pop(DynamicArray* arr);
void da_remove(DynamicArray* arr, int index);
void da_insert(DynamicArray* arr, int index, void* element);
void da_foreach(DynamicArray* arr, void (*fn)(void* element));

#endif //DYNAMIC_ARRAY_H
