//
// Created by hp on 28-Oct-22.
//
#include <stdio.h>
#include <stdlib.h>


#define MAX 50
#ifndef DICTIONARYPROJECT_TST_NODE_H
#define DICTIONARYPROJECT_TST_NODE_H
#include "LLD.h"
// C program to demonstrate Ternary Search Tree (TST) insert_to_baseTree, traverse
// and search operations

typedef struct inf_type
{
    // a character 'M' if Masculine, 'F' if Feminine, 'B' if Both
    char gender;
    // a character 'P' if Plural, 'S' if Singular, 'B' if Both
    char PL_SG;
}inf_Type ;

// same sturcture as the base tree but the pointer variable will point to inf_Type
typedef struct inf_node
{
    char data;
    // True if this character is last character of one of the words
    int end_of_word;
    struct inf_type * pointer;
    struct inf_node *left, *mid_eq, *right;
}inf_Node ;
// A node of ternary search tree
typedef struct node
{
    char data;

    // True if this character is last character of one of the words
    //and also acts as a count of the number of inflicted words in the inflicted tree
    int inflictedno;
    //pointer to the forme flechir
    inf_Node * pointer;
    struct node *left, *mid_eq, *right;
}Node ;





// A utility function to create a new ternary search tree node
Node* newNode(char );
Node * insert_to_baseTree(Node **root, p_cell ptr_word);
void traverseTSTUtil(Node* , char* , int );
void traverseinfTSTUtil(inf_Node * , char* , int );
void traverseTST(Node* );
void traverseinfTST(inf_Node * );
int searchTST(Node *, p_cell);
inf_Type * create_inftype(t_ht_list *);
inf_Node ** insert_to_inflicted_tree(inf_Node **root, p_cell word);
inf_Node* create_inflicted_tst(char );
inf_Node *insertinffromlist(inf_Node **, p_cell,t_ht_list *);
#endif //DICTIONARYPROJECT_TST_NODE_H
