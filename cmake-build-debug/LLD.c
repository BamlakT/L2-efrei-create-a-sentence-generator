#include <stdio.h>
#include <stdlib.h>
#include "LLD.h"

p_cell createCell(char val){
    p_cell  temp = (p_cell) malloc(sizeof(t_cell ));
    temp->value = val;
    temp->next =NULL;
    return temp;
}
t_ht_list* createlist(){
    t_ht_list* temp=(t_ht_list *) malloc(sizeof(t_ht_list ));
    temp->head=temp->tail=NULL;
    return temp;
}

void addTailHt(t_ht_list * list, char i){
    if(list->head== NULL ||list->tail== NULL){
        list->head=createCell(i);
        list->tail=list->head;
        list->head->next=NULL;
    }
    else{
        list->tail->next=createCell(i);
        list->tail=list->tail->next;
    }
    list->tail->next=NULL;
}
/* Function to delete the entire linked list */
void deleteList(p_cell * head_ref,p_cell * tail)
{
    /* deref head_ref to get the real head */
    p_cell  current = *head_ref;
    p_cell next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    /* deref head_ref to affect the real head back
       in the caller. */
    *head_ref = NULL;
    *tail=NULL;

}
void displayStdList(t_ht_list t){
    p_cell temp=t.head;
    printf("list [head @-]");
    if(temp!=NULL){
        do {
            printf("-->[ %c | @-]",temp->value);
            temp=temp->next;
        }while(temp!=NULL);
    }


    printf("-->NULL\n");
}


void displaytowordvoid(t_ht_list t){
p_cell temp=t.head;
if(temp!=NULL){
do {
printf("%c",temp->value);
temp=temp->next;
}while(temp!=NULL);
}
    printf(" ");

}
