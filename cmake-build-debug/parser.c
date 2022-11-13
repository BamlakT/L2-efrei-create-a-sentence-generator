//
// Created by hp on 28-Oct-22.
//
#include <stdio.h>
#include <time.h>
#include "parser.h"
#include "LLD.h"

#include "tst node.h"
//4 tries that acts as a global variable
Node * verb=NULL,* noun=NULL,* adjective=NULL,*adverb=NULL;

//Reads from the file and parses it into base form ,inflicted form,type(verb,adj,adv,noun)
int File_parser() {
    FILE *dictionary;
    int c, end = 0, list = 0;
    dictionary = fopen("demo.txt", "r");
    if (dictionary == NULL) {
        perror("Error in opening file");
        return (-1);
    }
    //created list for each kind of words
    t_ht_list *inflicted = createlist();
    t_ht_list *base = createlist();
    t_ht_list *type = createlist();
    //temporary pointer to know where to insert_to_baseTree the characters
    t_ht_list *temp = inflicted;
    //the variable "end" acts a boolean passenger and end == 1 if end of file
    while (end == 0) {
        do {
            c = fgetc(dictionary);
            if (feof(dictionary)) {
                end = 1;
                break;
            }
            //printf("%c", c);
            if (c == 9 || c == 10)
                break;
            else
                addTailHt(temp, c);
        } while (1);
        //switch case to know the current stage of the word
        //since the dictionary is written (0)inflicted form (1)base form (2)type
        switch (list) {
            case 0:
                list = 1;
                temp = base;
                break;
            case 1:
                list = 2;
                temp = type;
                break;
            default:
                list = 0;
                //we are now case 2, so now we can populate the tree since we have got all the words in a line
                insertall(base,inflicted,type);
                //deletelist frees the linked lists since we are using dynamic arrays and we no longer need it
                deleteList(& inflicted->head,&inflicted->tail);
                deleteList(& base->head,&base->tail);
                deleteList(& type->head,&type->tail);
                inflicted = createlist();
                base = createlist();
                type = createlist();
                temp = inflicted;
                break;
        }
    }
    //finished reading the file close it
    fclose(dictionary);
    return (0);
}


//very key function that inserts values from lists into the correct type of trees
void insertall(t_ht_list *baselist,  t_ht_list * inflictedlist,t_ht_list *typelist){
    Node *temp=NULL;
    switch (typelist->head->value) {
        case 'V':
            //we assume the word is a verb
            temp= insert_to_baseTree(&(verb), baselist->head);
            insertinffromlist(&(temp->pointer), inflictedlist->head,typelist);

            break;
        case 'N':
            //we assume the word is a noun
            temp= insert_to_baseTree(&(noun), baselist->head);
            insertinffromlist(&(temp->pointer), inflictedlist->head,typelist);
            break;
        case 'A':
            if(typelist->head->next->next->value&&typelist->head->next->next->value=='j'){
                //we assume the word is an adjective
                temp= insert_to_baseTree(&(adjective), baselist->head);
                insertinffromlist(&(temp->pointer), inflictedlist->head,typelist);
            }
            else {
                //we assume the word is an adverb
                temp= insert_to_baseTree(&(adverb), baselist->head);
                insertinffromlist(&(temp->pointer), inflictedlist->head,typelist);

            }break;

    }
}

t_ht_list * randomgenerator(Node * root){
    t_ht_list * word=createlist();
   // srand(time(0));
    int y,i,stop=0,ismiddle=0;
    Node *temp=root;

    while(!stop){

       //srand(time(0));
        if(temp){
            y=rand()%27;
            for (int j = 0; temp->right &&j <y ; ++j) {
                temp=temp->right;
            }

            i=rand()%3;
          //printf("temp->data--->%c\n",temp->data);
            switch (i) {
                case 0:
                    if(temp->left){
                        //printf("temp=temp->left no null\n");
                        temp=temp->left;}
                    else {
                        if (temp->right&&rand() % 3 != 0){
                            //printf("rand no--->0 left=null and temp=temp->right \n");
                            temp=temp->right;}
                        else{
                            //printf("rand no--->1or temp->right is null left=null and temp=temp->mid_eq/n");
                            ismiddle=1;}
                            //temp=temp->mid_eq;}
                    }
                    break;
                case 1:
                    ismiddle=1;
                    break;
                case 2:
                    if(temp->right){

                        //printf("temp=temp->right no null\n");
                        temp=temp->right;}
                    else {
                        if (temp->left&&rand() % 2 == 0){
                            //printf("rand no--->0 right=null and temp=temp->left \n");
                            temp=temp->left;}
                        else{
                           // printf("rand no--->1 or templeft is null rigth=null and temp=temp->mid_eq\n");
                            ismiddle=1;}
                            //temp=temp->mid_eq;}
                    }
                    break;
                default:
                    //printf("to be solved");
                    stop=1;
                    break;
            }
            if(temp->inflictedno!=0&&ismiddle){
                if(rand()%3==0){
                    //printf("**************rand =0 letter to be added--->%c\n",temp->data);
                    addTailHt(word,temp->data);
                    stop=1;}
                else{/*
                    printf("************rand=1 letter to be added--->%c\n",temp->data);*/
                    addTailHt(word,temp->data);
                    //if(ismiddle){
                    ismiddle=0;
                    temp=temp->mid_eq;   // }


                }
            }
            else if(ismiddle){/*
                printf("middle no null and temp=temp->mid_eq\n");
                printf("************rand=1 letter to be added--->%c\n",temp->data);*/
                addTailHt(word,temp->data);
                ismiddle=0;
                temp=temp->mid_eq;
            }
        }else{
            stop=1;
        }
    }
    return word;

}


