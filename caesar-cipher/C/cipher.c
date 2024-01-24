#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *cipher(char *str, int key) {
    int pt_len = strlen(str);
    char *cipher_text = (char*)malloc(sizeof(char) * pt_len);

    // iterating over characters
    for(int i = 0; i < pt_len; i++){
        char c = str[i];

        // processing capital and small letters seperately
        if(c >= 'A' && c <= 'Z'){
            // subtracting A will give character index, e.g. 0 for A, 1 for B, ...
            int index = c - 'A';
            index = (index + key) % 26;
            cipher_text[i] = 'A' + index;
        }else{
            int index = c - 'a';
            index = (index + key) % 26;
            cipher_text[i] = 'a' + index;
        }
    }

    return cipher_text;
}

int main(int argc, char **argv) {

    if(argc < 3){
        printf("USAGE: <plain-text> <key>\n");
        return EXIT_FAILURE;
    }

    char *cipher_text = cipher(argv[1], atoi(argv[2]));
    printf("Cipher text: %s\n", cipher_text);

    return EXIT_SUCCESS;
}