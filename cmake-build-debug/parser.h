//
// Created by hp on 28-Oct-22.
//

#ifndef DICTIONARYPROJECT_PARSER_H
#define DICTIONARYPROJECT_PARSER_H

#include "LLD.h"
#include "tst node.h"
#include "trie.h"
int File_parser();
//Trie
void insertall(t_ht_list *,  t_ht_list * ,t_ht_list *);
t_ht_list * randomgenerator(Node*);
int menu_real();
void autocomplete(Node* , p_cell );
int search_tree(int);
void print_tree();
void model_one_two();

void extract_randomword();

#endif //DICTIONARYPROJECT_PARSER_H
