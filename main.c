//TO DO:
// - Read a .txt with the grid to get the base plan (min 3*3)
// - Cell life rules
//      - /!\ overflow for checking around
// - Print it on screen

#include <stdio.h>
#include <stdlib.h>

#define COL 3
#define ROW 3
#define GEN 5


void check_neihbours(int grid[COL][ROW],int i, int j,int *pt){
    
    if( j - 1 >= 0){
            if(grid[i][j-1] == 1) (*pt)++;
    }
    if( j + 1 < ROW){
            if(grid[i][j+1] == 1) (*pt)++;
    }

    if(i - 1 >= 0 ){
        if( j - 1 >= 0){
            if(grid[i-1][j-1] == 1) (*pt)++;
        }
        if( j + 1 < ROW){
            if(grid[i-1][j+1] == 1) (*pt)++;
        }
    }
    if(i + 1 < COL){
        if( j - 1 >= 0){
            if(grid[i+1][j-1] == 1) (*pt)++;
        }
        if( j + 1 < ROW){
            if(grid[i+1][j+1] == 1) (*pt)++;
        }
    }
}

int main(){
    int neighbours, n=0, z;
    int grid[COL][ROW] = {{0,0,0},{1,1,1},{0,0, 0}};
    int buffer[COL][ROW]={{0,0,0},{0,0,0},{0,0, 0}};
    
    while(n < GEN){
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
            //prints and checks if the simulation is dead
            z = 0;
            for(int i = 0;i< COL; i++){
                for(int j=0;j<ROW;j++){
                    if(buffer[i][j] == 0) z++;
                    printf("%d",buffer[i][j]);
                    grid[i][j] = buffer[i][j];
                }
                printf("\n");
            }

            if(z == ROW*COL){
                printf("Se ha acabado la simulación a la gen %d\n",n+1);
                exit(0);
            }
            n++;
            printf("\n");

        }
    }
    return 0;
}