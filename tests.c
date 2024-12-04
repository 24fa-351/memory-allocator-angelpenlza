#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "mem.h"

#define SUCCESS 0

//== struct to test=========================================

typedef struct {
    int id; 
    char* name;
    float gpa;
} Student;

//==========================================================


int int_malloc_test(size_t size, heap* manager) {

    // being integer testing
    printf("testing integer allocation...\n");

    // call the allocate function
    int* ints = (int*)allocate(size, manager);
    if(ints == NULL) {
        printf("error with the allocate() function\n");
        return 1; 
    }

    // check heap details
    if(manager->used_space == checkHeapOccupiedSpace(manager)) {
        printf("space being used: %d\n", manager->used_space);
        printf("available free space: %d\n", manager->free_space);
    } else {
        printf("error calculating space.\n");
        printf("manager->used_space: %d\n", manager->used_space);
        printf("actual used space: %d\n", checkHeapOccupiedSpace(manager));
        return 1; 
    }

    // fill the array
    for(int ix = 0; ix < (int)size; ix++) {
        ints[ix] = ix; 
    }

    // free the array
    if(deallocate(ints, manager) != SUCCESS) {
        printf("deallocate did not free pointer properly\n");
        return 1; 
    }

    return 0; 
}
//==========================================================

int double_malloc_test(size_t size, heap* manager) {

    // begin double testing
    printf("testing double allocation...\n");

    // call the allocate function
    double* doubles = (double*)allocate(size, manager);
    if(doubles == NULL) {
        printf("error with the allocate function()\n");
        return 1; 
    }

    // check heap details
    printf("space being used: %d\n", manager->used_space);
    printf("available free space: %d\n", manager->free_space);

    // fill the array
    for(int ix = 0; ix < (int)size; ix++) {
        doubles[ix] = ix/3.0;
    }

    // free the array
    if(deallocate(doubles, manager) != SUCCESS) {
        printf("deallocate did not properly free the pointer\n");
        return 1; 
    }

    return 0;
}
//==========================================================

int struct_malloc_test(size_t size, heap* manager) {

    // begin struct testing
    printf("testing struct allocation\n");

    // call the allocate function
    Student* students = (Student*)allocate(size, manager);
    if(students == NULL) {
        printf("error with the allocate function\n");
        return 1; 
    }

    // check heap details
    printf("space being used: %d\n", manager->used_space);
    printf("available free space: %d\n", manager->free_space);

    // fill the array 
    for(int ix = 0; ix < (int)size; ix++) {
        students[ix].id = ix;
        students[ix].name = "none";
        students[ix].gpa = 4; 
    }

    // free the array
    if(deallocate(students, manager) != SUCCESS) {
        printf("deallocate failed\n");
        return 1; 
    }

    return 0;
}
//==========================================================

int small_multiple_allocations(heap* manager) {

    // test for allocating a small number of things
    printf("small testing...\n");

    // call the allocate function
    int* ints = (int*)allocate(sizeof(int) * 20, manager);
    char* chars = (char*)allocate(sizeof(char) * 20, manager);
    float* floats = (float*)allocate(sizeof(float) * 20, manager);

    if(ints == NULL || chars == NULL || floats == NULL) {
        printf("allocate failed\n");
        return 1; 
    }

    // check heap details
    printf("space being used: %d\n", manager->used_space);
    printf("available free space: %d\n", manager->free_space);

    // fill arrays 
    for(int ix = 0; ix < 20; ix++) {
        ints[ix] = ix; 
        chars[ix] = '*';
        floats[ix] = ix/2.0;
    }

    // show arrays 
    printf("ints[] contents");
    for(int ix = 0; ix < 20; ix++) {
        printf(" - %d", ints[ix]); 
    } printf("\n");

    printf("chars[] contents");
    for(int ix = 0; ix < 20; ix++) {
        printf(" - %c", chars[ix]);
    } printf("\n");

    printf("floats[] contents");
    for(int ix = 0; ix < 20; ix++) {
        printf(" - %f", floats[ix]);
    } printf("\n");

    // free arrays
    if( deallocate(ints, manager) != SUCCESS || 
        deallocate(chars, manager) != SUCCESS ||
        deallocate(floats, manager) != SUCCESS) {
            printf("error freeing pointers\n");
            return 1; 
    }

    // check heap details
    printf("space being used: %d\n", manager->used_space);
    printf("available free space: %d\n", manager->free_space);

    return 0;
}

//==========================================================

int large_multiple_allocations(heap* manager) {

    // begin testing
    printf("large testing\n");
    
    // call allocate function
    int* ints = (int*)allocate(sizeof(int) * 500, manager);
    char* chars = (char*)allocate(sizeof(char) * 500, manager);
    float* floats = (float*)allocate(sizeof(float) * 500, manager);

    if(ints == NULL || chars == NULL || floats == NULL) {
        printf("allocate failed\n");
        return 1; 
    }

    // check heap details
    printf("space being used: %d\n", manager->used_space);
    printf("available free space: %d\n", manager->free_space);

    // fill the arrays 
    for(int ix = 0; ix < 500; ix++) {
        ints[ix] = ix;
        chars[ix] = '*';
        floats[ix] = ix/2.0;
    }

    // free arrays
    if( deallocate(ints, manager) != SUCCESS ||
        deallocate(chars, manager) != SUCCESS ||
        deallocate(floats, manager) != SUCCESS) {
            printf("failed to deallocate pointers\n");
            return 1; 
    }

    // check heap details
    printf("space being used: %d\n", manager->used_space);
    printf("available free space: %d\n", manager->free_space);

    return 0; 
}

//==========================================================

int main(int argc, char* argv[]) {

//== initialize heap for allocation ========================

    heap* manager = initialize_heap();

//== test specific test, if user specifies =================

    int test = 0;

    if(argc > 2) {
        if(strcmp(argv[1], "-t") != 0) {
            printf("invalid flag\n");
            exit(1);
        } else {
            test = atoi(argv[2]);
        }
    }

//== run the tests =========================================
    printf("\trunning tests..\n");

//== test two ===============================================

    printf("=====================================\n");

    if(int_malloc_test(sizeof(int) * 100, manager) == SUCCESS) 
        printf("integer allocation successful\n");
    else {
        printf("failed to allocate space for int type\n");
        exit(1);
    }
    printf("=====================================\n");

//== test four ===============================================

    printf("=====================================\n");

    if(double_malloc_test(sizeof(double) * 100, manager) == SUCCESS) 
        printf("double allocation successful\n");
    else {
        printf("failed to allocate space for double type\n");
        exit(1);
    }
    printf("=====================================\n");

//== test five ===============================================

    printf("=====================================\n");

    if(struct_malloc_test(sizeof(Student) * 100, manager) == SUCCESS) 
        printf("struct allocation successful\n");
    else {
        printf("failed to allocate space for stuct type\n");
        exit(1);
    }
    printf("=====================================\n");

//== test six =================================================

    printf("=====================================\n");

    if(small_multiple_allocations(manager) == SUCCESS) 
        printf("small allocation testing successful\n");
    else {
        printf("error testing small allocation process\n");
        exit(1);
    }

    printf("=====================================\n");

//== test seven ================================================

    printf("=====================================\n");

    if(large_multiple_allocations(manager) == SUCCESS) 
        printf("large allocation testing successful\n");
    else {
        printf("error testing large allocation process\n");
        exit(1);
    }

    printf("=====================================\n");

    printf("\tall tests passed\n");
    return 0; 
}