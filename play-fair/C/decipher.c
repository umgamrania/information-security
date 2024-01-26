#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "linked_list.h"

// Convert string to upper case
char *strupr(char *str) {
    int len = strlen(str);
    char *upr = (char*)malloc(len * sizeof(char));
    for(int i = 0; i < len; i++) {
        if(str[i] >= 'a' && str[i] <= 'z'){
            upr[i] = str[i] - 32;
        }
        else{
            upr[i] = str[i];
        }
    }

    return upr;
}

int strfind(char *str, char target) {
    int len = strlen(str);

    for(int i = 0; i < len; i++){
        if(str[i] == target){
            return i;
        }
    }
    return -1;
}

// Generates a string of non repeating characters
// with characters of the key being at the beginning
char *create_matrix(char *key) {
    /*
        We don't actually need "A MATRIX".
        Just a string of characters, we can find the index
        of the character, do some math and get its row and col
    */

    key = strupr(key);
    int len_key = strlen(key);

    // No matter the key size, the matrix is 5x5, 25 chars (ignoring J)
    char *buf = (char*)malloc(25 * sizeof(char));

    // An array for storing which characters have already
    // appeared in the string
    bool encountered[26] = {false};

    int buf_i = 0; // index for adding char to buffer
    // appending key characters
    for(int i = 0; i < len_key; i++) {
        if(key[i] == 'J'){
            continue;
        }

        int char_index = key[i] - 'A';

        if(!encountered[char_index]){
            // char not in buf
            buf[buf_i++] = key[i];
            encountered[char_index] = true;
        }
    }

    // appending rest of the characters
    for(int i = 0; i < 26; i++) {
        if('A' + i == 'J'){
            continue;
        }
        if(!encountered[i]){
            // char not in buf
            buf[buf_i++] = 'A' + i;
            encountered[i] = true;
        }
    }
    buf[buf_i] = '\0';

    return buf;
}

linked_list_t *create_pairs(char *cipher_text) {
    cipher_text = strupr(cipher_text);
    int len_pt = strlen(cipher_text);
    linked_list_t *pairs = new_list();

    for(int i = 0; i < len_pt; /* nothing */) {
        char a = cipher_text[i];
        if(i == len_pt - 1) {
            // Last character, string has odd chars
            insert_end(pairs, a, 'X');
            break;
        }

        char b = cipher_text[i+1];

        if(a == b) {
            insert_end(pairs, a, 'X');
            i++;
        }
        else {
            insert_end(pairs, a, b);
            i += 2;
        }
    }

    return pairs;
}

char *decipher(char *cipher_text, char *key) {
    char *matrix = create_matrix(key);
    linked_list_t *pairs = create_pairs(cipher_text);

    char *plain_text = (char*)malloc(strlen(cipher_text) * sizeof(char));
    int index = 0; // index for cipher text string

    node_t *ptr = pairs->head;
    while(ptr != NULL) {
        char a = ptr->a;
        char b = ptr->b;

        int pos_a = strfind(matrix, a);
        int pos_b = strfind(matrix, b);
        
        int row_a = floor(pos_a / 5);
        int col_a = pos_a % 5;
        int row_b = floor(pos_b / 5);
        int col_b = pos_b % 5;

        if(row_a == row_b) {
            plain_text[index++] = matrix[(row_a * 5) + ((col_a - 1) % 5)];
            plain_text[index++] = matrix[(row_b * 5) + ((col_a - 1) % 5)];
        }
        else if(col_a == col_b) {
            plain_text[index++] = matrix[((row_a - 1) % 5) * 5 + col_a];
            plain_text[index++] = matrix[((row_b - 1) % 5) * 5 + col_a];
        }
        else {
            plain_text[index++] = matrix[(row_a * 5) + col_b];
            plain_text[index++] = matrix[(row_b * 5) + col_a];
        }

        ptr = ptr->next;
    }

    plain_text[index] = '\0';
    return plain_text;
}

int main() {
    printf("%s\n", decipher("SPOPPGKSOPPH", "hello"));
    return EXIT_SUCCESS;
}