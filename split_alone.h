int split_alone(cell **list,struct cell_map game_map[][size+2],char map[][size+2],int choose,int player)
{
	if(choose==1)
	{
		cell *current=*list;
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
    		*list=NULL;
    		ok=0;
    		char name[15];
    		for(i=-1;i<=1;i++)
    		{
        		for(j=-1;j<=1;j++)
        		{
            		if(x+i<=size && x+i>0 && y+j<=size && y+j>0 && game_map[x+i][y+j].full==0 && map[x+i][y+j]!='3' && i+j!=2 && 5*i+j!=-4)
           			{
            	    	if(ok==1)
            	    	{
            	    		printf("Enter the name of the %d'th new cells:",ok+1);
                			gets(name);
                			cell *neww=new_cell(x+i,y+j,name,40);
                			game_map[x+i][y+j].energy=40;
                			game_map[x+i][y+j].full=player;
                			strcpy(game_map[x+i][y+j].name,name);
            	    		ok++;
            	    		add_cell(*list,neww);
						}
						if(ok==0)
            			{
            	    		printf("Enter the name of the %d'th new cells:",ok+1);
                			gets(name);
                			*list=new_cell(x+i,y+j,name,40);
                			game_map[x+i][y+j].energy=40;
                			game_map[x+i][y+j].full=player;
                			strcpy(game_map[x+i][y+j].name,name);
            	    		ok++;
            	    	}
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
    		*list=NULL;
    		ok=0;
    		char name[15];
    		for(i=-1;i<=1;i++)
    		{
        		for(j=-1;j<=1;j++)
        		{
            		if(x+i<=size && x+i>0 && y+j<=size && y+j>0 && game_map[x+i][y+j].full==0 && map[x+i][y+j]!='3' && i+j!=-2 && 5*i+j!=4)
           			{
            	    	if(ok==1)
            	    	{
            	    		printf("Enter the name of the %d'th new cells:",ok+1);
                			gets(name);
                			cell *neww=new_cell(x+i,y+j,name,40);
                			game_map[x+i][y+j].energy=40;
                			game_map[x+i][y+j].full=player;
                			strcpy(game_map[x+i][y+j].name,name);
            	    		ok++;
            	    		add_cell(*list,neww);
						}
						if(ok==0)
            			{
            	    		printf("Enter the name of the %d'th new cells:",ok+1);
                			gets(name);
                			*list=new_cell(x+i,y+j,name,40);
                			game_map[x+i][y+j].energy=40;
                			game_map[x+i][y+j].full=player;
                			strcpy(game_map[x+i][y+j].name,name);
            	    		ok++;
            	    	}
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
}
