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
    //srand(time(NULL));
    //random_helper(verb);
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
//generates a random base form
t_ht_list * randomgenerator(Node * root){
    t_ht_list * word=createlist();
   // srand(time(0));
    int y,i,stop=0,ismiddle=0,u=0;
    Node *temp=root;
    if(temp) {
        y = rand() % 25;
        for (int j = 0; temp->right && j < y; ++j) {

            temp = temp->right;
        }
       // printf("\n%c<----%d\n",temp->key,y);
        u=1;
    }
    while(!stop){

       //srand(time(0));
        if(temp){

            y=rand()%15;
            for (int j = 0; u==0&&temp->right &&j <y ; ++j) {
                temp=temp->right;
            }

            //printf("reached here");
            if(u)
                i=1;
            else
                i=rand()%3;
            u=0;
          //printf("temp->key--->%c\n",temp->key);
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
            if(temp&&temp->inflictedno!=0&&ismiddle){
                if(rand()%3==0){
                    //printf("**************rand =0 letter to be added--->%c\n",temp->key);
                    addTailHt(word,temp->key);
                    stop=1;}
                else{/*
                    printf("************rand=1 letter to be added--->%c\n",temp->key);*/
                    addTailHt(word,temp->key);
                    //if(ismiddle){
                    ismiddle=0;
                    temp=temp->mid_eq;   // }


                }
            }
            else if(ismiddle){/*
                printf("middle no null and temp=temp->mid_eq\n");
                printf("************rand=1 letter to be added--->%c\n",temp->key);*/
                addTailHt(word,temp->key);
                ismiddle=0;
                temp=temp->mid_eq;
            }
        }else{
            stop=1;
        }
    }
    return word;
}


void model_one_two(){
    int i=0;
    int j = 0;
    //choice of the model of the sentence
    printf("\nplease choose which model you want\n");
    printf (" 1--->base form | 2--->inflicted form\n");   // added line on 20 november//
    scanf("%d", &j);
    if (j==1){
        printf(" 1--->first form | 2--->second form\n 3---<Third form |  4 --->Back\n  ");

        //read the input/answer
        scanf("%d", &i);
        if (i == 1) {
            //model 1 random sentence
            //random word from the (noun,adjective,verb,adverb) tree
            displaytowordvoid(*randomgenerator(noun));
            displaytowordvoid(*randomgenerator(adjective));
            displaytowordvoid(*randomgenerator(verb));
            displaytowordvoid(*randomgenerator(noun));
        } else if (i == 2) {
            //model 2 random sentence
            displaytowordvoid(*randomgenerator(noun));
            printf(" qui ");
            displaytowordvoid(*randomgenerator(verb));
            displaytowordvoid(*randomgenerator(verb));
            displaytowordvoid(*randomgenerator(noun));
            displaytowordvoid(*randomgenerator(adjective));}
    }
    else if (j==2){
        int k=0;
        printf(" 1--->first model | 2--->second model\n");
        scanf("%d", &k);
        if(k==1){
           // model1_inflicted_form();}
       // else //if(k==2){
           // model2_inflicted_form();
        }
    }
}


int menu_real(){
    int num;

    while(1){
        num=6;
        do { // SAISIE SECU
            printf("\nPlease enter your choice\n");
            printf(" (1) Search words from the tree | (2) Print all the base words in all trees\n (3) Generate Randoms Sentence  | (4) Get the inflicted form of a base word\n (5) Generate Random base word /Inflicted word   | (6) Quit \n  ");
            printf("What do you want ?\n:");

            scanf("%d", &num);
        } while (num<0|| num > 6);
        switch(num){
            case 1 :
                search_tree(0);
                break;
            case 2 :
                print_tree();
                break;
            case 3 :
                model_one_two();
                return menu_real();
            case 4:
                search_tree(1);
                break;
            case 6:
                printf("Goodbye!\n");
                return 0;
            case 5:
                extract_randomword();
                break;
            default:
                printf("incorrect type of value given!!  Please enter numbers not characters\n");
                num=5;
                return -1;
                break;
        }
    }
}

void extract_randomword(){
    int i=0,k=0;
    printf("\nplease choose which model you want\n");
    printf (" 1--->base form | 2--->inflicted form\n");
    scanf("%d", &k);
    //choice of which tree
    printf("\nplease choose from which tree you want to extract a random word\n");
    printf(" 1--->verb | 2--->noun\n 3--->adverb |  4 --->adjective\n  ");

    //read the input/answer
    scanf("%d", &i);
    if(k==1){
        switch (i) {
            case 1:
                displaytowordvoid(*randomgenerator(verb));
                break;
            case 2:
                displaytowordvoid(*randomgenerator(noun));
                break;
            case 3:
                displaytowordvoid(*randomgenerator(adverb));
                break;
            case 4:
                displaytowordvoid(*randomgenerator(adjective));
                break;
        }
    }
    else{
        switch (i) {
            case 1:
                random_helper(verb);
                break;
            case 2:
                random_helper(noun);
                break;
            case 3:
                random_helper(adverb);
                break;
            case 4:
                random_helper(adjective);
                break;
        }

    }

}

