#include <stdio.h>
#include <string.h>

int main() {
    char secretword[20];
    sprintf(secretword, "Melancia");

    int won = 0;
    int lost = 0;

    do{
        char try;
        scanf("%c", &try);

        for(int i = 0; i < strlen(secretword); i++)
            if(secretword[i] == try) {
                printf("The position %d has this letter!\n", i);
            }



    } while (!won && !lost);
    
}