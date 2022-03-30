#include <string.h>
#include <stdlib.h>
#include "variables.h"
#include "builtins.h"
#include "io_helpers.h"
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#define STDIN_FILENO 0

struct stack *tpe = NULL;

void push(char *a){
    if(tpe == NULL){
        struct stack *chu = NULL;
        strcpy(chu->data, a);
        chu->next = NULL;
        tpe = chu; 
    } else{
        struct stack *tmp = NULL;
        strcpy(tmp->data, a);
        while(tpe->next != NULL){
            tpe = tpe->next;
        }
        tpe->next = tmp;

    }
}

void pop(){
    if (tpe == NULL){
        display_message("Base Directory Reached");
    }else
    {
        while(tpe->next->next != NULL){
            tpe = tpe->next;
        }
        tpe->next = NULL;
        
    }
    
}

// ====== Command execution =====

/* Return: index of builtin or -1 if cmd doesn't match a builtin
 */
bn_ptr check_builtin(const char *cmd) {
    ssize_t cmd_num = 0;
    while (cmd_num < BUILTINS_COUNT &&
           strncmp(BUILTINS[cmd_num], cmd, MAX_STR_LEN) != 0) {
        cmd_num += 1;
    }
    return BUILTINS_FN[cmd_num];
}


// ===== Builtins =====

/* Prereq: tokens is a NULL terminated sequence of strings.
 * Return 0 on success and -1 on error ... but there are no errors on echo. 
 */
ssize_t bn_echo(char **tokens) {
    ssize_t index = 1;
    int d = 0;
    while(tokens[index] != NULL){
    node z;
    z = gethead();
    
    if (tokens[index] != NULL) {
        // TODO:
        // Implement the echo command
        char a[10];
        strcpy(a,"$");
        while (z != NULL){
            strcat(a, z->value);
            if (strcmp(tokens[index], a) == 0){
                display_message(z->name);
                display_message("");
                d += 1;
            }
            z = z-> next;
            strcpy(a,"$");
            

        }
        
        
    }
    index +=1;
    }
    if(d != 0){
        display_message("\n");
        return 0;
    }
    index = 1;
    while (tokens[index] != NULL) {
        // TODO:
        // Implement the echo command
        display_message(tokens[index]);
        display_message(" ");
        index += 1;
    }
    display_message("\n");

    return 0;
}

ssize_t bn_cd(char **tokens){
    if(tokens[1] == NULL){
        display_message("ERROR: No input source provided");
        return 0;
    }
    if(strcmp(tokens[1], "../..") == 0 || strcmp(tokens[1], "...") == 0){
        char nme[1000];
        getwd(nme);
        char rand = '/';
        int counter = strlen(nme) - 1;
        while (nme[counter] != rand)
        {
            counter -= 1;
        }
        char new_nme[1000];
        int upto_counter = 0;
        while(upto_counter != counter){
            new_nme[upto_counter] = nme[upto_counter];
            upto_counter += 1;
        }
        if (chdir(new_nme) == -1){
            display_message("Sorry, unable to change");
        }
        
        display_message(nme);
        display_message("\n");
        display_message(new_nme);
        display_message("    ");
        //printf("%c", nme[58]);
        //printf("%lu", strlen(nme));
        // char *new_pt = NULL;
        // new_pt = nme;
        // char **t = NULL;
        // tokenize_for_me_baby(new_pt, t);
    }else if(strcmp(tokens[1], "../../..") == 0 || strcmp(tokens[1], "....") == 0){
        char nme[1000];
        getwd(nme);
        char rand = '/';
        int counter = strlen(nme) - 1;
        int bklash_counter = 0;
        while (bklash_counter != 2)
        {
            if(nme[counter] == rand){
                bklash_counter += 1;
            }
            counter -= 1;
        }
        char new_nme[1000];
        int upto_counter = 0;
        while(upto_counter != counter){
            new_nme[upto_counter] = nme[upto_counter];
            upto_counter += 1;
        }
        if (chdir(new_nme) == -1){
            display_message("Sorry, unable to change");
        }
    }else if(chdir(tokens[1]) == -1){
        display_message("ERROR: Invalid path \n");
        return 0;
    } else{
        display_message("Diectory changed");
    }
    return 0;

}

size_t tokenize_for_me_baby(char *in_ptr, char **t) {
    // TODO, uncomment the next line.
    char *curr_ptr = strtok (in_ptr, "/");
    size_t token_count = 0;

    while (curr_ptr != NULL) {  // TODO: Fix this
        // TODO: Fix this
        t[token_count] = curr_ptr;
        curr_ptr = strtok(NULL, "/");
        t += 1;       
    }
    
    t[token_count] = NULL;
    return token_count;
}

ssize_t bn_cat(char **tokens){
    if(tokens[1] == NULL){
        display_message("ERROR: No input source provided");
        return 0;
    }
    FILE *fe;
    if(sizeof(tokens) >= 3){
        char buf[10];
        while (read(STDIN_FILENO, buf, 10)){
            printf("%s", buf);
        }
        return 0;
        
    } else {
    fe = fopen(tokens[1], "r");
    perror("Came to < 3 part \n");
    }
    if(fe == NULL){
        display_message("ERROR: Cannot open file \n");
        return 0;
    }
    char line[150];
    while(fgets(line, 150, fe) != NULL){
        printf("%s", line);
    }
    fclose(fe);
    return 0;


}


ssize_t bn_wc(char **tokens){
    int charac_count = 0;
    int space_counter = 0;
    int words = 0;
    int line_counter = 0;
    // display_message(tokens[0]);
    // display_message(tokens[1]);
    //display_message(tokens[3]);
    // display_message("\n");
    if(tokens[1] == NULL){
        display_message("ERROR: No input source provided");
        return 0;
    }
    FILE *fe;
    if(tokens == NULL){
        fe = STDIN_FILENO;
    } else {
        fe = fopen(tokens[1], "r");
    }
    if(fe == NULL){
        display_message("ERROR: Cannot open file \n");
        return 0;
    }
    char line = ' ';
    char emp = ' ';
    while(line != EOF){
        line = fgetc(fe);
        if(line == emp){
            space_counter += 1;

        } else {
            charac_count += 1;
        }

    }
    fclose(fe);
    FILE *new_fe;
    if(tokens == NULL){
        new_fe = STDIN_FILENO;
    } else{
    new_fe = fopen(tokens[1], "r");
    }
    char abc[60];
    while (fscanf(new_fe, "%[^\n ] ", abc) != EOF){
        words += 1;
    }
    fclose(new_fe);

    FILE *hi_fe;
    if(tokens == NULL){
        hi_fe = STDIN_FILENO;
    } else{
    hi_fe = fopen(tokens[1], "r");
    }
    char wrd[300];
    while (fgets(wrd,sizeof(wrd), hi_fe) != NULL){
        line_counter += 1;
    }
    fclose(hi_fe);

    // display_message("word count  ");
    // char *shru = NULL;
    // sprintf(shru, "%d", words);
    // display_message(shru);
    // display_message("\n");
    // display_message("character count  ");
    // char *shrut = NULL;
    // sprintf(shrut, "%d",charac_count);
    // display_message(shrut);
    // display_message("\n");
    // display_message("newline count  ");
    // char *shruti = NULL;
    // sprintf(shruti, "%d", line_counter);
    // display_message(shruti);
    // display_message("\n");
    char beyou[200];
    sprintf(beyou, " word count %d \n character count %d \n newline count %d \n", words, charac_count, line_counter);
    display_message(beyou);
    display_message(" ");
    return 0;

 }