void print_tree(){
    printf("Following is traversal of noun ternary search tree\n");
    char nounl[MAX];

    base_recprint(noun, nounl, 0);
    //printbasetree(noun);
    printf("Following is traversal of adjective ternary search tree\n");
    char adjectivel[MAX];

    base_recprint(adjective, adjectivel, 0);
   // printbasetree(adjective);
    printf("Following is traversal of adverb ternary search tree\n");
    char adverblist[MAX];

    base_recprint(adverb, adverblist, 0);
   // printbasetree(adverb);
    printf("Following is traversal of verb ternary search tree\n");
    char verblist[MAX];

    base_recprint(verb, verblist, 0);
   // printbasetree(verb);
}

int search_tree(int num){
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
            if(findinbasetree(verb, list->head)){
                //displaytowordvoid(*list);
                printf("\nit is found\n");
                if(num){
                    char buffer[MAX];
                    inf_printtree((insert_to_baseTree(&verb, list->head))->pointer, buffer, 0);
                }
                  //  printinflictedtree((insert_to_baseTree(&verb, list->head))->pointer);
                return 1;
            }
            else{
                printf("not found");
                return 0;
            }

            break;
        case 2 :

            if(findinbasetree(noun, list->head)){
                printf("\nit is found\n");
                if(num){
                    char buffer[MAX];
                    inf_printtree((insert_to_baseTree(&noun, list->head))->pointer, buffer, 0);
                }
                    //printinflictedtree((insert_to_baseTree(&noun, list->head))->pointer);
                return 1;
            }
            else{
                printf("\nit is found\n");
                return 0;
            }

            break;        //return second_menu();
        case 3 :
            if(findinbasetree(adverb, list->head)){
                printf("\nit is found\n");
                if(num){
                    char buffer[MAX];
                    inf_printtree((insert_to_baseTree(&adverb, list->head))->pointer, buffer, 0);
                }
                   // printinflictedtree((insert_to_baseTree(&adverb, list->head))->pointer);
                return 1;
            }
            else{
                printf("\nit is found\n");
                return 0;
            }
            //fonctions
            break;//return second_menu();
        case 4 :
            if(findinbasetree(adjective, list->head)){
                printf("\nit is found\n");
                if(num){
                    char buffer[MAX];
                    inf_printtree(insert_to_baseTree(&adjective, list->head)->pointer, buffer, 0);
                }
                    //printinflictedtree((insert_to_baseTree(&adjective, list->head))->pointer);
                return 1;
            }
            else{
                printf("not found");
                return 0;
            }
            break;
        default:
            printf("incorrect type of value given!!  Please enter numbers not characters\n");

            break;

    }


}

void random_helper(Node * root){
    t_ht_list *mylist;//verb
    mylist =randomgenerator(root);//alle(r)
    //displaytowordvoid(*mylist);
    //printf("\n ..................................\n");
    Node * last_node =insert_to_baseTree(&root,mylist->head);
    inf_Node * inf_root=last_node->pointer;
    t_ht_list * inf_list = randomgenerator_inflicted(inf_root);
   // printf("\n ..................................\n");
    //printf("display one random inflicted word \n");
    displaytowordvoid(*inf_list);
    inf_Node ** leaf_inf=insert_to_inflicted_tree(&inf_root, inf_list->head);
    if((*leaf_inf)->pointer->gender=='F'){
        printf("\nThis word is Feminine");
    }
    else if((*leaf_inf)->pointer->gender=='M')
        printf("\nThis word is Masculine");
    else
        printf("\nThis word works for both Masculine and Feminine");


    if((*leaf_inf)->pointer->PL_SG=='S') {
            printf("\nThis word is Singular");}
    else if((*leaf_inf)->pointer->PL_SG=='P')
        printf("\nThis word is Plural");
    else
        printf("\nThis word works for both Plural and Singular\n");

    if((*leaf_inf)->pointer->person==1)
        printf("This verb is first person");
    else if((*leaf_inf)->pointer->person==2)
        printf("This verb is second person");
    else if((*leaf_inf)->pointer->person==3)
        printf("This verb is third person");



}



t_ht_list * randomgenerator_inflicted(inf_Node * root){
    t_ht_list * word=createlist();
    // srand(time(0));
    int y,i,stop=0,ismiddle=0,u=0;
    inf_Node *temp=root;
    if(temp) {
        y = rand() % 25;
        for (int j = 0; temp->right && j < y; ++j) {

            temp = temp->right;
        }
        // printf("\n%c<----%d\n",temp->key,y);
        u=1;
    }
    while(!stop){

        //srand(time(0));
        if(temp){

            y=rand()%15;
            for (int j = 0; u==0&&temp->right &&j <y ; ++j) {
                temp=temp->right;
            }

            //printf("reached here");
            if(u)
                i=1;
            else
                i=rand()%3;
            u=0;
            //printf("temp->key--->%c\n",temp->key);
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
            if(temp&&temp->end_of_word!=0&&ismiddle){         // ?
                if(rand()%3==0){
                    //printf("**************rand =0 letter to be added--->%c\n",temp->key);
                    addTailHt(word,temp->key);
                    stop=1;}
                else{/*
                    printf("************rand=1 letter to be added--->%c\n",temp->key);*/
                    addTailHt(word,temp->key);
                    //if(ismiddle){
                    ismiddle=0;
                    temp=temp->mid_eq;   // }


                }
            }
            else if(ismiddle){/*
                printf("middle no null and temp=temp->mid_eq\n");
                printf("************rand=1 letter to be added--->%c\n",temp->key);*/
                addTailHt(word,temp->key);
                ismiddle=0;
                temp=temp->mid_eq;
            }
        }else{
            stop=1;
        }
    }
    return word;
}
