#include<time.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define MAXTOKENCOUNT 20
#define MAXTOKENLENGTH 20
#define MAXLINELENGTH 400

int rows;
int cols;
int mines;

int get_random(int range) {
	return ((int)floor((float)range*rand()/RAND_MAX))%range;
}

void getTokens(char line[], char tokens[][MAXTOKENLENGTH],int *count){
	char linecopy[MAXLINELENGTH];
	char *p;
	int tokencount;

	strcpy(linecopy,line);

	p = strtok(linecopy, " ");// initialize p to first token
	tokencount = 0;

	while (p != NULL) {
		strcpy(tokens[tokencount],p);

		p = strtok(NULL," ");
		tokencount++;
	}
}

void getLine(char line[], int maxlinelen){
	fgets(line, maxlinelen, stdin);
	int linelen = strlen(line);
	if (line[linelen-1] == '\n') line[linelen-1] = '\0';
}

struct cell {
	int position;
	int adjcount;
	int mined;
	int covered;
	int flagged;
};

typedef struct cell cell;

cell **board;

void command_new(){
	board = (cell **) malloc(sizeof(cell *) * rows);
	for (int i=0; i<rows; i++) {
		board[i] = (cell *) malloc( sizeof(cell) * cols);
	}
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			board[i][j].position = i*cols + j;
			board[i][j].adjcount = 0;
            board[i][j].mined = 0;
            board[i][j].covered = 1;
            board[i][j].flagged = 0;
		}
	}
	// add mines to cells randomly
    for (int m = 0; m < mines; m++) {
        int r, c;

        // loop until you find a row,col that doesn’t already have a mine
        do {
            r = get_random(rows);
            c = get_random(cols);
        } while (board[r][c].mined == 1);

        // place mine in cell at r,c
        board[r][c].mined = 1;
    }
    // calculate adjacency counts for cells that are not mined
    int neighborcount = 8;
    int rowneighbors[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int colneighbors[] = {0, 1, 1, 1, 0, -1, -1, -1};

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int minecount = 0;

            for (int d = 0; d < neighborcount; d++) {
                int r2 = r + rowneighbors[d];
                int c2 = c + colneighbors[d];

                // Check if r2 and c2 are valid
                if (0 <= r2 && r2 < rows && 0 <= c2 && c2 < cols) {
                    // Check if the neighbor contains a mine
                    if (board[r2][c2].mined == 1) {
                        minecount++;
                    }
                }
            }
            // Set adjcount for the cell at r and c to minecount
            board[r][c].adjcount = minecount;
        }
    }
}

void display_cell(cell *c) {
    if (c->flagged == 1) {
        printf("%2s", "P");
    } else if (c->covered == 1) {
        printf("%2s", "/");
    } else if (c->mined == 1) {
        printf("%2s", "*");
    } else if (c->adjcount > 0) {
        printf("%2d", c->adjcount);
    } else {
        printf("%2s", ".");
    }
}

void command_show(){
	for (int i=0; i<rows; i++) {
		for (int j=0; j<cols; j++) {
			display_cell(&board[i][j]);
		}
		printf("\n");
	}
}

void command_flag(int r, int c) {
    if(board[r][c].flagged == 0){
    	board[r][c].flagged = 1;
    }
    else{
    	printf("Cell is already flagged\n");
    }
}

void command_unflag(int r, int c) {
    board[r][c].flagged = 0;
}

void uncover_recursive(int r, int c) {
    board[r][c].covered = 0;

    // If adjcount is not zero stop recursion
    if (board[r][c].adjcount > 0) {
        return;
    }

    // Loop through neighbors
    int neighborcount = 8;
    int rowneighbors[] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int colneighbors[] = {0, 1, 1, 1, 0, -1, -1, -1};

    for (int d = 0; d < neighborcount; d++) {
        int nr = r + rowneighbors[d];
        int nc = c + colneighbors[d];

        // Check if neighbor n exists and is covered
        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && board[nr][nc].covered == 1) {
            uncover_recursive(nr, nc);
        }
    }
}

int processCommand(char tokens[][MAXTOKENLENGTH], int tokencount){
	if(strcmp(tokens[0], "new") == 0){
		printf("New Game Created \n" );
		rows = atoi(tokens[1]);
        cols = atoi(tokens[2]);
        mines = atoi(tokens[3]);
		command_new();
	}
	else if(strcmp(tokens[0], "quit") == 0){
		printf("Ending Game Bye! \n" );
		return 0;
	}
	else if(strcmp(tokens[0], "show") == 0){
		printf("Current Board: \n" );
		command_show();
	}
	else if (strcmp(tokens[0], "flag") == 0){
		int r = atoi(tokens[1]);
        int c = atoi(tokens[2]);
        command_flag(r, c);
    } 
    else if (strcmp(tokens[0], "unflag") == 0){
    	int r = atoi(tokens[1]);
        int c = atoi(tokens[2]);
        command_unflag(r, c);
    } 
    else if (strcmp(tokens[0], "uncover") == 0){
    	int r = atoi(tokens[1]);
        int c = atoi(tokens[2]);
        uncover_recursive(r, c);
    }
	return 1;
}

void rungame(){
	srand(time(0));
	char line[MAXLINELENGTH];
	char tokens[MAXTOKENCOUNT][MAXTOKENLENGTH];
	while (1) {
		int tokencount;
		int result;
		printf(">> ");
		getLine(line,MAXLINELENGTH);
		getTokens(line,tokens,&tokencount);
		result = processCommand(tokens,tokencount);
		if (result == 0) break;
	}
}

int main(void){
	rungame();
	return 0;
}