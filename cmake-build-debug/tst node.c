//
// Created by hp on 28-Oct-22.
//

#include "tst node.h"
#include "LLD.h"
//global variable typelist that is a t_ht_list pointer
t_ht_list * typelistt=NULL;
// create ternary search tree for the base form
Node* create_base_tst(char letter)
{
    Node* mynode = (Node*) malloc(sizeof(Node ));
    mynode->key = letter;
    mynode->left = mynode->mid_eq = mynode->right=NULL;
    mynode->pointer=NULL;

    mynode->inflictedno = 0;
    return mynode;
}


// Recursive Function to insert to baseTree a new ptr_word in a Ternary Search Tree returns the last node of word
Node* insert_to_baseTree(Node** root, p_cell ptr_word)
{    // Base Case: Tree is empty
    if (!(*root))
        *root = create_base_tst(ptr_word->value);
    else if(!(*root)->key)
        (*root)->key=ptr_word->value;
    // If ptr_word->value is < than (*root)->key,
    // then insert_to_baseTree this ptr_word in (*root)->left
    if ((ptr_word->value) < (*root)->key)
        insert_to_baseTree(&((*root)->left), ptr_word);
        // If ptr_word->value is > than (*root)->key,
        // then insert_to_baseTree this ptr_word in (*root)->right)
    else if ((ptr_word->value) > (*root)->key)
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
void base_recprint(Node* node_root, char* string, int height)
{
    if (node_root)
    {
        base_recprint(node_root->left, string, height);
        string[height] = node_root->key;
        if (node_root->inflictedno)
        {
            string[height + 1] = '\0';
            printf("%s\n", string);
        }
        else{

        }
        base_recprint(node_root->mid_eq, string, height + 1);
        base_recprint(node_root->right, string, height);
    }
}


// A recursive function to traverse Ternary Search Tree
void inf_printtree(inf_Node * node_root, char* string, int height)
{
    if (node_root)
    {
        //left tstsubtree
        inf_printtree(node_root->left, string, height);

        //obtain
        string[height] = node_root->key;
        if (node_root->end_of_word)
        {
            string[height + 1] = '\0';
            printf("%s\n", string);
        }
        inf_printtree(node_root->mid_eq, string, height + 1);
        //right tsttree
        inf_printtree(node_root->right, string, height);
    }
}




// Function to search a given ptr_wrd in TST
int findinbasetree(Node *node_root, p_cell ptr_wrd)
{
    if (!node_root)
        return 0;
    if (ptr_wrd->value < (node_root)->key)
        return findinbasetree(node_root->left, ptr_wrd);
    else if (ptr_wrd->value > (node_root)->key)
        return findinbasetree(node_root->right, ptr_wrd);
    else
    {
        if (!(ptr_wrd->next)){
            return node_root->inflictedno;}
        return findinbasetree(node_root->mid_eq, ptr_wrd->next);
    }
}

//create tree for the inflicted node
inf_Node* create_inflicted_tst(char data)
{
    inf_Node * temp = (inf_Node*) malloc(sizeof(inf_Node ));
    temp->key = data;
    temp->end_of_word=0;
    temp->left = temp->mid_eq = temp->right=NULL;
    temp->pointer=NULL;
    return temp;
}


inf_Node *insertinffromlist(inf_Node ** root, p_cell word,t_ht_list * typelist){
        typelistt=typelist;
    return (*insert_to_inflicted_tree(root, word));
}
inf_Node ** insert_to_inflicted_tree(inf_Node ** node_root, p_cell ptr_pcellword)
{
    // Base Case: Tree is empty
    if (!(*node_root))
        *node_root = create_inflicted_tst(ptr_pcellword->value);
    else if(!(*node_root)->key)
        (*node_root)->key=ptr_pcellword->value;
    // If ptr_word->value is < than (*root)->key,
    // then insert_to_baseTree this ptr_word in (*root)->left
    if ((ptr_pcellword->value) < (*node_root)->key)
        insert_to_inflicted_tree(&((*node_root)->left), ptr_pcellword);

        // If ptr_word->value is > than (*root)->key,
        // then insert_to_baseTree this ptr_word in (*root)->right_>
    else if ((ptr_pcellword->value) > (*node_root)->key)
        insert_to_inflicted_tree(&((*node_root)->right), ptr_pcellword);

        // If == as root->key,
    else {
        if (ptr_pcellword->next)
            insert_to_inflicted_tree(&((*node_root)->mid_eq), ptr_pcellword->next);
        //endofword-
        else{
            (*node_root)->end_of_word++;
            if(!(*node_root)->pointer){
                ((*node_root)->pointer)= create_inftype(typelistt);
            }

            return node_root;
        }
    }

}
//creates an inflicted type key structure
inf_Type * create_inftype(t_ht_list * typelist){
    inf_Type * temp= (inf_Type*)malloc(sizeof(inf_Type));
    p_cell tempo=typelist->head;
    while(tempo&&!(temp->PL_SG&&temp->gender)){
        switch (tempo->value) {
            case 'P':
                if(tempo->next&&tempo->next->value=='L')
                    temp->PL_SG='P';
                else{
                    if(tempo->next&&tempo->next->value==1)
                        temp->person=1;
                    else if(tempo->next&&tempo->next->value==2)
                        temp->person=2;
                    else if(tempo->next&&tempo->next->value==3)
                        temp->person=3;
                }
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
    if(!temp->person)
        temp->person=0;
    return temp;

}


