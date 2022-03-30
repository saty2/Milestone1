
#define __variables_H__
#include <string.h>
#include "io_helpers.h"

#include <sys/types.h>

struct LinkedList{
    char name[64];
    char value[64];
    struct LinkedList *next;
 };

typedef struct LinkedList *node;

int make_variable(char *valu, char *nme, int c);
void addNode(node h, char *vale, char *nme);
node createNode();
node gethead();