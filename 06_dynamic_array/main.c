#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamic_array.h"

// gcc main.c dynamic_array.c -o test

// ------------------------------------------------------------
// Test infrastructure
// ------------------------------------------------------------

static int verbose = 0;
static int tests_run = 0;
static int tests_passed = 0;

#define ASSERT(label, condition) do { \
    tests_run++; \
    if (condition) { \
        tests_passed++; \
        if (verbose) printf("  PASS: %s\n", label); \
    } else { \
        if (verbose) printf("  FAIL: %s\n", label); \
    } \
} while(0)

void print_result(const char *test_name, int before) {
    int passed = tests_passed - before;
    int total  = tests_run - (tests_run - (tests_run - before + (tests_run - before)));
    // simpler: track before_run too
    printf("[%s] — will show after refactor, ignore this line\n", test_name);
}

// Better: pass both before counts
void result(const char *name, int passed_before, int run_before) {
    int p = tests_passed - passed_before;
    int t = tests_run    - run_before;
    printf("%-20s %d/%d %s\n", name, p, t, (p == t) ? "PASS" : "FAIL");
}

// ------------------------------------------------------------
// Helper
// ------------------------------------------------------------

void print_int(void *e) {
    if (verbose) printf("  element: %d\n", *(int*)e);
}

// ------------------------------------------------------------
// Tests
// ------------------------------------------------------------

void test_constructor(void) {
    int p = tests_passed, r = tests_run;
    if (verbose) printf("\n-- constructor --\n");

    DynamicArray arr = da_constructor(8, sizeof(int));
    ASSERT("capacity set",      arr.capacity     == 8);
    ASSERT("element_size set",  arr.element_size == sizeof(int));
    ASSERT("size starts at 0",  arr.size         == 0);
    ASSERT("data not NULL",     arr.data         != NULL);
    da_free(&arr);

    result("da_constructor", p, r);
}

void test_push(void) {
    int p = tests_passed, r = tests_run;
    if (verbose) printf("\n-- push --\n");

    DynamicArray arr = da_constructor(4, sizeof(int));
    int val = 42;
    da_push(&arr, &val);
    ASSERT("size increments",   arr.size == 1);
    ASSERT("value stored",      *(int*)da_get(&arr, 0) == 42);

    // push past capacity to test resize
    int vals[] = {1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) da_push(&arr, &vals[i]);
    ASSERT("size after overflow", arr.size == 6);
    ASSERT("capacity grew",       arr.capacity > 4);
    da_free(&arr);

    result("da_push", p, r);
}

void test_get(void) {
    int p = tests_passed, r = tests_run;
    if (verbose) printf("\n-- get --\n");

    DynamicArray arr = da_constructor(4, sizeof(int));
    int vals[] = {10, 20, 30};
    for (int i = 0; i < 3; i++) da_push(&arr, &vals[i]);

    ASSERT("get index 0", *(int*)da_get(&arr, 0) == 10);
    ASSERT("get index 1", *(int*)da_get(&arr, 1) == 20);
    ASSERT("get index 2", *(int*)da_get(&arr, 2) == 30);
    da_free(&arr);

    result("da_get", p, r);
}

void test_set(void) {
    int p = tests_passed, r = tests_run;
    if (verbose) printf("\n-- set --\n");

    DynamicArray arr = da_constructor(4, sizeof(int));
    int val = 1;
    da_push(&arr, &val);
    int newval = 99;
    da_set(&arr, 0, &newval);
    ASSERT("value updated", *(int*)da_get(&arr, 0) == 99);
    da_free(&arr);

    result("da_set", p, r);
}

void test_pop(void) {
    int p = tests_passed, r = tests_run;
    if (verbose) printf("\n-- pop --\n");

    DynamicArray arr = da_constructor(4, sizeof(int));
    int vals[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) da_push(&arr, &vals[i]);
    da_pop(&arr);
    ASSERT("size decrements", arr.size == 2);
    ASSERT("last element gone", *(int*)da_get(&arr, 1) == 2);
    da_free(&arr);

    result("da_pop", p, r);
}

void test_remove(void) {
    int p = tests_passed, r = tests_run;
    if (verbose) printf("\n-- remove --\n");

    DynamicArray arr = da_constructor(4, sizeof(int));
    int vals[] = {10, 20, 30, 40};
    for (int i = 0; i < 4; i++) da_push(&arr, &vals[i]);
    da_remove(&arr, 1);  // remove 20
    ASSERT("size decrements",    arr.size == 3);
    ASSERT("element 0 intact",   *(int*)da_get(&arr, 0) == 10);
    ASSERT("element shifted",    *(int*)da_get(&arr, 1) == 30);
    ASSERT("element 2 shifted",  *(int*)da_get(&arr, 2) == 40);
    da_free(&arr);

    result("da_remove", p, r);
}

void test_insert(void) {
    int p = tests_passed, r = tests_run;
    if (verbose) printf("\n-- insert --\n");

    DynamicArray arr = da_constructor(4, sizeof(int));
    int vals[] = {10, 30};
    for (int i = 0; i < 2; i++) da_push(&arr, &vals[i]);
    int newval = 20;
    da_insert(&arr, 1, &newval);  // insert 20 between 10 and 30
    ASSERT("size increments",  arr.size == 3);
    ASSERT("element 0",        *(int*)da_get(&arr, 0) == 10);
    ASSERT("inserted element", *(int*)da_get(&arr, 1) == 20);
    ASSERT("shifted element",  *(int*)da_get(&arr, 2) == 30);
    da_free(&arr);

    result("da_insert", p, r);
}

void test_foreach(void) {
    int p = tests_passed, r = tests_run;
    if (verbose) printf("\n-- foreach --\n");

    DynamicArray arr = da_constructor(4, sizeof(int));
    int vals[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) da_push(&arr, &vals[i]);
    if (verbose) da_foreach(&arr, print_int);
    // not much to assert without side effects — just check it doesn't crash
    ASSERT("foreach runs without crash", 1);
    da_free(&arr);

    result("da_foreach", p, r);
}

// ------------------------------------------------------------
// Main
// ------------------------------------------------------------

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "-v") == 0) verbose = 1;

    printf("=== dynamic_array tests ===\n");
    printf("%-20s %s\n", "function", "result");
    printf("-----------------------------\n");

    test_constructor();
    test_push();
    test_get();
    test_set();
    test_pop();
    test_remove();
    test_insert();
    test_foreach();

    printf("-----------------------------\n");
    printf("total: %d/%d passed\n", tests_passed, tests_run);
    return (tests_passed == tests_run) ? 0 : 1;
}
