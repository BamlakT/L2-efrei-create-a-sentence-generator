//
// Created by hp on 01-Nov-22.
//
/*
#include <malloc.h>
#include <stdio.h>
#include "flecher_tst.h"
#include "tst node.h"


Fle_Node* newFle_Node(char data)
{
    Fle_Node* temp = (Fle_Node*) malloc(sizeof(Fle_Node ));
    temp->data = data;
    temp->inflictedno = 0;
    temp->left = temp->eq = temp->right =NULL;
    return temp;
}
t_ht_list *  Fle_Node_insert(Fle_Node ** root, p_cell word)
{
    // Base Case: Tree is empty
    if (!(*root))
        *root = newFle_Node(word->value);

    // If current character of word is smaller than root's character,
    // then insert this word in left subtree of root
    if ((word->value) < (*root)->data)
        Fle_Node_insert(&((*root)->left), word);

        // If current character of word is greater than root's character,
        // then insert this word in right subtree of root
    else if ((word->value) > (*root)->data)
        Fle_Node_insert(&((*root)->right), word);

        // If current character of word is same as root's character,
    else {
        if (word->next)
            Fle_Node_insert(&((*root)->eq), word->next);

            // the last character of the word
        else{
            (*root)->inflictedno = 1;
            return (*root)->pointer=createlist();
        }
    }

}

// A recursive function to traverse Ternary Search Tree
void traverseFle_NodeUtil(Fle_Node* root, char* buffer, int depth)
{
    if (root)
    {
        // First traverse the left subtree
        traverseFle_NodeUtil(root->left, buffer, depth);

        // Store the character of this node
        buffer[depth] = root->data;
        if (root->inflictedno)
        {
            buffer[depth+1] = '\0';
            printf( "%s\n", buffer);
        }

        // Traverse the subtree using equal pointer (middle subtree)
        traverseFle_NodeUtil(root->eq, buffer, depth + 1);

        // Finally Traverse the right subtree
        traverseFle_NodeUtil(root->right, buffer, depth);
    }
}

// The main function to traverse a Ternary Search Tree.
// It mainly uses traverseTSTUtil()
void traverseFle_NodeTST(Fle_Node* root)
{
    char buffer[MAX];
    if(root!=NULL)
        traverseTSTUtil(root, buffer, 0);
}

// Function to search a given word in TST
int searchFle_NodeTST(Fle_Node *root, p_cell word)
{
    if (!root)
        return 0;

    if (word->value < (root)->data)
        return searchFle_NodeTST(root->left, word);

    else if (word->value > (root)->data)
        return searchFle_NodeTST(root->right, word);

    else
    {
        if (!(word->next)){

            return root->inflictedno;}

        return searchFle_NodeTST(root->eq, word->next);
    }
}

*/