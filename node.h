#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int size;
int i,j;
int energy=0;
int count_line=0;
int cell_number,cell_number2;
struct cell_map
{
    char name[15];
    int full;
    int energy;
    int energy_house;
};
struct cell
{
    char name[15];
    int x;
    int y;
    int energy;
    struct cell *next;
};
typedef struct cell cell;
cell* new_cell(int x,int y,char name[],int energy)
{
    cell *new=(cell *)malloc(1*sizeof(cell));
    new->next=NULL;
    new->x=x;
    new->y=y;
    new->energy=energy;
    strcpy(new->name,name);
    return new;
}
void add_cell(cell *list,cell *new)
{
    cell *current=list;
    while(current->next!=NULL)
    {
        current=current->next;
    }
    current->next=new;
    current->next->next=NULL;
}
int print_cells(cell *list)
{
    cell *current=list;
    int i=1;
    int count=0;
    while(current!=NULL)
    {
        count++;
        printf("[%d] %s (%d , %d) energy : %d\n",i,current->name,current->x,current->y,current->energy);
        i++;
        current=current->next;
    }
    return count;
}
void delete_node(cell *list,int select)
{
    cell *current=list;
    for(i=1;i<=select-2;i++)
    {
        current=current->next;
    }
    current->next=current->next->next;
}
