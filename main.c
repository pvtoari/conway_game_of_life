//TO DO:
// - Read a .txt with the grid to get the base plan (min 3*3)
// - Cell life rules
//      - /!\ overflow for checking around
// - Print it on screen

#include <stdio.h>

#define COL 3
#define ROW 3
#define GEN 10

void check_neihbours(int grid[COL][ROW],int i, int j,int *pt){
        
        for(int ai=-1;ai<2;ai++){
            if(i+ai <0 || i+ai >= ROW )continue;
            for(int aj=-1;aj<2;aj++){
                if(j+aj <0 || j+aj >= COL || (aj == 0 && ai == 0))continue;
                if(grid[i+ai][j+aj] == 1 ) (*pt)++;
            }

        }
        //printf("neighbours: %d for cell [%d,%d]\n",*pt,i,j);
}

int main(){
    int neighbours, n=0, u;
    int grid[COL][ROW] = {{1,1,0},{1,1,1},{0,0, 0}};
    int buffer[COL][ROW]={{0,0,0},{0,0,0},{0,0, 0}};



   while(n<GEN){
        for(int i=0;i < COL; i++){
            for(int j=0;j< ROW;j++){
                neighbours = 0;
                check_neihbours(grid, i, j, &neighbours);

                switch (neighbours) {
                    case 2:
                        if(grid[i][j] == 0) buffer[i][j] = 0;
                        else buffer[i][j] = 1;
                    case 3:
                    if(grid[i][j] == 0 && neighbours == 3) buffer[i][j] = 1;
                        break;
                    default:
                        buffer[i][j] = 0;
                    break;
                }
                
            }
        }
        u=0;
        for(int i = 0;i< COL; i++){
            for(int j=0;j<ROW;j++){
                if(buffer[i][j]==1)u++;
                printf("%d",buffer[i][j]);
                grid[i][j] = buffer[i][j];
            }
            printf("\n");
        }
        if(u == 0){
            printf("\nSimulación acabada a la gen: %d\n",n+1);
            break;
        }
        printf("\nSimulación nº%d\n",n+1);
        n++;
    }




    return 0;
}