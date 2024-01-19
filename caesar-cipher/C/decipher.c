#include <stdio.h>

void decipher(char *str, int key) {
    // iterating over characters
    for(int i = 0; str[i] != '\0'; i++){
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
            str[i] = 'A' + original_char;
        }else{
            int index = c - 'a';
            int original_char = index - key;
            if(original_char < 0) {
                original_char = 26 - (original_char * -1);
            }
            str[i] = 'a' + original_char;
        }
    }
}

int main() {
    char str[1024];
    int k;

    printf("Enter cipher text (string): ");
    scanf("%s", str);

    printf("Enter key (int): ");
    scanf("%d", &k);

    decipher(str, k);

    printf("Plain text: %s\n", str);

    return 0;
}