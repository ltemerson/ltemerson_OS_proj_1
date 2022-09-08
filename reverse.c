#include <stdio.h>
#include <stdlib.h>
struct Node {
	char *data;
	struct Node* next;
};

void printList(struct Node*);

void printList(struct Node* head) {
	printf("\n[head] =>");
	while(head != NULL) {
		printf(" %s =>",head->data);
		head = head->next;
	}

	printf(" [null]\n");
}

int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	struct Node* head = (struct Node*) malloc(sizeof(struct Node));
	head->next = NULL;

	if ((file = fopen(argv[1],"r")) == NULL) {
		printf("Error!\n");
		return(1);
	}

	while ((read = getline(&line, &len, file)) != -1) {
		printf("Retrieved line of length %zd:\n", read);
		fwrite(line, read, 1, stdout);
		head->data=line;
		struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
		new_node->next = head;

		head = new_node;

		line = NULL;
		
	}

	struct Node* curr;
	curr = head;
	head = head->next;

	free(curr);

	printList(head);

	while(head!=NULL) {
		curr = head;
		head= head->next;
		if(curr->data != NULL) {
			free(curr->data);
		}
		free(curr);
	}
	free(head);
	fclose(file);
	free(line);
	return(0);
}