void modelone(){
    int i=0;
    printf("\nplease choose which model you want\n");
    printf(" 1--->first form | 2--->second form\n 3---<Third form |  4 --->Back\n  ");


    scanf("%d", &i);
    if (i == 1) {
        displaytowordvoid(*randomgenerator(noun));
        displaytowordvoid(*randomgenerator(adjective));
        displaytowordvoid(*randomgenerator(verb));
        displaytowordvoid(*randomgenerator(noun));
    } else if (i == 2) {
        displaytowordvoid(*randomgenerator(noun));
        printf(" qui ");
        displaytowordvoid(*randomgenerator(verb));
        displaytowordvoid(*randomgenerator(verb));
        displaytowordvoid(*randomgenerator(noun));
        displaytowordvoid(*randomgenerator(adjective));}

}
int menu_real(){
    int num;

    while(1){
        num=6;
        do { // SAISIE SECU
            printf("\nPlease enter your choice\n");
            printf(" (1) Search words from the tree | (2) Print all the base words in the tree\n (3) Generate Randoms Sentence  | (4) Know who's behind this project\n (5)Quit\n  ");
            printf("What do you want ?\n:");

            scanf("%d", &num);
        } while (num<0|| num > 6);
        switch(num){
            case 1 :
                search_tree();
                //fonctions
                //return second_menu();
                break;
            case 2 :
                print_tree();

                break;        //return second_menu();
            case 3 :
                modelone();
                return menu_real();
                //fonctions
                break;//return second_menu();
            case 5 :
                printf("Goodbye!\n");
                return 0;
                break;
            default:
                printf("incorrect type of value given!!  Please enter numbers not characters\n");
               // menu_real();
               num=5;
                return -1;
                break;

        }


    }

}

// Function to autocomplete
// based on the given prefix
// and return the suggestions
void autocomplete(Node* root, p_cell word)
{
  //t_ht_list words;
    //vector<string> words;
    /*
    while (word){
        printf("%c",word->value);
        word=word->next;
    }*/

    // If pattern is empty
    // return an empty list
    if (!word)
        return;

    // Iterating over the characters
    // of the pattern and find it's
    // corresponding node in the tree

    while (root && word) {

        // If current character is smaller
        if (root->data > word->value)
            // Search the left subtree
            root = root->left;

            // current character is greater
        else if (root->data < word->value)
            // Search right subtree
            root = root->right;

            // If current character is mid_eq
        else if (root->data == word->value) {

            // Search mid_eq subtree
            // since character is found, move to the next character in the pattern
            root = root->mid_eq;
            word=word->next;
        }
            // If not found
        else
            return;

    }
    if(root)
        printf("kkkkkkkkkkkkkkkkkkkkkkk");

    printf("---------------");
    traverseTST(root);

}


void print_tree(){
    printf("Following is traversal of noun ternary search tree\n");
    traverseTST(noun);
    printf("Following is traversal of adjective ternary search tree\n");
    traverseTST(adjective);
    printf("Following is traversal of adverb ternary search tree\n");
    traverseTST(adverb);
    printf("Following is traversal of verb ternary search tree\n");
    traverseTST(verb);
}

/*
               printf("\n********Printing the child of adverb***************************** /\n");
               traverseinfTST((temp)->pointer);
               printf("\n********Printing the child of child of adverb***************************** /\n");
               switch ((temp1)->pointer->gender) {
                   case 'F':
                       printf("Fem\n");
                       break;
                   case 'M':
                       printf("Mas\n");
                       break;
                   default:
                       printf("Both mas and fem\n");
                       break;

               }

               switch ((temp1)->pointer->PL_SG) {
                   case 'S':
                       printf("Singular\n");
                       break;
                   case 'P':
                       printf("Plural\n");
                       break;
                   default:
                       printf("Both Plural and Singular\n");
                       break;

               }
               printf("*******************\n");*/

void search_tree(){
    t_ht_list * list=createlist();
    int i=0;
    do{
    printf("\nplease choose from which you want to search\n");
    printf(" 1--->verb | 2--->noun\n 3--->adverb |  4 --->adjective\n  ");
    scanf("%d", &i);
        printf("%d\n",i);
    } while (i<1|| i > 4);
    char name[50];
    printf("Enter the word you want to search: ");
    scanf("%s",name);
    for(int j=0;name[j]!='\0';j++)
        addTailHt(list,name[j]);
    //printf("%d",i);
    switch(i){
        case 1 :
            if(searchTST(verb,list->head)){
                displaytowordvoid(*list);
                printf("it is found");
            }
            else
                printf("not found");
            break;
        case 2 :

            if(searchTST(noun,list->head)){
                printf("it is found");
            }
            else
                printf("not found");

            break;        //return second_menu();
        case 3 :
            if(searchTST(adverb,list->head)){
                printf("it is found");
            }
            else
                printf("not found");
            //fonctions
            break;//return second_menu();
        case 4 :
            if(searchTST(adjective,list->head)){
                printf("it is found");
            }
            else
                printf("not found");
            break;
        default:
            printf("incorrect type of value given!!  Please enter numbers not characters\n");

            break;

    }


}