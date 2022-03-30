#include <string.h>
#include <stdlib.h>
#include "variables.h"
#include <string.h>




node head;// saves the head for the first time

int make_variable(char *valu, char *nme, int c){
    node checker;
    checker = head;
    while (checker != NULL)
        {
            if(checker->name == valu){
                strncpy(checker->value, nme,sizeof(checker->value));
                return 0; 
            }
            checker = checker->next;
        }
    if(c == 0){
        head = createNode();
        strcpy(head->name, nme);
        strcpy(head->value, valu);
    } else{
        addNode(head, valu, nme);
    }
    return 0;  

}


node createNode(){
    node a; 
    a = (node)malloc(sizeof(struct LinkedList));
    a->next = NULL;
    return a;
}

void addNode(node h, char *vale, char *nmee){
    node t,a;
    t = createNode();
    strcpy(t->name, nmee);
    strcpy(t->value, vale); 
    a  = h;
    while(a->next != NULL){
        a = a->next;
    }
        a->next = t;
    }

node gethead(){
    return head;
}