// Memstack, a small utility written by khhs
// Name has 99% already been used a hundred times before
// But please do not remove this comment if you plan to use it.

// C implementation

#include <memstack.h>

#include <stdlib.h>
#include <stdio.h>

// Global memstack can be accessed across the whole of a code base, but is hidden.
// The global memstack cannot be accessed directly by the user, and instead they must
// use NULL or GLOBAL_MEMSTACK to apply functions such as msalloc and msfree to
// the global stack.
memstack* global = NULL;

// Set to 0 if global is not initialized, and 1 if it is.
// Checking for a NULL global is great and all, but the moment we free global
// it breaks.
static int __global_init = 0;

// msinit() is a legacy function used specifically to initialise the global memstack.
// if msinit() is called after the global memstack has already been initialised the
// memstack_chain_ptr* chain will be freed and a new global memstack will be allocated.
void msinit() {

    // Check if global has already been initialised or not
    if (__global_init) {
        global = msnew();
        __global_init = 1;
    } else {
        // If it is, we free its memory and create a new global memstack
        msfree(global);
        global = msnew();
        __global_init = 1;
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

    ms->length = 0;

    return ms;  // Return the memstack we created.
}

// Allocates a new node onto the memstack chain and allocates the space of parameter "size" for the user.
void* msalloc(memstack* storage, int size) {
    if(storage == GLOBAL_MEMSTACK) {
        // Ensure global is initialised before allocating
        if (__global_init) {
            return msalloc(global, size);
        } else {
            // if not initialised, msalloc() now calls msinit() for the user
            msinit();
            return msalloc(GLOBAL_MEMSTACK, size);
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

    ++storage->length;

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
        // Ensure global is initialized first
        // This is because we dereference global (so we don't want it to be unallocated memory)
        if (__global_init) {
            free_node(global->first);
            free(global);
            __global_init = 0;
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
        if (__global_init) {
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

        storage->length = 0;
    }
}

// Add a new node without allocating memory.
// This can be used when the user wants to add previously allocated to the memstack without
// allocating new memory through msalloc().
void mspush(memstack* storage, void* ptr) {
    if (storage == GLOBAL_MEMSTACK) {

        // Ensure global is not NULL
        if (global != NULL) {
            mspush(global, ptr);
        } else {
            msinit();
            mspush(global, ptr);
        }
    } else if (ptr == NULL) {
        return;
    } else {
        // Create new node to add to the linked list.
        memstack_chain_ptr* new_node = (memstack_chain_ptr*)malloc(sizeof(memstack_chain_ptr));
        new_node->ptr = ptr;  // Set pointer to what ever use passed in
        new_node->previous = storage->last;  // Set the previous node as the current last node
        new_node->next = NULL;  // This will be the last element so "next" is NULL.
	
        // Make our new node the last node
        
        // If we don't have any nodes on the memstack, we'll get a segfault as we try to index a null pointer.
        // This *should* avoid that by assigning this node as first if no first node exists.
        
        // TODO: Check if this needs to be done elsewhere
        if(storage->first != NULL) {
        	storage->last->next = new_node;
		new_node->previous = storage->last;
        	storage->last = new_node;

        } else {
        	storage->first = new_node;
        	storage->last = storage->first;
        }

        ++storage->length;
    }
}

// Removes the last node from the memstack and returns the pointer allocated with msalloc()
// If NULL is given, and global is not initialised, then mspop() will return NULL.
void* mspop(memstack* storage) {
    if (storage == GLOBAL_MEMSTACK) {

        // Ensure global is not NULL.
        if (global != NULL) {
            return mspop(global);
        } else {
            return NULL;
        }
    } else if (storage->length < 2) {
        // Our handling of the memstack is different if it's length is less than 2
        void* user_ptr = storage->last->ptr;
        free(storage->last);
        storage->last = NULL;
        storage->first = NULL;
        return user_ptr;
    } else {
            // Store the pointer the user wants.
            void* user_ptr = storage->last->ptr;

            // Get the second-to-last node that will become the new last node.
            memstack_chain_ptr *new_last = storage->last->previous;

            // Free the last node in the memstack.
            free(storage->last);
            new_last->next = NULL;  // Ensures we do not encounter undefined behaviour on msfree() / msclear() / mspop() / msrollback()

            // Set previously second-to-last node to the last node.
            storage->last = new_last;

            return user_ptr;  // Give the user what they want :)
    }
}

// msprint loops through the linked list and shows some debug information.
// This is useful for both maintainers, and users of memstack.
// Originally created to help debug, I've made it available to all library users.
// For each node, it shows the previous, next, and current memstack_chain_ptr
void msfprint(memstack* storage, FILE* stream) {

    // To handle global memstack
    if (storage == GLOBAL_MEMSTACK) {
        if (__global_init)
            msinit();  // Allocate for the user if needs be

        msfprint(global, stream);
    } else {
        memstack_chain_ptr* current_node = storage->first;
        int index = 0;
        fprintf(stream, "Printing memstack: \n");
        while (current_node != NULL) {
            fprintf(
                stream,
                " [%d] %p <--previous-- [%d] Current: %p --next--> [%d] %p\n",
                    index-1,                        /* Previous node index  */
                    current_node->previous,         /* Previous node pointer */
                    index,                          /* Current node index */
                    current_node,                   /* Current node pointer */
                    index+1,                        /* Next node index */
                    current_node->next              /* Next node pointer */
            );
            current_node = current_node->next;
            ++index;
        }
        fprintf(stream, " [INFO] Node count: %d\n", index);
        fprintf(stream, " [INFO] Nodes are linked to both the next, and previous node\n");
        fflush(stream);
    }
}

// msprint loops through the linked list and shows some debug information.
// This is useful for both maintainers, and users of memstack.
// Originally created to help debug, I've made it available to all library users.
// For each node, it shows the previous, next, and current memstack_chain_ptr
extern void msprint(memstack* storage) {
    msfprint(storage, stdout);
}


// msrollback rolls back a memstack by removing a number of memstack_chain_ptr* nodes.
// The number of nodes removed is described by rollback_count.
// Nodes are removed from the last node added, to the first node added.
// The boolean parameter "destructive" details whether the user allocated memory (void* ptr) is freed or not.
// If destructive is true, then everything is freed, even the user allocated memory,
// otherwise, if destructive is false, the user allocate memory is not removed (DANGEROUS).
void msrollback(memstack* storage, int rollback_count, int destructive) {

    if (storage == GLOBAL_MEMSTACK) {
        if (global != NULL) {
            msrollback(global, rollback_count, destructive);
        } else {
            return;
        }
    } else {
        // Destroys "rollback_count" nodes
        while (rollback_count > 0) {
            // mspop() will handle freeing the latest node for us
            void* ptr = mspop(storage);
            if (destructive == 1) {
                free(ptr);  // Free user allocated memory if rollback is destructive
            }
            --rollback_count;
            --storage->length;
        }
    }

}

// Free a pointer and remove it from the stack, if you want to dealloc ahead of time!
void msdealloc(memstack* storage, void* memory) {

  if(memory == NULL)
    return;

  if (storage == GLOBAL_MEMSTACK) {
    if (global != NULL) {
      msdealloc(global, memory);
    } else {
      return;
    }
  }

  memstack_chain_ptr* c = storage->first;
  
  while(c->ptr != memory) {
    if(c->next == NULL)
      return;

    c = c->next;
  }

  if(c->next != NULL)
    c->next->previous = c->previous;
  
  if(c->previous != NULL)
    c->previous->next = c->next;

  free(c);
  free(memory);

}

#ifdef MSCLEANUP

__attribute__((destructor)) 
static void msexit() {
	msfree(GLOBAL_MEMSTACK);
}

#endif
