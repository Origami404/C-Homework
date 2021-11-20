#include <stdio.h>
#include <string.h>

int main() {
    char password[] = "secret";
    char userInput[81];

    printf("Input password: ");
    scanf("%s", userInput);

    if (strcmp(userInput, password) == 0) { // strcmp(userInput, password) == 0
        printf("Correct passward! Welcome to the system...\n");
    } else if (strcmp(userInput, password) < 0) { // strcmp(userInput, password) < 0
        printf("Invaild password! user input < password\n");
    } else {
        printf("Invaild password! user input < password\n");
    }
    
    return 0;
}