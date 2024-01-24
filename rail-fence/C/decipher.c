#include <stdio.h>
#include <string.h>
#include <math.h>
#include "linked_list.h"

char *decipher(char *cipher_text, int depth) {
    int ct_len = strlen(cipher_text);
    int tick_size = (2 * depth) - 2;
    int p = floor(ct_len / tick_size);
    int r = ct_len % tick_size;

    int element_count[depth];
    element_count[0] = p;
    element_count[depth - 1] = p; // last element

    if(r > depth) {
        element_count[0]++;
        element_count[depth-1]++;
    }

    for(int i = 1; i < depth - 1; i++) {
        element_count[i] = p * 2;
    }

    if(r > depth) {
        int i = depth - 2;
        while(i > r - depth) {
            element_count[i]++;
            i--;
        }
    }

    int i = 0;
    while(i < (r < depth ? r : depth)) {
        element_count[i]++;
        i++;
    }

    int indices[depth];
    indices[0] = 0;
    int total = 0;
    for(int i = 0; i < depth - 1; i++) {
        indices[i+1] = total + element_count[i];
        total += element_count[i];
    }

    char *pt = (char*)malloc(sizeof(char) * ct_len);
    i = 0;
    int direction = 1;

    int pt_index = 0;
    while(pt_index < ct_len) {
        int index = indices[i];
        pt[pt_index++] = cipher_text[index];
        indices[i]++;

        if(i == 0)
            direction = 1;
        else if(i == depth - 1)
            direction = -1;
        i += direction;
    }

    pt[pt_index] = '\0';

    return pt;
}

int main(int argc, char **argv) {
    printf("%s\n", decipher(argv[1], atoi(argv[2])));
}