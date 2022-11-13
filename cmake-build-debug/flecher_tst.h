//
// Created by hp on 01-Nov-22.
//
/*
#ifndef DICTIONARYPROJECT_FLECHER_TST_H
#define DICTIONARYPROJECT_FLECHER_TST_H
#define MAX 50
#include "LLD.h"
#include "tst node.h"

// A node of ternary search tree
typedef struct fle_node
{
    char data;

    // True if this character is last character of one of the words
    unsigned inflictedno: 1;
    t_ht_list * pointer;
    struct fle_node *left, *eq, *right;
}Fle_Node ;
Fle_Node* newFle_Node(char );
t_ht_list * Fle_Node_insert(Fle_Node** , p_cell);
void traverseFle_NodeUtil(Fle_Node* , char* , int );
void traverseFle_NodeTST(Fle_Node* );
int searchFle_NodeTST(Fle_Node *, p_cell);
#endif //DICTIONARYPROJECT_FLECHER_TST_H
*/