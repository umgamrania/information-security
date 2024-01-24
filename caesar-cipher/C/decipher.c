#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *decipher(char *str, int key) {

    int ct_len = strlen(str);
    char *plain_text = (char*)malloc(ct_len * sizeof(char));

    // iterating over characters
    for(int i = 0; ct_len; i++){
        char c = str[i];

        // processing capital and small letters seperately
        if(c >= 'A' && c <= 'Z'){
            // subtracting A will give character index, e.g. 0 for A, 1 for B, ...
            int index = c - 'A';
            int original_char = index - key;

            // Cycling back to start
            // If Z was in plain text, with key = 3, its cipher would be C,
            // So the plain text for C, should give Z
            if(original_char < 0) {
                // If original char is negative, it means the plain text near the end
                original_char = 26 - (original_char * -1);
            }
            plain_text[i] = 'A' + original_char;
        }else{
            int index = c - 'a';
            int original_char = index - key;
            if(original_char < 0) {
                original_char = 26 - (original_char * -1);
            }
            plain_text[i] = 'a' + original_char;
        }
    }

    return plain_text;
}

int main(int argc, char **argv) {

    if(argc < 3){
        printf("USAGE: <cipher-text> <key>\n");
        return EXIT_FAILURE;
    }

    char *plain_text = decipher(argv[1], atoi(argv[2]));
    printf("Plain text: %s\n", plain_text);

    return 0;
}