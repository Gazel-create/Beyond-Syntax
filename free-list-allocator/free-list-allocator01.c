#include <stdio.h>
#include <stdbool.h>
#include <sys/mman.h>


struct  node_data {
	
	size_t memory_size;
	bool is_free;
	struct node_data * ptr;
};


struct node_data *global_start;

void *my_malloc(size_t request_size);

int main(){
	
	void *raw_memory = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	
	struct node_data *metadata = (struct node_data *)raw_memory;
	metadata->is_free = true;
	metadata->memory_size = 4096 - sizeof(struct node_data);
	metadata->ptr = NULL;

	global_start = metadata;

	my_malloc(34);
	
	return 0;
}

void *my_malloc(size_t request_size) {
    struct node_data *metadata2 = global_start;
    
    while (metadata2 != NULL) {
        if (metadata2->is_free == true && metadata2->memory_size >= request_size) {
            
            void *user_memory = (void *)(metadata2 + 1);
            struct node_data *metadata3 = (struct node_data *)((char *)user_memory + request_size);
            
            size_t old_size = metadata2->memory_size;
            
            metadata2->memory_size = request_size;
            metadata2->is_free = false;
            
            metadata3->ptr = metadata2->ptr;
            metadata2->ptr = metadata3;
            
            metadata3->is_free = true;
            metadata3->memory_size = old_size - request_size - sizeof(struct node_data);
            
            return user_memory;
        }
        metadata2 = metadata2->ptr;
    }
    return NULL;
}
