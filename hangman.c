#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include<stdlib.h>
#include "hangman.h"

char secret_word[word_length];
char attempt[26];
int attempts_num = 0;

void welcome() {
    printf("\n\n");
    printf("*********************************\n");
    printf("**  Welcome to The Hangman Game **\n");
    printf("**********************************\n\n");
    printf("  ___________.._______         \n");
    printf(" | .__________))______|        \n");
    printf(" | | / /      ||               \n");
    printf(" | |/ /       ||               \n");
    printf(" | | /        ||.-''.          \n");
    printf(" | |/         |/  _  \\        \n");
    printf(" | |          ||  `/,|         \n");
    printf(" | |          (\\`_.'          \n");
    printf(" | |         .-`--'.           \n");
    printf(" | |        /Y . . Y\\         \n");
    printf(" | |       // |   | \\\\       \n");
    printf(" | |      //  | . |  \\\\      \n");
    printf(" | |     ')   |   |   (`       \n");
    printf(" | |          ||'||            \n");
    printf(" | |          || ||            \n");
    printf(" | |          || ||            \n");
    printf(" | |          || ||            \n");
    printf(" | |         /_| |_\\          \n");
    printf(" | |                           \n");
    printf(" |_|                         \n\n");
 

}

void read_attempt(){
    char letter;
    scanf(" %c", &letter);

    attempt[attempts_num] = letter;
    (attempts_num)++;
}

int already_attempted(char letter) {
    int found = 0;

    for(int j = 0; j < attempts_num; j++) {
        if(tolower(attempt[j]) == tolower(letter)) {
            found = 1;
            break;
        }
    }
    return found;
}

void show_game() {
    
        int wrong = wrong_attempt();

        printf("   _________       \n");
        printf("  |/        |      \n");
        printf("  |        %c%c%c  \n",  (wrong >= 1 ? '(' :' '),
                                         (wrong >= 1 ? '_' :' '),
                                         (wrong >= 1 ? ')' :' '));

        printf("  |        %c%c%c  \n", (wrong >= 2 ? '\\' :' '),
                                        (wrong >= 2 ? '|' :' '),
                                        (wrong >= 2 ? '/' :' '));

        printf("  |         %c    \n",  (wrong >= 3 ? '|' :' '));

        printf("  |        %c %c   \n", (wrong >= 4 ? '/' :' '),
                                        (wrong >= 4 ? '\\' :' '));
        printf(" _|____            \n");
        printf("                   \n");

        for(int i = 0; i < strlen(secret_word); i++) {
        int found = already_attempted(secret_word[i]);

        if(found) {
            printf("%c ", secret_word[i]);
        }else {
            printf("_ ");
        }
    }
}

void word_add() {

    char yes;
    printf("Do you want to add a new word to the database? (Y/N)");
    scanf(" %c", &yes);

    if(yes == 'Y') {
        char new_word[word_length];
        printf("What's the word? ");
        scanf("%s", new_word);

        FILE* f;
        f = fopen("words.txt", "r+");
        if( f == 0){
            printf("Sorry, database not available\n");
            exit(1);
        }

        int total_words;
        fscanf(f, "%d", &total_words);
        total_words++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", total_words);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", new_word);

        fclose(f);
    }
}

void word_choice() {
    FILE* f;
    f = fopen("words.txt", "r");
    if( f == 0){
        printf("Sorry, database not available\n");
        exit(1);
    }

    int num_words;
    fscanf(f, "%d", &num_words);

    srand(time(0));
    int random_num = rand() % num_words;

    for(int i = 0; i <= random_num; i++) {
        fscanf(f, "%s", secret_word);
    }

    fclose(f);
}

int wrong_attempt() {
    int wrong = 0;

    for(int i = 0; i < attempts_num; i++) {
        int in_word = 0;

        for(int j = 0; j < strlen(secret_word); j++) {
            if(attempt[i] == secret_word[j]){

                in_word = 1;
                break;
            }
        } 
        if(!in_word) wrong++;
    }
    return wrong;
}

int lose(){
 
    return wrong_attempt() >= 5;
    
}

int winn(){
    for(int i = 0; i < strlen(secret_word); i++) {
        if(!already_attempted(secret_word[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {

    word_choice();
    welcome();

    do{

        printf("\n");
        show_game();
        printf("\n\n");
        printf("Choice a letter.");
        printf("\n\n");
        read_attempt();

    } while (!winn() && !lose());

    if(winn()){
        printf(" __   __           __        ___             _           \n");
        printf(" \\ \\ / /__  _   _  \\ \\      / (_)_ __  _ __ | |      \n");
        printf("  \\ V / _ \\| | | |  \\ \\ /\\ / /| | '_ \\| '_ \\| |   \n");
        printf("   | | (_) | |_| |   \\ V  V / | | | | | | | |_|         \n");
        printf("   |_|\\___/ \\__,_|    \\_/\\_/  |_|_| |_|_| |_(_)      \n\n\n");
        printf(" The word was **%s**\n\n", secret_word);
                                                      
                                                                                       
    }else {
        printf(" __   __            _                _          \n");
        printf(" \\ \\ / /__  _   _  | | ___  ___  ___| |       \n");
        printf("  \\ V / _ \\| | | | | |/ _ \\/ __|/ _ \\ |     \n");
        printf("   | | (_) | |_| | | | (_) \\__ \\  __/_|       \n");
        printf("   |_|\\___/ \\__,_| |_|\\___/|___/\\___(_) \n\n\n");
        printf(" The word was **%s**\n\n", secret_word);
    }
    word_add();  
}