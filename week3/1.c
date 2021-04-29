#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 1024

struct Node {
    char name[LINE_MAX];
    struct Node *next;
};

void push(struct Node **head_ref, char *name) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    strcpy(new_node->name, name);
    new_node->next = (*head_ref);
    (*head_ref) = new_node;
}

void printList(struct Node* node) {
    while (node != NULL) {
        printf("%s ", node->name);
        printf("\n");
        node = node->next;
    }
}

int main(void) {
    struct Node *size_s = NULL;
    struct Node *size_m = NULL;

    struct Node *size_l = NULL;

    struct Node *size_xl = NULL;

    static char line[LINE_MAX];
    int index = 1;
    int sum, s, m, l, xl, size;
    char name[LINE_MAX];
    
    FILE *stdin = fopen("stdin.txt", "r");
    fscanf(stdin, "%d %d %d %d %d", &sum, &s, &m, &l, &xl);
    for(int i = 0; i < sum; i++) {
        fscanf(stdin, "%s %d", name, &size);
        if(s >= size) {
            push(&size_s, name);
        }else if(s < size && size <= m) {
            push(&size_m, name);

        }else if(m < size && size <= xl) {
            push(&size_l, name);

        }else {
            push(&size_xl, name);
            
        }
        
    }   
    printf("S: \n");
    printList(size_s);
    printf("M: \n");

    printList(size_m);
    printf("L: \n");

    printList(size_l);
    printf("XL: \n");

    printList(size_xl);


}