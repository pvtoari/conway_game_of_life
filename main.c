//TO DO:
// X Read a file with the grid to get the base plan (256*256)
// X Cell life rules 
//      X /!\ overflow for checking around
// X Print it on screen

#include <stdlib.h>
#include <stdio.h>

#define SQR 
#define COL 5
#define ROW 5
#define GEN 6

char grid[COL][ROW], buffer[COL][ROW];

void check_neihbours(int i, int j,int *pt);
void read_input();
int print_gen(int *g);

void check_neihbours(int i, int j,int *pt){
        for(int ai=-1;ai<2;ai++){
            if((i)+ai <0 || i+ai >= ROW )continue;
            for(int aj=-1;aj<2;aj++){
                if(j+aj <0 || j+aj >= COL || (aj == 0 && ai == 0))continue;
                if(grid[i+ai][j+aj] == '1' ) (*pt)++;
            }
        }
}

void read_input(){
    int i =0;
    FILE *fptr;
    
    if((fptr = fopen("in", "r") ) == NULL){
        printf("File could not be openned\n");
        exit(-1);
    }

    while(fgets(grid[i], ROW+1, fptr) != NULL){
        if(sizeof(grid[i])/sizeof(char) != ROW){
            printf("Bad grid format\n");
            exit(-2);
        }
        fseek(fptr, 1, SEEK_CUR);
        i++;
    }

    fclose(fptr);
}

int print_gen(int *g){
    int u =0;

    for(int i = 0;i< COL; i++){
        for(int j=0;j<ROW;j++){
            if(buffer[i][j]=='1')u++;
            printf("%c",buffer[i][j]);
            grid[i][j] = buffer[i][j];
        }
        printf("\n");
    }
    *g +=1;
        if(u == 0){
            printf("\nSimulación acabada a la gen: %d\n",*g);
            return -1;
        }
        printf("\nSimulación nº%d\n",*g);
    
    return 0;
}

int main(){
    int neighbours, g=0;
    read_input();
    for(int i = 0; i<COL;i++){
        for(int j=0;j<ROW;j++){
            printf("%c",grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
    while(g<GEN){
        for(int i=0;i < COL; i++){
            for(int j=0;j< ROW;j++){
                neighbours = 0;
                check_neihbours(i, j, &neighbours);

                switch (neighbours) {
                    case 2:
                        if(grid[i][j] == '0') buffer[i][j] = '0';
                        else buffer[i][j] = '1';
                        break;
                    case 3:
                        if(grid[i][j] == '0' && neighbours == 3) buffer[i][j] = '1';
                        if(grid[i][j] == '1') buffer[i][j]='1';
                        break;
                    default:
                        buffer[i][j] = '0';
                    break;
                }
            }
        }
        if(print_gen(&g) == -1) return -1;
    }
    return 0;
}