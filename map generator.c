#include <stdio.h>
int main()
{
    printf("Enter the size of ground :");
    unsigned int size;
    scanf("%d",&size);
    char map[size+2][size+2];
	int i,j;
    for(i=0;i<=size+1;i++)
    {
        for(j=0;j<=size;j++)
        {
            map[i][j]='4';
        }
    }
    printf("Enter the number of ENERGY cells:");
    int energy;
    scanf("%d",&energy);

    for(i=1;i<=energy;i++)
    {
        printf("Enter the coordinate of the %d'th energy cells:\n",i);
        int x,y;
        scanf("%d%d",&x,&y);
        map[x][y]='1';
    }
    printf("Enter the number of MITOSIS cells:");
    int mitosis;
    scanf("%d",&mitosis);
    for(i=1;i<=mitosis;i++)
    {
        printf("Enter the coordinate of the %d'th mitosis cells:\n",i);
        int x,y;
        scanf("%d%d",&x,&y);
        map[x][y]='2';
    }
    printf("Enter the number of FORBIDDEN cells:");
    int forbidden;
    scanf("%d",&forbidden);
    for(i=1;i<=forbidden;i++)
    {
        printf("Enter the coordinate of the %d'th forbidden cells:\n",i);
        int x,y;
        scanf("%d%d",&x,&y);
        map[x][y]='3';
    }
    FILE *fp=fopen("D://maps//map.bin","wb");
    fwrite(&size,sizeof(unsigned int),1,fp);
    for(i=1;i<=size;i++)
    {
        for(j=1;j<=size;j++)
        {
            fwrite(&map[i][j], sizeof(char),1,fp);
        }
    }
    fclose(fp);
    printf("Map generated successfully :)");
    return 0;
}
