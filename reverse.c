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
	FILE *file1;
	FILE *file2
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	
	if (argc<2 || argc>3) {
		fprintf(stderr, "usage: reverse <input> <output>\n");
		return(1);
	}
	

	if ((file1 = fopen(argv[1],"r")) == NULL) {
		fprintf(stderr, "error: cannot open file '%s'\n",argv[1]);
		return(1);
	}
	
	struct Node* head = (struct Node*) malloc(sizeof(struct Node));
	if(head == NULL) {
		fprintf(stderr,"error: malloc failed\n");
		return(1);
	}
		
	head->next = NULL;
	
	while ((read = getline(&line, &len, file1)) != -1) {
		head->data=line;
		struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
		if(new_node == NULL) {
			fprintf(stderr,"error: malloc failed\n");
			return(1);
		}
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
