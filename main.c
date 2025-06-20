#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


//configure windows for ansi escape sequence terminal

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _WIN32
// Some old MinGW/CYGWIN distributions don't define this:
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

static HANDLE stdoutHandle;
static DWORD outModeInit;

void setupConsole(void) {
	DWORD outMode = 0;
	stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	if(stdoutHandle == INVALID_HANDLE_VALUE) {
		exit(GetLastError());
	}
	
	if(!GetConsoleMode(stdoutHandle, &outMode)) {
		exit(GetLastError());
	}

	outModeInit = outMode;
	
    // Enable ANSI escape codes
	outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

	if(!SetConsoleMode(stdoutHandle, outMode)) {
		exit(GetLastError());
	}	
}

void restoreConsole(void) {
    // Reset colors
    printf("\x1b[0m");	
	
    // Reset console mode
	if(!SetConsoleMode(stdoutHandle, outModeInit)) {
		exit(GetLastError());
	}
}


#else
void setupConsole(void) {}
void restoreConsole(void) {}
#endif

#define SLP 1
#define COL 25
#define ROW 25
#define GEN 100


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
    
    if((fptr = fopen("save", "r") ) == NULL){
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
    int u =0,s =0;
    printf("\x1b[2J");
    printf("\x1b[H");
    
    for(int i=-2;i<=COL;i++){
        printf("\x1b[1;47m  \x1b[0m");
    }
    printf("\n");
    for(int i = 0;i< COL; i++){
        printf("\x1b[1;47m  \x1b[0m ");
        for(int j=0;j<ROW;j++){
            if(buffer[i][j] == grid[i][j]) s++;
            if(buffer[i][j]=='1'){
                u++;
                printf("\x1b[1;47m  \x1b[0m");
            }
            else printf("  ");
            grid[i][j] = buffer[i][j];
        }
        printf(" \x1b[1;47m  \x1b[0m");
        printf("\n");
    }

    for(int i=-2;i<=COL;i++){
        printf("\x1b[1;47m  \x1b[0m");
    }

    *g +=1;
    
    
        if(u == 0 || s == ROW*COL){
            printf("\nSimulación acabada a la gen: %d\n",*g);
            sleep(SLP);
            return -1;
        }
        printf("\nSimulación nº%d\n",*g);
    
    sleep(SLP);
    
    return 0;
}

int main(){
    printf("\x1b[=14h");
    printf("\x1b[?47h"); //save scren
    printf("\x1b[2J");  //clear screen
    setupConsole();
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
        if(print_gen(&g) == -1){
            printf("\x1b[2J");
            restoreConsole();
            printf("\x1b[?47l"); //restore screen
            return -1;}
    }
    return 0;
}