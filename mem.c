#include "mem.h"
#include <stdlib.h>
#include <math.h>

//== struct algorithms ====================

int checkHeapFreeSpace(heap* h) {
    int size = 0; 
    for(int ix = 0; ix < HEAP_SIZE; ix++)
        if(h->total_space->occupied == FALSE) 
            size++;
    return size; 
}

int checkHeapOccupiedSpace(heap* h) {
    return HEAP_SIZE - checkHeapFreeSpace(h);
}

//== heap algorithms ======================

heap* initialize_heap() {
    heap* h = (heap*)malloc(sizeof(heap));
    h->used_space = 0;
    h->free_space = HEAP_SIZE;
    h->root = NULL;
    for(int ix = 0; ix < HEAP_SIZE; ix++)
        h->total_space[ix].occupied = FALSE;
    return h;
}

int heap_parent(int index) {
    return (index - 1) / 2;
} 

int heap_left_child(int index) {
    return (index * 2) + 1;
}

int heap_right_child(int index) {
    return (index * 2) + 2;
}

int level(int index) {
    return (int)floor(log2(index + 1)) % 2 == 0;
}

void insert(Block* block, heap* manager) {

    // if the heap is empty
    if(manager->root == NULL) {
        manager->root = block;
        block->parent = NULL;
        block->left_child = NULL;
        block->right_child = NULL;
    }
}

void del(Block* block, heap* manager) {

}

//== main algorithms ========================

void* allocate(size_t size, heap* manager) {

    // variables
    void* ptr; 

    // testing purposes
    ptr = malloc(sizeof(char) * size);

    
    // update heap details
    manager->used_space += size;
    manager->free_space -= size; 

    

    return ptr;
}

int deallocate(void* ptr, heap* manager) {    

    free(ptr);

    ptr = NULL;

    // update heap details
    manager->used_space -= sizeof(ptr);
    manager->free_space += sizeof(ptr);

    return 0; 
}