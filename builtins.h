#ifndef __BUILTINS_H__
#define __BUILTINS_H__
#include <unistd.h>


/* Type for builtin handling functions
 * Input: Array of tokens
 * Return: >=0 on success and -1 on error
 */
struct stack{
    char data[1000];
    struct stack *next;
};
void push(char *a);
void pop();


typedef ssize_t (*bn_ptr)(char **);
ssize_t bn_echo(char **tokens);
ssize_t bn_cd(char **tokens);
ssize_t bn_cat(char **tokens);
ssize_t bn_wc(char **tokens);
size_t tokenize_for_me_baby(char *in_ptr, char **t);
/* Return: index of builtin or -1 if cmd doesn't match a builtin
 */
bn_ptr check_builtin(const char *cmd);


/* BUILTINS and BUILTINS_FN are parallel arrays of length BUILTINS_COUNT
 */
static const char * const BUILTINS[] = {"echo", "cat",  "cd", "wc"};
static const bn_ptr BUILTINS_FN[] = {bn_echo,bn_cat,bn_cd,bn_wc, NULL};    // Extra null element for 'non-builtin'
static const size_t BUILTINS_COUNT = sizeof(BUILTINS) / sizeof(char *);

#endif
