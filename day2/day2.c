#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *ptr;
};

int main()
{

	int buff[] = {10, 20, 30};
	struct node *head = NULL;
			
		for (int i = 0; i < 3; ++i){
			
			struct node *memory = malloc(sizeof(struct node));
			memory->data = buff[i];
			memory->ptr = head;

			head = memory;
		}
		
		struct node *prev = NULL;
		struct node *current = head;
		struct node *next = NULL;
		
		while (current != NULL){
			
			next = current->ptr;
			current->ptr = prev;
			prev = current;
			current = next;



		}


		return 0;
		
		
			
	
}
