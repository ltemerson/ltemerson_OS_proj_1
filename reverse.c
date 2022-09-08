#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node {
	char *data;
	struct Node* next;
};

void printList(struct Node*);
void writeToFile(FILE*, struct Node*);

void printList(struct Node* head) {
	while(head != NULL) {
		printf("%s",head->data);
		head = head->next;
	}
}

void writeToFile(FILE* fp, struct Node* head) {
	while(head !=NULL) {
		fprintf(fp,"%s",head->data);
		head = head->next;
	}
}

int main(int argc, char *argv[])
{
	FILE *file1;
	FILE *file2;
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
	
	if(argc == 3) {
		int fp1Cnt = strlen(argv[1]);
		int fp2Cnt = strlen(argv[2]);
		if(fp1Cnt == fp2Cnt) {
			if((strncmp(argv[1],argv[2],fp2Cnt)) == 0) {
				fprintf(stderr, "error: input and output file must differ\n");
				return(1);
			}
		} 

		if((file2 = fopen(argv[2],"w")) == NULL) {
			fprintf(stderr, "error: cannot open file '%s'\n",argv[2]);
			return(1);
		}
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
	
	if(argc == 2){
		printList(head);
	}
	
	if(argc == 3) {
		writeToFile(file2,head);
	}
	
	while(head!=NULL) {
		curr = head;
		head= head->next;
		if(curr->data != NULL) {
			free(curr->data);
		}
		free(curr);
	}

	free(head);
	fclose(file1);
	if(argc == 3) {
		fclose(file2);
	}
	free(line);
	return(0);
}
