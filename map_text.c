#include <stdio.h>
int main()
{
    FILE *map=fopen("D://maps//map.bin","rb");
    FILE *tx=fopen("D://map_text//map.txt","w");
    int size;
    fread(&size,sizeof(int),1,map);
    fprintf(tx,"The size of the table is : %d\n\n",size);
    char c;
    int i,j;
    char table[size+2][size+2];
    for(i=1;i<=size;i++)
    {
        for(j=1;j<=size;j++)
        {
            fread(&table[i][j],sizeof(char),1,map);
        }
    }
    for(i=size;i>=1;i--)
    {
        for(j=1;j<=size;j++)
        {
            if(table[j][i]=='1')
            {
                fprintf(tx,"Energy    ");
            }
            if(table[j][i]=='2')
            {
                fprintf(tx,"Mitosis   ");
            }
            if(table[j][i]=='3')
            {
                fprintf(tx,"Forbidden ");
            }
            if(table[j][i]=='4')
            {
                fprintf(tx,"Normal    ");
            }
        }
        fprintf(tx,"\n\n");
    }
    return 0;
}
