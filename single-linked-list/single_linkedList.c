#include <stdio.h>
#include <stdlib.h>


struct node {
	int x;
	struct node *ptr;
};



int main (){
	int value[] = {10, 20, 30};

	struct node *head = NULL;
	
	for (int x = 0; x < 3; x++){

		struct node *new_node = malloc(sizeof(struct node));
		
		new_node->x = value[x];
		new_node->ptr = head;

		head = new_node;	
	
		}

	struct node *current = head;
	while (current != NULL){
		struct node *next_node = current->ptr;

		free(current);
		current = next_node;
	}
	
	head = NULL;
	return 0;

}

