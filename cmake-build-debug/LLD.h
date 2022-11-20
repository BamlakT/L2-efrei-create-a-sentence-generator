#ifndef __QUEUE_H_INCLUDED__
#define __QUEUE_H_INCLUDED__



// cell for the ht linked list

struct s_cell
{
    char value;
    struct s_cell *next;
};

typedef struct s_cell t_cell, *p_cell;
// simple structure for ht linked list(head tail features)
typedef struct s_std_list
{
    p_cell head;
    p_cell tail;
} t_ht_list;

t_ht_list* createlist();

void addTailHt(t_ht_list *, char );
p_cell createCell(char);
void deleteList(p_cell * ,p_cell * );
void displaytowordvoid(t_ht_list );
#endif