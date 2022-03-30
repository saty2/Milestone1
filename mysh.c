#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include  <ctype.h>
#include "variables.h"
#include "builtins.h"
#include "io_helpers.h"

int main(int argc, char* argv[]) {
    char *prompt = "mysh$ "; // TODO Step 1, Uncomment this.

    char input_buf[MAX_STR_LEN + 1];
    input_buf[MAX_STR_LEN] = '\0';
    char *token_arr[MAX_STR_LEN] = {NULL};
    int var_count = 0;


    while (1) {
        // Prompt and input tokenization


        // TODO Step 2:
        // Display the prompt via the display_message function.
        display_message(prompt);


        int ret = get_input(input_buf);
        size_t token_count = tokenize_input(input_buf, token_arr);
        //display_message(token_arr[0]);
        //display_message(token_arr[1]);
        //display_message(token_arr[2]);
        
        // Clean exit
        if (ret != -1 && (token_count == 0 || ((strncmp("exit", token_arr[0], 4) == 0))) && ret != 1) {
            node h;
            h = gethead();
            node curr;
            while((curr = h) != NULL){
                h = h->next;
                free(curr);
            }
            free(h);
            
            break;
        }
        char *empy = "|";

        // Command execution
        if (token_count >= 1) {
            bn_ptr builtin_fn = check_builtin(token_arr[0]);
            if(token_count > 2 && strcmp(token_arr[2], empy) == 0){
     int fd[2];
     if(pipe(fd) == -1){
         display_message("Sorry,Unable To Open Pipe :( \n");

     }

     int pid1 = fork();
     if(pid1 < 0){
         perror("Fork is not working Us Do SomeThing Buddy");
     } else if (pid1 == 0) {
         dup2(fd[1], STDOUT_FILENO);
         if(close(fd[0]) == -1){
             perror("clse1");
         }
        ssize_t err = builtin_fn(token_arr);
        if (err == - 1) {
            display_error("ERROR: Builtin failed: ", token_arr[0]);
        }
        if(close(fd[1]) == -1){
            perror("close2");
        }
     }
    //  close(fd[0]);
    //  close(fd[1]);

     int m[2];
     if(pipe(m) == -1){
         display_message("Sorry,Unable To Open Pipe :( \n");

     }
    //  int pid2 = fork();
    //  if(pid2 < 0){
    //      perror("Fork is SomeThing Buddy");
    //  } else{
         dup2(m[0], STDIN_FILENO);
         if(close(m[1]) == -1){
             perror("close3");
         }
         bn_ptr builtin_fn = check_builtin(token_arr[3]);
         ssize_t err = builtin_fn(token_arr);
        if (err == - 1) {
            display_error("ERROR: Builtin failed: ", token_arr[0]);
        }
        if(close(m[0]) == -1){
            perror("close 4");
        }
    //  if(close(fd[0]) == -1){
    //      perror("close5");
    //  }
    //  if(close(fd[1]) == -1){
    //      perror("close6");
    //  }
    //  if(close(m[0]) == -1){
    //      perror("close7");
    //  }
    //  if(close(m[1]) == -1){
    //      perror("close8");
    //  }

    //  waitpid(pid1,NULL, 0);
    //  waitpid(pid2,NULL, 0);
     // waitpid(pid1,NULL, 0);
            } else if (builtin_fn != NULL) {
                ssize_t err = builtin_fn(token_arr);
                if (err == - 1) {
                    display_error("ERROR: Builtin failed: ", token_arr[0]);
                }
             
        } else if(token_count == 1){
            char *in_ptr = token_arr[0];
            char *curr_ptr = strtok (in_ptr, "=");
            token_count = 0;
            token_arr[0] =  NULL;

        while (curr_ptr != NULL) {  // TODO: Fix this
            // TODO: Fix this
            token_arr[token_count] = curr_ptr;
            curr_ptr = strtok(NULL, "=");
            token_count += 1;       
            }
    
            token_arr[token_count] = NULL;
            if(token_count==2){
                make_variable(token_arr[0],token_arr[1], var_count);
                var_count +=1;
            } else{
            display_error("ERROR: Unrecognized command: ", token_arr[0]);
            }
        } else {
                    display_error("ERROR: Unrecognized command: ", token_arr[0]);
            }
        }
    }



    return 0;
}
