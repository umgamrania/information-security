#include <stdio.h>

void cipher(char *str, int key) {
    // iterating over characters
    for(int i = 0; str[i] != '\0'; i++){
        char c = str[i];

        // processing capital and small letters seperately
        if(c >= 'A' && c <= 'Z'){
            // subtracting A will give character index, e.g. 0 for A, 1 for B, ...
            int index = c - 'A';
            index = (index + key) % 26;
            str[i] = 'A' + index;
        }else{
            int index = c - 'a';
            index = (index + key) % 26;
            str[i] = 'a' + index;
        }
    }
}

int main() {
    char str[1024];
    int k;

    printf("Enter plain text (string): ");
    scanf("%s", str);

    printf("Enter key (int): ");
    scanf("%d", &k);

    cipher(str, k);

    printf("Cipher text: %s\n", str);

    return 0;
}