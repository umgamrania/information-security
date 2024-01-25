#include <stdio.h>
#include <string.h>
#include "linked_list.h"

char *cipher(char *plain_text, int depth) {
    linked_list_t **matrix = (linked_list_t**)malloc(depth * sizeof(linked_list_t*));

    // initializing linked_list
    for(int i = 0; i < depth; i++){
        matrix[i] = new_list();
    }

    printf(" \b");

    int row = 0;
    int direction = 1; // going up or going down

    for(int i = 0; plain_text[i] != '\0'; i++){
        insert_end(matrix[row], plain_text[i]);
        if(row == 0){
            direction = 1;
        }
        else if(row == depth - 1){
            direction = -1;
        }
        row += direction;
    }

    int pt_len = strlen(plain_text);
    char *cipher_text = (char*)malloc(sizeof(pt_len));

    int counter = 0;
    node_t *ptr;
    for(int i = 0; i < depth; i++) {
        ptr = matrix[i]->head;

        while(ptr != NULL){
            cipher_text[counter] = ptr->val;
            counter++;
            ptr = ptr->next;
        }

        free_list(matrix[i]);
    }

    cipher_text[counter] = '\0';
    return cipher_text;
}

int main(int argc, char **argv) {
    if(argc < 3){
        printf("USAGE: cipher <plain-text> <depth>\n");
        return EXIT_FAILURE;
    }
    printf("Cipher text: %s\n", cipher(argv[1], atoi(argv[2])));
    return EXIT_SUCCESS;
}