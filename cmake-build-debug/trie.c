//
// Created by hp on 29-Oct-22.
//
/*
#include "trie.h"

// C implementation of search and insert_to_baseTree operations
// on Trie
#include <stdio.h>
#include <stdlib.h>


// Returns new trie node (initialized to NULLs)
TrieNode *createtrienode()
{
    TrieNode *pNode = NULL;
    pNode = (TrieNode *)malloc(sizeof(TrieNode));
    //pNode->trielist=createnodelist();
    pNode->head=NULL;
    pNode->isEndOfWord=0;
    return pNode;
}

// If not present, inserts key into trie
// If the key is prefix of trie node, just marks leaf node
TrieNode * insertriefromlist(TrieNode * root, t_ht_list word){

    TrieNode *ptr_trie=root;
    p_cell temp=word.head;
    int endoflist=0;
    while(!endoflist){

        if(temp->next==NULL){
           // printf("\nreached here2 baaaaaaaaaaaaaaaaaa\n");
            endoflist=1;
            insertrie(&ptr_trie,temp,endoflist);}
        else{

            ptr_trie= insertrie(&ptr_trie,temp,endoflist);
            printf("\nans--->%c\n",temp->value);
            //printf("\n->>>>>>>>>%c\n",root->head->value);
            //printf("\nreached here3\n");
            temp=temp->next;}
    }
    printf("finallly does it work?%d/n",ptr_trie->head==NULL);
    return ptr_trie;
}
Trie_cell createTrieCell(char val){
    Trie_cell  temp = (Trie_cell) malloc(sizeof(struct trie_cell));
    temp->value = val;
    temp->next =NULL;
   // temp->child=NULL;
    return temp;
}
TrieNode * insertrie(TrieNode ** root, p_cell word,int i)
{
    Trie_cell temp=(*root)->head;
    Trie_cell prev;
    //printf("\nreached here is it%d \n",);
    while (temp!=NULL&&temp->value<word->value){

        prev=temp;
        temp=temp->next;
    }
    if(temp==NULL) {
        printf("\nreached here34 \n");
        temp=createTrieCell(word->value);
        root->head=temp;]
        if(i){
            (*root)->isEndOfWord=1;
            return NULL;}
        return temp->child=createtrienode();
    }
    else if(temp->value!=word->value){
        *(prev->next)= *(createTrieCell(word->value));
        *prev->next->next=*temp;
        if(i){
            (*root)->isEndOfWord=1;
            return NULL;}
        return prev->next->child=createtrienode();
    }
    else{
        if(i){
            (*root)->isEndOfWord=1;
            return NULL;}
        return temp->child=createtrienode();}

}
void displaytrieList(TrieNode t){
    Trie_cell temp=t.head;
    printf("list [head @-]");
    if(temp!=NULL){
        do {
            printf("-->[ %c | @-]",temp->value);
            temp=temp->next;
        }while(temp!=NULL);
    }


    printf("-->NULL\n");
}

// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;

    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl->isEndOfWord);
}*/