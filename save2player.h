#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void save_two_player(cell*list,cell *list2,int start,int cell_number,int cell_number2,struct cell_map game_map[][size+2])
{
    FILE *save_f=fopen("D://saves//save.bin","wb");
    fwrite(&start,sizeof(int),1,save_f); //start
    fwrite(&cell_number,sizeof(int),1,save_f); //cell number 1
    fwrite(&cell_number2,sizeof(int),1,save_f); //cell number 2
    cell *current=list;
    for(i=1;i<=cell_number;i++)
    {
        char name_current[15];
        strcpy(name_current,current->name);
        int size_name=(int)strlen(name_current);
        int x_current=current->x;
        int y_current=current->y;
        int energy_current=current->energy;
        fwrite(&size_name,sizeof(int),1,save_f);
        fwrite(&name_current,sizeof(char),size_name,save_f);
        fwrite(&x_current,sizeof(int),1,save_f);
        fwrite(&y_current,sizeof(int),1,save_f);
        fwrite(&energy_current,sizeof(int),1,save_f);
        current=current->next;
    }
    current=list2;
    for(i=1;i<=cell_number2;i++)
    {
        char name_current[15];
        strcpy(name_current,current->name);
        int size_name=(int)strlen(name_current);
        int x_current=current->x;
        int y_current=current->y;
        int energy_current=current->energy;
        fwrite(&size_name,sizeof(int),1,save_f);
        fwrite(&name_current,sizeof(char),size_name,save_f);
        fwrite(&x_current,sizeof(int),1,save_f);
        fwrite(&y_current,sizeof(int),1,save_f);
        fwrite(&energy_current,sizeof(int),1,save_f);
        current=current->next;
    }
    for(i=1;i<=size;i++)
    {
        for(j=1;j<=size;j++)
        {
            int temp=game_map[i][j].energy_house;
            fwrite(&temp,sizeof(int),1,save_f);
        }
    }
    fclose(save_f);
}
