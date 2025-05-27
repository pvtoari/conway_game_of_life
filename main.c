//TO DO:
// - Read a file with the grid to get the base plan (256*256)
// X Cell life rules 
//      X /!\ overflow for checking around
// - Print it on screen

#include <stdlib.h>
#include <stdio.h>

#define COL 3
#define ROW 4
#define GEN 10

char grid[COL][ROW], buffer[COL][ROW];

void check_neihbours(int i, int j,int *pt);
void read_input();

void check_neihbours(int i, int j,int *pt){
        for(int ai=-1;ai<2;ai++){
            if((i)+ai <0 || i+ai >= ROW )continue;
            for(int aj=-1;aj<2;aj++){
                if(j+aj <0 || j+aj >= COL || (aj == 0 && ai == 0))continue;
                if(grid[i+ai][j+aj] == 1 ) (*pt)++;
            }

        }
        //printf("neighbours: %d for cell [%d,%d]\n",*pt,i,j);
}

void read_input(){
    int i =0;
    FILE *fptr;
    
    if((fptr = fopen("in", "r") ) == NULL){
        printf("File could not be openned\n");
        exit(-1);
    }

    while(fgets(grid[i], ROW, fptr) != NULL){
        if(sizeof(grid[i])/sizeof(char) != ROW){
            printf("Bad grid format\n");
            exit(-2);
        }
        i++;
    }

    fclose(fptr);


}

int main(){
    int neighbours, n=0, u;
    read_input();
    for(int i =0; i<COL;i++){
        printf("%s", grid[i]);
    }
    /*while(n<GEN){
        for(int i=0;i < COL; i++){
            for(int j=0;j< ROW;j++){
                neighbours = 0;
                check_neihbours(i, j, &neighbours);

                switch (neighbours) {
                    case 2:
                        if(grid[i][j] == '0') buffer[i][j] = '0';
                        else buffer[i][j] = '1';
                    case 3:
                    if(grid[i][j] == '0' && neighbours == 3) buffer[i][j] = '1';
                        break;
                    default:
                        buffer[i][j] = '0';
                    break;
                }
                
            }
        }
        u=0;
        for(int i = 0;i< COL; i++){
            for(int j=0;j<ROW;j++){
                if(buffer[i][j]=='1')u++;
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
    }*/
    return 0;
}