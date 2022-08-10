// Memstack, a small utility written by khhs
// Name has 99% already been used a hundred times before
// But please do not remove this comment if you plan to use it.

// C implementation

#include <memstack.h>

// Global memstack can be accessed across the whole of a code base, but is hidden.
// The global memstack cannot be accessed directly by the user, and instead they must
// use NULL or GLOBAL_MEMSTACK to apply functions such as msalloc and msfree to
// the global stack.
memstack* global = NULL;

// msinit() is a legacy function used specifically to initialise the global memstack.
// if msinit() is called after the global memstack has already been initialised the
// memstack_chain_ptr* chain will be freed and a new global memstack will be allocated.
void msinit(){

    // Check if global has already been initialised or not
    if (global == NULL) {
        global = msnew();
    } else {
        // If it is, we free its memory and create a new global memstack
        msfree(global);
        global = msnew();
    } 
}

// Creates a new memstack.
// Allocates a new memstack and the first node within the memstack chain.
// The memstack is used to manage a memstack chain within a local scope.
memstack* msnew() {
    // Allocate new memstack and the first memstack chain pointer.
    memstack* ms = (memstack*)malloc(sizeof(memstack));
    ms->first = NULL;  // There are no chain pointers yet.

    // Very important! We dereference ms->last in msalloc so
    // removing this line causes undefined behaviour (probably segfault).
    ms->last = ms->first;

    return ms;  // Return the memstack we created.
}

// Allocates a new node onto the memstack chain and allocates the space of parameter "size" for the user.
void* msalloc(memstack* storage, int size) {
    if(storage == GLOBAL_MEMSTACK) {
        // Ensure global is initialised before allocating
        if (global != NULL) {
            return msalloc(global, size);
        } else {
            // if not initialised, msalloc() now calls msinit() for the user
            msinit();
            return msalloc(global, size);
        }
    }
    // Create new node to add to the linked list.
    memstack_chain_ptr* new_node = (memstack_chain_ptr*)malloc(sizeof(memstack_chain_ptr));
    new_node->ptr = malloc(size);  // Allocate space user requested.
    new_node->previous = storage->last;  // Set the previous node as the current last node
    new_node->next = NULL;  // This will be the last element so "next" is NULL.

    // Check if there is a first node
    if (storage->first == NULL) {
        // If not, the node we just created will become the first node.
        storage->first = new_node;
        storage->last = storage->first;
    } else {
        // If there is we just create a new last node
        storage->last->next = new_node;
        storage->last = new_node;
    }

    return new_node->ptr;  // Return pointer to memory user wanted to be allocated.
}

// Recursively frees all the nodes.
// Totally a re-skin of free_index because I like this function but "node" sounded better to me.
void free_node(memstack_chain_ptr* node){

    if (node == NULL) {
        return;
    }

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
    if (storage == GLOBAL_MEMSTACK) {
        // Ensure global is not NULL before freeing
        // This is because we dereference global (so we don't want it to be NULL)
        if (global != NULL) {
            free_node(global->first);
            free(global);
        }
    } else {
        // If it's not NULL we can free it normally
        free_node(storage->first);
        free(storage);
    }
}

// Frees all nodes stored within the memstack but does not free the memstack itself.
void msclear(memstack* storage) {

    // Check if we're clearing global or not
    if (storage == GLOBAL_MEMSTACK) {

        // Ensure global is not NULL
        if (global != NULL) {
            msclear(global);  // Since global isn't NULL "storage == GLOBAL_MEMSTACK" will be false...
        } else {
            msinit();  // initialise global if not NULL.
            // We don't have to clear since msinit() generates an empty global anyway.
        }
    } else {
        // Free the memstack_chain_ptr* chain
        free_node(storage->first);

        // Create a new memstack_chain_ptr* chain
        storage->first = (memstack_chain_ptr*)malloc(sizeof(memstack_chain_ptr));
        storage->first->next = NULL;
        storage->first->previous = NULL;
        storage->first->ptr = NULL;

        // Set up last pointer for future allocations
        storage->last = storage->first;
    }

}
