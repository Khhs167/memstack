// Memstack, a small utility written by khhs
// Name has 99% already been used a hundred times before
// But please do not remove this comment if you plan to use it.

// C implementation

#include <memstack.h>
#include <stdlib.h>

struct memstack_chain_ptr_t{
    void* ptr;
    struct memstack_chain_ptr_t* next;
};

typedef struct memstack_chain_ptr_t memstack_chain_ptr;

memstack_chain_ptr* first = { NULL };

memstack_chain_ptr* get_item_list(memstack_chain_ptr* c){
    if(c->next == NULL)
        return c;
    return get_item_list(c->next);
}

void msinit(){
    first = malloc(sizeof(memstack_chain_ptr));
    first->ptr = NULL;
    first->next = NULL;
}

void* msalloc(int size){
    memstack_chain_ptr* p = (memstack_chain_ptr*)malloc(sizeof(memstack_chain_ptr));
    p->ptr = malloc(size);
    p->next = NULL;
    memstack_chain_ptr* c = get_item_list(first);
    c->next = p;
    return p->ptr;
}

void free_index(memstack_chain_ptr* index){
    if(index->ptr != NULL)
        free(index->ptr);
    if(index->next != NULL)
        free_index(index->next);
    free(index);
}

void msfree(){
    free_index(first);
}
