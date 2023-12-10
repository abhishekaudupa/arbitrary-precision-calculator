#include "allocator.h"
#include <assert.h>

static Alloc_Mem_List *head = NULL;
static int lock = 1;

void *get_memory(const size_t n_bytes) {
    
    //to return allocated memory.
    void *mem_ptr = NULL;

    //unlock the allocate_memory function.
    lock = 0;

    //allocate memory dynamically.
    mem_ptr = allocate_memory(n_bytes);

    //lock the allocate_memory function.
    lock = 1;

    //track the allocation, if allocation succeeded.
    if(mem_ptr)
	insert_at_first(mem_ptr);

    return mem_ptr;
}

void *allocate_memory(const size_t n_bytes) {

    //design time ensuring no other outside function
    //calls this function.
    assert(lock != 1);
    
    //to return allocated memory.
    void *mem_ptr = NULL;

    //to keep track of allocation attempts.
    int alloc_attempt = MAX_MEM_ALLOC_ATTEMPTS;

    //make attempts to allocate memory.
    while(!mem_ptr && alloc_attempt) {
	mem_ptr = malloc(n_bytes);
	--alloc_attempt;
    }

    return mem_ptr;
}

Status insert_at_first(void *mem) {
    
    //design time check.
    assert(mem);

    //unlock the allocate_memory function.
    lock = 0;

    //allocate mem. for Alloc_Mem_List node.
    Alloc_Mem_List *new = allocate_memory(sizeof(*new));

    //lock the allocate_memory function.
    lock = 1;

    //handle allocation failure.
    if(!new)
	return s_failure;

    //store the memory that is to be tracked.
    new->mem = mem;

    //set new's next to head.
    new->next = head;

    //make the head point to new.
    head = new;

    return s_success;
}

void release_memory() {

    //get traversers to traverse Alloc_Mem_List.
    Alloc_Mem_List *trav = head;
    Alloc_Mem_List *foll = NULL;

    while(trav) {

	//increment follower.
	foll = trav;

	//increment traverser.
	trav = trav->next;

	//release memory inside the follower.
	free(foll->mem);

	//release the follower itself.
	free(foll);
    }
}
