#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "windows.h"
#include "save1player.h"
#include "save2player.h"
#include "undo.h"
#include "split_alone.h"
void MoveTOXY(int x , int y)
{
    COORD coord ={ x , y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void move_cell(int choose,int move,cell *list,struct cell_map game_map[][size+2],int player)
{
    cell *current=list;
    int count=choose;
    count--;
    for(i=1;i<=count;i++)
    {
        current=current->next;
    }
    int energy=current->energy;
    char name[15];
    strcpy(name,current->name);
    int x=current->x;
    if(move==1)
    {
        game_map[current->x][current->y].full=0;
        current->y=(current->y)+1;
    }
    if(move==2)
    {
        game_map[current->x][current->y].full=0;
        current->y=(current->y)-1;
    }
    if(move==3 && x%2==0 )
    {
        game_map[current->x][current->y].full=0;
        current->x=(current->x)+1;
    }
    if(move==4 && x%2==0 )
    {
        game_map[current->x][current->y].full=0;
        current->x=(current->x)-1;
    }
    if(move==5 && x%2==0 )
    {
        game_map[current->x][current->y].full=0;
        current->x=(current->x)+1;
        current->y=(current->y)-1;
    }
    if(move==6 && x%2==0 )
    {
        game_map[current->x][current->y].full=0;
        current->x=(current->x)-1;
        current->y=(current->y)-1;
    }
    if(move==3 && x%2==1 )
    {
        game_map[current->x][current->y].full=0;
        current->x=(current->x)+1;
        current->y=(current->y)+1;
    }
    if(move==4 && x%2==1 )
    {
        game_map[current->x][current->y].full=0;
        current->x=(current->x)-1;
        current->y=(current->y)+1;
    }
    if(move==5 && x%2==1 )
    {
        game_map[current->x][current->y].full=0;
        current->x=(current->x)+1;
    }
    if(move==6 && x%2==1 )
    {
        game_map[current->x][current->y].full=0;
        current->x=(current->x)-1;
    }
    game_map[current->x][current->y].energy=energy;
    strcpy(game_map[current->x][current->y].name,name);
    game_map[current->x][current->y].full=player;
}
void get_energy(int choose,cell *list,struct cell_map game_map[][size+2])
{
    cell *current=list;
    int count=choose;
    count--;
    for(i=1;i<=count;i++)
    {
        current=current->next;
    }
    if(game_map[current->x][current->y].energy_house>15)
    {
        game_map[current->x][current->y].energy_house-=15;
        current->energy+=15;
        game_map[current->x][current->y].energy+=15;
    }
    else
    {
        int now=game_map[current->x][current->y].energy_house;
        game_map[current->x][current->y].energy_house-=now;
        current->energy+=now;
        game_map[current->x][current->y].energy+=now;
    }
}
void put_cells(char map[size+2][size+2],cell **list,struct cell_map game_map[][size+2],int cell_number,int player)
{
    for(i=1;i<=cell_number;i++)
    {
        int x,y,r;
        do
        {
            r=rand()%(size*size);
            x=(r%size)+1;
            y=(r/size)+1;
        } while(game_map[x][y].full==1 || game_map[x][y].full==2 || map[x][y]=='3');
        printf("Enter the %d'th cell name :",i);
        char name[15];
        gets(name);
        if(i==1)
        {
            *list=new_cell(x,y,name,100);
        }
        else
        {
            cell *new=new_cell(x,y,name,100);
            add_cell(*list,new);
        }
        strcpy(game_map[x][y].name,name);
        game_map[x][y].energy=100;
        game_map[x][y].full=player;
    }
}
int split(cell *list,struct cell_map game_map[][size+2],char map[][size+2],int choose,int player)
{
	
    cell *current=list;
    
    if(choose==1)
	{
		int tx=current->x;
		int ty=current->y;
		int tenergy=current->energy;
		char tname[15];
		strcpy(tname,current->name);
		current->x=current->next->x; 
		current->y=current->next->y; 
		current->energy=current->next->energy;
		strcpy(current->name,current->next->name);
		current->next->x=tx;
		current->next->y=ty;
		current->next->energy=tenergy;
		strcpy(current->next->name,tname);
		choose=2;
	}
    for(i=1;i<choose;i++)
    {
        current=current->next;
    }
    int ok=0;
    if(current->energy<80)
    {
        printf("NOT ENOUGH ENERGY\n");
        return 1;
    }
    int x=current->x;
    int y=current->y;
    if(x%2==0)
    {
	
		for(i=-1;i<=1;i++)
    	{
        	for(j=-1;j<=1;j++)
        	{
        	    if(x+i<=size && x+i>0 && y+j<=size && y+j>0 && game_map[x+i][y+j].full==0 && map[x+i][y+j]!='3' && i+j!=2 && 5*i+j!=-4)
           		{
                	ok++;
            	}
        	}
    	}
    	if(ok<2)
    	{
        	printf("NO SPACE TO SPLIT");
        	return 1;
    	}
    	if(player==1)
    		cell_number++;
    	if(player==2)
    		cell_number2++;
    	delete_node(list,choose);
    	ok=0;
    	char name[15];
    	for(i=-1;i<=1;i++)
    	{
        	for(j=-1;j<=1;j++)
        	{
            	if(x+i<=size && x+i>0 && y+j<=size && y+j>0 && game_map[x+i][y+j].full==0 && map[x+i][y+j]!='3' && i+j!=2 && 5*i+j!=-4)
           		{
            	    printf("Enter the name of the %d'th new cells:",ok+1);
                	gets(name);
                	cell *neww=new_cell(x+i,y+j,name,40);
                	game_map[x+i][y+j].energy=40;
                	game_map[x+i][y+j].full=player;
                	strcpy(game_map[x+i][y+j].name,name);
        	        add_cell(list,neww);
            	    ok++;
            	}
            	if(ok==2)
            	{
            	    break;
            	}
        	}
        	if(ok==2)
        	{
            	break;
       	 	}
    	}
    	game_map[x][y].full=0;
    	game_map[x][y].energy=0;
    }
	if(x%2==1)
    {
	
		for(i=-1;i<=1;i++)
    	{
        	for(j=-1;j<=1;j++)
        	{
        	    if(x+i<=size && x+i>0 && y+j<=size && y+j>0 && game_map[x+i][y+j].full==0 && map[x+i][y+j]!='3' && i+j!=-2 && 5*i+j!=4)
           		{
                	ok++;
            	}
        	}
    	}
    	if(ok<2)
    	{
        	printf("NO SPACE TO SPLIT");
        	return 1;
    	}
    	if(player==1)
    		cell_number++;
    	if(player==2)
    		cell_number2++;
    	delete_node(list,choose);
    	ok=0;
    	char name[15];
    	for(i=-1;i<=1;i++)
    	{
        	for(j=-1;j<=1;j++)
        	{
            	if(x+i<=size && x+i>0 && y+j<=size && y+j>0 && game_map[x+i][y+j].full==0 && map[x+i][y+j]!='3' && i+j!=-2 && 5*i+j!=4)
           		{
            	    printf("Enter the name of the %d'th new cells:",ok+1);
                	gets(name);
                	cell *neww=new_cell(x+i,y+j,name,40);
                	game_map[x+i][y+j].energy=40;
                	game_map[x+i][y+j].full=player;
                	strcpy(game_map[x+i][y+j].name,name);
        	        add_cell(list,neww);
            	    ok++;
            	}
            	if(ok==2)
            	{
            	    break;
            	}
        	}
        	if(ok==2)
        	{
            	break;
       	 	}
    	}
    	game_map[x][y].full=0;
    	game_map[x][y].energy=0;
    }
}
void print_table(struct cell_map game_map[][size+2],char map[][size+2])
{
    int x=1,y=count_line+3,count=1;
    int ff=100,xx=1,yy=1;
    int q=(1+count_line)%3;
    int i2=size+1;
    for(i=(1+count_line-q)/3 +1;i<=((1+count_line-q)/3)+size;i++)
    {
        i2--;
        if(ff==100)
            ff=70;
        else
            ff=100;
        x=1; y=3*i;
        for(j=1;j<=size;j++)
        {
            if(j%2==1)
            {
                if(i%2==1)
                {
                    if(ff==100)
                    ff=70;
                    else
                        ff=100;
                }
                if(i%2==0)
                {
                    if(ff==90)
                    ff=50;
                    else
                        ff=90;
                }
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ff);
                MoveTOXY(x,y);
                printf("%-7d",game_map[j][i2].energy_house);
                MoveTOXY(x,++y);
                printf("   %d   ",game_map[j][i2].full);
                MoveTOXY(x,++y);
                printf("%-7c",map[j][i2]);
                x+=7,y=3*i;
            }
            else
            {
                y+=1.5;
                if(i%2==1)
                {
                    if(ff==100)
                    ff=70;
                    else
                        ff=100;
                }
                if(i%2==0)
                {
                    if(ff==90)
                    ff=50;
                    else
                        ff=90;
                }
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),ff);
                MoveTOXY(x,y);
                printf("%-7d",game_map[j][i2].energy_house);
                MoveTOXY(x,++y);
                printf("   %d   ",game_map[j][i2].full);
                MoveTOXY(x,++y);
                printf("%-7c",map[j][i2]);
                x+=7,y=3*i;
            }
        }
    }
    count_line+=size*3 + 5;
    MoveTOXY(0,count_line+1);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}
