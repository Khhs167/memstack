// Memstack, a small utility written by khhs
// Name has 99% already been used a hundred times before
// But please do not remove this comment if you plan to use it.

// C implementation

#include <memstack.h>
#include <stdlib.h>

// Creates a new memstack.
// Allocates a new memstack and the first node within the memstack chain.
// The memstack is used to manage a memstack chain within a local scope.
memstack* msnew() {
    // Allocate new memstack and the first memstack chain pointer.
    memstack* ms = (memstack*)malloc(sizeof(memstack));
    ms->first = (memstack_chain_ptr*)malloc(sizeof(memstack_chain_ptr));

    // We just set everything to NULL for now.
    ms->first->ptr = NULL;
    ms->first->next = NULL;

    // Very important! We dereference ms->last in msalloc so
    // removing this line causes undefined behaviour (probably segfault).
    ms->last = ms->first;

    return ms;  // Return the memstack we created.
}

// Allocates a new node onto the memstack chain and allocates the space of parameter "size" for the user.
void* msalloc(memstack* storage, int size) {

    // Create new node to add to the linked list.
    memstack_chain_ptr* new_node = (memstack_chain_ptr*)malloc(sizeof(memstack_chain_ptr));
    new_node->ptr = malloc(size);  // Allocate space user requested.
    new_node->next = NULL;  // This will be the last element so "next" is NULL.

    // Make our new node the last node
    storage->last->next = new_node;
    storage->last = new_node;

    return new_node->ptr;  // Return pointer to memory user wanted to be allocated.
}

// Recursively frees all the nodes.
// Totally a re-skin of free_index because I like this function but "node" sounded better to me.
void free_node(memstack_chain_ptr* node){

    // We check if the node contains one of the user's allocations and free it.
    if(node->ptr != NULL)
        free(node->ptr);

    // We check if there's another node.
    if(node->next != NULL)
        free_node(node->next);  // Recursion bitch! Yeah, khhs!

    free(node);  // Free the last node... RIP.
}

// Frees all the nodes stored within the memstack and frees the memstack itself.
void msfree(memstack* storage) {
    free_node(storage->first);
    free(storage);
}
