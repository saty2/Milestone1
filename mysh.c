#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include  <ctype.h>

#include "builtins.h"
#include "io_helpers.h"




int main(int argc, char* argv[]) {
    char *prompt = "mysh$ "; // TODO Step 1, Uncomment this.

    char input_buf[MAX_STR_LEN + 1];
    input_buf[MAX_STR_LEN] = '\0';
    char *token_arr[MAX_STR_LEN] = {NULL};


    while (1) {
        // Prompt and input tokenization


        // TODO Step 2:
        // Display the prompt via the display_message function.
        display_message(prompt);


        int ret = get_input(input_buf);
        size_t token_count = tokenize_input(input_buf, token_arr);
        int a = 0;
        for(int y=0; y<token_count;y++){
            if(strncmp("*", token_arr[y], 1) == 0){
                a += 1;
            }
        }
        if(a == 1){
            char ch[100];
            int op_add = 0;
            for(int i = 0; i<token_count - 1;i++){
                if(strncmp(token_arr[i],"*",1) == 0){
                    op_add = i;
                }
                int x = atoi(token_arr[op_add + 1]);
                if(isdigit(x) == 1){
                    //int *num = token_arr[op_add+1];
                    memset(ch,atoi(token_arr[op_add - 1]), x);
                    printf("%s", ch);
                    if(sizeof(ch) > MAX_STR_LEN){
                        //display_message("ERROR: input line too long\n");
                        write(STDERR_FILENO, "ERROR: input line too long\n", strlen("ERROR: input line too long\n"));
                    }
                }
            }
        }

        // Clean exit
        if (ret != -1 && (token_count == 0 || ((strncmp("exit", token_arr[0], 4) == 0))) && ret != 1) {
            break;
        }

        // Command execution
        if (token_count >= 1) {
            bn_ptr builtin_fn = check_builtin(token_arr[0]);
            if (builtin_fn != NULL) {
                ssize_t err = builtin_fn(token_arr);
                if (err == - 1) {
                    display_error("ERROR: Builtin failed: ", token_arr[0]);
                }
            } else {
                display_error("ERROR: Unrecognized command: ", token_arr[0]);
            }
        }

    }

    return 0;
}
