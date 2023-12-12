#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdlib.h>
#include "common.h"

#define MAX_MEM_ALLOC_ATTEMPTS 500

//List to keep track of allocated memory.
typedef struct _Alloc_Mem_List {
    void *mem;
    struct _Alloc_Mem_List *next;
} Alloc_Mem_List;

void *get_memory(const size_t n_bytes);
    
void *allocate_memory(const size_t n_bytes);
    
Status track_mem(void *mem);
    
void release_memory();

#endif