int main()
{
    srand(time(NULL));
    //start of map reading
    FILE *map_f=fopen("D://maps//map.bin","rb");
    fread(&size,sizeof(unsigned int),1,map_f);
    struct cell_map game_map[size+2][size+2];
    for(i=1;i<=size;i++)
    {
        for(j=1;j<=size;j++)
        {
            game_map[i][j].full=0;
            game_map[i][j].energy_house=0;
            game_map[i][j].energy=0;
        }
    }
    char map[size+2][size+2];
    for(i=1;i<=size;i++)
    {
        for(j=1;j<=size;j++)
        {
            fread(&map[i][j],sizeof(char),1,map_f);
            if(map[i][j]=='1')
            {
                game_map[i][j].energy_house=100;
            }
        }
    }
    fclose(map_f);
    //end of map reading
    count_line+=5;
    printf("[1] Load\n[2] New single player game\n[3] New Multi player game\n[4] Exit\n");
    int start;
    scanf("%d",&start);
    getchar();
    cell *list=NULL;
    cell *list2=NULL;
    int start_from_save=0;
    if(start==1)
    {
        start_from_save=1;
        FILE *fp=fopen("D://saves//save.bin","rb");
        fread(&start,sizeof(int),1,fp);
        if(start==2)
        {
            fread(&cell_number,sizeof(int),1,fp);
            int name_size=0;
            for(i=1;i<=cell_number;i++)
            {
                int x,y,energy;
                char name[15];
                fread(&name_size,sizeof(int),1,fp);
                fread(&name,sizeof(char),name_size,fp);
                fread(&x,sizeof(int),1,fp);
                fread(&y,sizeof(int),1,fp);
                fread(&energy,sizeof(int),1,fp);
                name[name_size]='\0';
                if(i==1)
                {
                    list=new_cell(x,y,name,energy);
                }
                else
                {
                    cell *new=new_cell(x,y,name,energy);
                    add_cell(list,new);
                }
                strcpy(game_map[x][y].name,name);
                game_map[x][y].energy=energy;
                game_map[x][y].full=1;
            }
            for(i=1;i<=size;i++)
            {
                for(j=1;j<=size;j++)
                {
                    fread(&game_map[i][j].energy_house,sizeof(int),1,fp);
                }
            }
        }
        if(start==3)
        {
            fread(&cell_number,sizeof(int),1,fp);
            fread(&cell_number2,sizeof(int),1,fp);
            int name_size=0;
            for(i=1;i<=cell_number;i++)
            {
                int x,y,energy;
                char name[15];
                fread(&name_size,sizeof(int),1,fp);
                fread(&name, sizeof(char),name_size,fp);
                fread(&x,sizeof(int),1,fp);
                fread(&y,sizeof(int),1,fp);
                fread(&energy,sizeof(int),1,fp);
                name[name_size]='\0';
                if(i==1)
                {
                    list=new_cell(x,y,name,energy);
                }
                else
                {
                    cell *new=new_cell(x,y,name,energy);
                    add_cell(list,new);
                }
                strcpy(game_map[x][y].name,name);
                game_map[x][y].energy=energy;
                game_map[x][y].full=1;
            }
            for(i=1;i<=cell_number2;i++)
            {
                int x,y,energy;
                char name[15];
                fread(&name_size,sizeof(int),1,fp);
                fread(&name, sizeof(char),name_size,fp);
                fread(&x,sizeof(int),1,fp);
                fread(&y,sizeof(int),1,fp);
                fread(&energy,sizeof(int),1,fp);
                name[name_size]='\0';
                if(i==1)
                {
                    list2=new_cell(x,y,name,energy);
                }
                else
                {
                    cell *new=new_cell(x,y,name,energy);
                    add_cell(list2,new);
                }
                strcpy(game_map[x][y].name,name);
                game_map[x][y].energy=energy;
                game_map[x][y].full=2;
            }
        }
        for(i=1;i<=size;i++)
        {
            for(j=1;j<=size;j++)
            {
                fread(&game_map[i][j].energy_house,sizeof(int),1,fp);
            }
        }
        fclose(fp);
    }
    /////////////////////





    /////////////////////
    if(start==2)
    {
        if(start_from_save==0)
        {
            printf("Enter the number of cells that you need :");
            count_line+=3;
            scanf("%d",&cell_number);
            getchar();
            put_cells(map,&list,game_map,cell_number,1);
            count_line+=cell_number;
        }
        int t=0;
        while(1)
        {
            print_table(game_map,map);
            printf("Please choose one of your cells:\n");
            count_line+=2;
            count_line+=print_cells(list);
            int choose;
            scanf("%d",&choose);
            getchar();
            t++;
            if(t%2==1)
            	undo_one_player_odd(list,start,cell_number,game_map);
            else
            	undo_one_player_even(list,start,cell_number,game_map);
            printf("[1] Move\n[2] Split a cell\n[3] Boost energy\n[4] Save\n[5] Undo\n[6] Exit\n");
            count_line+=6;
            int action;
            scanf("%d",&action);
            getchar();
            if(action==1)
            {
                count_line+=7;
                printf("[1] North\n[2] South \n[3] Northeast\n[4] Northwest\n[5] Southeast\n[6] Southwest\n");
                int move;
                scanf("%d",&move);
                getchar();
                move_cell(choose,move,list,game_map,1);
            }
            if(action==2)
            {
            	int df=1;
            	if(choose==1 && cell_number==1)
            	{
            		df=0;
            		split_alone(&list,game_map,map,choose,1);
				}
            	if(cell_number!=1 && df==1)
                	split(list,game_map,map,choose,1);
                count_line+=3;
            }
            if(action==3)
            {
                get_energy(choose,list,game_map);
            }
            if(action==4)
            {
                save_one_player(list,start,cell_number,game_map);
            }
            if(action==5)
            {	
            	for(i=1;i<=size;i++)
    			{
        			for(j=1;j<=size;j++)
        			{
            			game_map[i][j].full=0;
            			game_map[i][j].energy_house=0;
            			game_map[i][j].energy=0;
        			}
    			}
            	list=NULL;
            	if(t%2==0)
            	{
            		FILE *fp=fopen("D://undo//undo_odd.bin","rb");
        			fread(&start,sizeof(int),1,fp);
            		fread(&cell_number,sizeof(int),1,fp);
            		int name_size=0;
            		for(i=1;i<=cell_number;i++)
            		{
                		int x,y,energy;
                		char name[15];
                		fread(&name_size,sizeof(int),1,fp);
                		fread(&name,sizeof(char),name_size,fp);
                		fread(&x,sizeof(int),1,fp);
                		fread(&y,sizeof(int),1,fp);
                		fread(&energy,sizeof(int),1,fp);
                		name[name_size]='\0';
                		if(i==1)
                		{
                    		list=new_cell(x,y,name,energy);
                		}
                		else
                		{
                    		cell *new=new_cell(x,y,name,energy);
                    		add_cell(list,new);
                		}
                		strcpy(game_map[x][y].name,name);
                		game_map[x][y].energy=energy;
                		game_map[x][y].full=1;
            		}
            		for(i=1;i<=size;i++)
            		{
                		for(j=1;j<=size;j++)
                		{
                    		fread(&game_map[i][j].energy_house,sizeof(int),1,fp);
                		}
            		}
				}
				if(t%2==1)
            	{
            		FILE *fp=fopen("D://undo//undo_even.bin","rb");
        			fread(&start,sizeof(int),1,fp);
            		fread(&cell_number,sizeof(int),1,fp);
            		int name_size=0;
            		for(i=1;i<=cell_number;i++)
            		{
                		int x,y,energy;
                		char name[15];
                		fread(&name_size,sizeof(int),1,fp);
                		fread(&name,sizeof(char),name_size,fp);
                		fread(&x,sizeof(int),1,fp);
                		fread(&y,sizeof(int),1,fp);
                		fread(&energy,sizeof(int),1,fp);
                		name[name_size]='\0';
                		if(i==1)
                		{
                    		list=new_cell(x,y,name,energy);
                		}
                		else
                		{
                    		cell *new=new_cell(x,y,name,energy);
                    		add_cell(list,new);
                		}
                		strcpy(game_map[x][y].name,name);
                		game_map[x][y].energy=energy;
                		game_map[x][y].full=1;
            		}
            		for(i=1;i<=size;i++)
            		{
                		for(j=1;j<=size;j++)
                		{
                    		fread(&game_map[i][j].energy_house,sizeof(int),1,fp);
                		}
            		}
				}
			}
            if(action==6)
            {
            	printf("By extiting , the proccess will be deleted do you want to save:\n");
                printf("1)Yes	2)No \n");
                int close;
                scanf("%d",&close);
                if(close==1)
                {
                	save_one_player(list,start,cell_number,game_map);
				}
				printf("End of the game  :) ");
                return 0;
            }
        }
    }
    ///////////////////



    ///////////////////
    if(start==3)
    {
        if(start_from_save==0)
        {
            printf("Enter the number of the cells of the first player:");
            count_line+=2;
            scanf("%d",&cell_number);
            getchar();
            put_cells(map,&list,game_map,cell_number,1);
            count_line+=cell_number;
            count_line++;
            printf("Enter the number of the cells of the second player:");
            count_line+=2;
            scanf("%d",&cell_number2);
            getchar();
            count_line+=cell_number2;
            count_line++;
            put_cells(map,&list2,game_map,cell_number2,2);
        }
        int w;
        for(w=1;;w++)
        {
            print_table(game_map,map);
            if(w%2==1)
            {
                printf("First player please choose one of you cells:\n");
                count_line+=3;
                count_line+=print_cells(list);
                int choose;
                scanf("%d",&choose);
                getchar();
                count_line+=6;
                printf("[1] Move\n[2] Split a cell\n[3] Boost energy\n[4] Save\n[5] Exit\n");
                int action;
                scanf("%d",&action);
                getchar();
                if(action==1)
                {
                    count_line+=7;
                    printf("[1] North\n[2] South \n[3] Northeast\n[4] Northwest\n[5] Southeast\n[6] Southwest\n");
                    int move;
                    scanf("%d",&move);
                    getchar();
                    move_cell(choose,move,list,game_map,1);
                }
                if(action==2)
                {
                	int df=1;
                    if(choose==1 && cell_number==1)
            		{
            			df=0;
            			split_alone(&list,game_map,map,choose,1);
					}
            		if(cell_number!=1 && df==1)
                		split(list,game_map,map,choose,1);
                	count_line+=3;
                }
                if(action==3)
                {
                    get_energy(choose,list,game_map);
                }
                if(action==4)
                {
                    save_two_player(list,list2,start,cell_number,cell_number2,game_map);
                }
                if(action==5)
                {
                	printf("By extiting , the proccess will be deleted do you want to save:\n");
                	printf("1)Yes	2)No \n");
                	int close;
                	scanf("%d",&close);
                	if(close==1)
                	{
                		save_two_player(list,list2,start,cell_number,cell_number2,game_map);
					}
					printf("End of the game  :) ");
                    return 0;
                }
            }
            /////////////////////////////////////////
            if(w%2==0)
            {
                printf("Second player please choose one of you cells:\n");
                count_line+=2;
                print_cells(list2);
                int choose;
                scanf("%d",&choose);
                getchar();
                count_line+=6;
                printf("[1] Move\n[2] Split a cell\n[3] Boost energy\n[4] Save\n[5] Exit\n");
                int action;
                scanf("%d",&action);
                getchar();
                if(action==1)
                {
                    count_line+=7;
                    printf("[1] North\n[2] South \n[3] Northeast\n[4] Northwest\n[5] Southeast\n[6] Southwest\n");
                    int move;
                    scanf("%d",&move);
                    getchar();
                    move_cell(choose,move,list2,game_map,2);
                }
                if(action==2)
                {
                	int df=1;
                    if(choose==1 && cell_number2==1)
            		{
            			df=0;
            			split_alone(&list2,game_map,map,choose,2);
					}
            		if(cell_number2!=1 && df==1)
                		split(list2,game_map,map,choose,2);
                	count_line+=3;
                }
                if(action==3)
                {
                    get_energy(choose,list2,game_map);
                }
                if(action==4)
                {
                    save_two_player(list,list2,start,cell_number,cell_number2,game_map);
                }
                if(action==5)
                {
                	printf("By extiting ,the proccess will be deleted do you want to save:\n");
                	printf("1)Yes	2)No \n");
                	int close;
                	scanf("%d",&close);
                	if(close==1)
                	{
                		save_two_player(list,list2,start,cell_number,cell_number2,game_map);
					}
					printf("End of the game  :) ");
                    return 0;
                }
            }
        }
    }
    if(start==4)
    {
        return 0;
    }
    return 0;
}
