//
// Created by hp on 28-Oct-22.
//

#include "tst node.h"
#include "LLD.h"
//global variable typelist that is a t_ht_list pointer
t_ht_list * typelistt=NULL;
// create ternary search tree for the base form
Node* create_base_tst(char data)
{
    Node* temp = (Node*) malloc(sizeof(Node ));
    temp->data = data;
    temp->inflictedno = 0;
    temp->left = temp->mid_eq = temp->right=NULL;
    temp->pointer=NULL;
    return temp;
}


// Recursive Function to insert to baseTree a new ptr_word in a Ternary Search Tree returns the last node of word
Node* insert_to_baseTree(Node** root, p_cell ptr_word)
{    // Base Case: Tree is empty
    if (!(*root))
        *root = create_base_tst(ptr_word->value);
    else if(!(*root)->data)
        (*root)->data=ptr_word->value;
    // If ptr_word->value is < than (*root)->data,
    // then insert_to_baseTree this ptr_word in (*root)->left
    if ((ptr_word->value) < (*root)->data)
        insert_to_baseTree(&((*root)->left), ptr_word);
        // If ptr_word->value is > than (*root)->data,
        // then insert_to_baseTree this ptr_word in (*root)->right)
    else if ((ptr_word->value) > (*root)->data)
        insert_to_baseTree(&((*root)->right), ptr_word);
        // If ptr_word->value of ptr_word is == as root's character,
    else {if (ptr_word->next)
            insert_to_baseTree(&((*root)->mid_eq), ptr_word->next);
            // the last letter of the ptr_word
        else{
            (*root)->inflictedno++;
            //since all base forms has inflicted forms in the dictionary check if the inflicted tree pointer is not null
            //else create new inf_tree with no values(to be determined in the other func)
            if(!(*root)->pointer){
                (*root)->pointer = (inf_Node*) malloc(sizeof(inf_Node ));
                (*root)->pointer->end_of_word = 0;
                (*root)->pointer->left = (*root)->pointer->mid_eq = (*root)->pointer->right=NULL;
                (*root)->pointer->pointer=NULL;
            } return (*root);
        }
    }
}

// A recursive function to traverse Ternary Search Tree
void traverseTSTUtil(Node* root, char* buffer, int depth)
{
    if (root)
    {
        // First traverse the left subtree
        traverseTSTUtil(root->left, buffer, depth);

        // Store the character of this node
        buffer[depth] = root->data;
        if (root->inflictedno)
        {
            buffer[depth+1] = '\0';
            printf( "%s\n", buffer);
        }

        // Traverse the subtree using mid_eq pointer (middle subtree)
        traverseTSTUtil(root->mid_eq, buffer, depth + 1);

        // Finally Traverse the right subtree
        traverseTSTUtil(root->right, buffer, depth);
    }
}

// The main function to traverse a Ternary Search Tree.
// It mainly uses traverseTSTUtil()
void traverseTST(Node* root)
{
    char buffer[MAX];
    if(root!=NULL)
        traverseTSTUtil(root, buffer, 0);
}

// A recursive function to traverse Ternary Search Tree
void traverseinfTSTUtil(inf_Node * root, char* buffer, int depth)
{
    if (root)
    {
        // First traverse the left subtree
        traverseinfTSTUtil(root->left, buffer, depth);

        // Store the character of this node
        buffer[depth] = root->data;
        if (root->end_of_word)
        {
            buffer[depth+1] = '\0';
            printf( "%s\n", buffer);
        }

        // Traverse the subtree using mid_eq pointer (middle subtree)
        traverseinfTSTUtil(root->mid_eq, buffer, depth + 1);

        // Finally Traverse the right subtree
        traverseinfTSTUtil(root->right, buffer, depth);
    }
}

// The main function to traverse a Ternary Search Tree.
// It mainly uses traverseTSTUtil()
void traverseinfTST(inf_Node * root)
{
    char buffer[MAX];
    if(root!=NULL)
        traverseinfTSTUtil(root, buffer, 0);
}


// Function to search a given word in TST
int searchTST(Node *root, p_cell word)
{
    if (!root)
        return 0;

    if (word->value < (root)->data)
        return searchTST(root->left, word);

    else if (word->value > (root)->data)
        return searchTST(root->right, word);

    else
    {
        if (!(word->next)){

            return root->inflictedno;}

        return searchTST(root->mid_eq, word->next);
    }
}

//create tree for the inflicted node
inf_Node* create_inflicted_tst(char data)
{
    inf_Node * temp = (inf_Node*) malloc(sizeof(inf_Node ));
    temp->data = data;
    temp->end_of_word=0;
    temp->left = temp->mid_eq = temp->right=NULL;
    temp->pointer=NULL;
    return temp;
}


inf_Node *insertinffromlist(inf_Node ** root, p_cell word,t_ht_list * typelist){
        typelistt=typelist;
    return (*insert_to_inflicted_tree(root, word));
}
inf_Node ** insert_to_inflicted_tree(inf_Node ** root, p_cell word)
{
    // Base Case: Tree is empty
    if (!(*root))
        *root = create_inflicted_tst(word->value);
    else if(!(*root)->data)
        (*root)->data=word->value;
    // If current character of word is smaller than root's character,
    // then insert_to_baseTree this word in left subtree of root
    if ((word->value) < (*root)->data)
        insert_to_inflicted_tree(&((*root)->left), word);

        // If current character of word is greater than root's character,
        // then insert_to_baseTree this word in right subtree of root
    else if ((word->value) > (*root)->data)
        insert_to_inflicted_tree(&((*root)->right), word);

        // If current character of word is same as root's character,
    else {
        if (word->next)
            insert_to_inflicted_tree(&((*root)->mid_eq), word->next);

            // the last character of the word
        else{
            (*root)->end_of_word++;
            if(!(*root)->pointer){
                ((*root)->pointer)= create_inftype(typelistt);
            }

            return root;
        }
    }

}
//creates an inflicted type data structure
inf_Type * create_inftype(t_ht_list * typelist){
    inf_Type * temp= (inf_Type*)malloc(sizeof(inf_Type));
    p_cell tempo=typelist->head;
    while(tempo&&!(temp->PL_SG&&temp->gender)){
        switch (tempo->value) {
            case 'P':
                if(tempo->next&&tempo->next->value=='L')
                    temp->PL_SG='P';
                break;
            case 'S':
                if(tempo->next&&tempo->next->value=='G')
                    temp->PL_SG='S';
                break;
            case 'M':
                temp->gender='M';
                break;
            case 'F':
                if(tempo->next&&tempo->next->value=='e')
                    temp->gender='F';
                break;
            default:
                break;

        }
        tempo=tempo->next;
    }
    if(!temp->PL_SG)
        temp->PL_SG='B';
    if(!temp->gender)
        temp->gender='B';
    return temp;

}


