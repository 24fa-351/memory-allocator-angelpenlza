#ifndef MEMORY_ALLOCATOR
#define MEMORY_ALLOCATOR

#include <stdlib.h>

#define TRUE 0
#define FALSE 1
#define HEAP_SIZE 10000

//== structs =============================

typedef struct {
    int occupied;   // boolean value
    uint8_t size;   // 1 byte data type
    void* value;    // void* for flexibility
    struct Block* left_child;
    struct Block* right_child;
    struct Block* parent;
} Block;

typedef struct {
    Block total_space[HEAP_SIZE];
    int used_space; 
    int free_space;
    Block* root; 
} heap;

//== struct algorithms ====================

int checkHeapFreeSpace(heap* h);

int checkHeapOccupiedSpace(heap* h);

//== heap algorithms ======================

heap* initialize_heap();

int heap_parent(int index);

int heap_left_child(int index);

int heap_right_child(int index);

int level(int index);

void insert(Block* block, heap* manager);

void del(Block* block, heap* manager);

//== main algorithms ======================

void* allocate(size_t size, heap* manager);

int deallocate(void* ptr, heap* manager);

#endif