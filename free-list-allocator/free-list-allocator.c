#include <stdio.h>
#include <stdbool.h>
#include <sys/mman.h>

struct metadata {
	size_t memory_size;
	bool is_free;
	struct metadata * ptr;
};

void * my_malloc(size_t request_size);
struct metadata *global_metadata;
void my_free(void * user_space);



int main(){
	
	void * raw_memory = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	struct metadata *metadata1 = (struct metadata *)raw_memory;
	metadata1->memory_size = 4096 - sizeof(struct metadata);
	metadata1->is_free = true;
	metadata1->ptr = NULL;
	
	global_metadata = metadata1;
	
	//here, i got the free space to use later after done using i need to destroy it
	void * my_data = my_malloc(36);
	// here after i am done using teh memory i destroy it
	my_free(my_data);
	return 0;
}


void * my_malloc(size_t request_size){
	
	struct metadata *metadata2 = global_metadata ;
	
	
	while (metadata2 !=  NULL){
		if (metadata2->is_free == true && metadata2->memory_size >= request_size){
			void * user_space = (void *)(metadata2 + 1);
			struct metadata *metadata3 = (struct metadata *)((char *)user_space + request_size);

			size_t old_size = metadata2->memory_size;

			metadata2->is_free = false;
			metadata2->memory_size = request_size;
			metadata3->ptr = metadata2->ptr;
			metadata2->ptr = metadata3;

			metadata3->is_free = true;
			metadata3->memory_size = old_size - request_size - sizeof(struct metadata);
			metadata3->ptr = NULL;

			return user_space;

		}
		
		metadata2 = metadata2->ptr;
		
	}
return NULL;	
}

void my_free(void *user_space){

	struct metadata *cleaning_crew = ((struct metadata *)user_space) - 1;
	cleaning_crew->is_free = true;
}
