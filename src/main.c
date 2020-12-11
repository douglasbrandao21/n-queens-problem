#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int numberOfSolutions = 0;
int boardDimension;

struct Node {
	int board[32][32];
	struct Node* next;
};

// List to store the solutions and show them later.
struct Node* head = NULL;

/**
  * Function that append a solution to the list of the solutions
  * 
  * @param board[]: current state of the board.
*/
void append(int board[boardDimension][boardDimension]) {
   struct Node* node = (struct Node*) malloc(sizeof(struct Node));

   struct Node *last = head;

   for(int row = 0; row < boardDimension; row++)
       for(int column = 0; column < boardDimension; column++)
           node->board[row][column] = board[row][column];
       

   node->next = NULL;

   if (head == NULL) {
       head = node;

       return;
   }

   while (last->next != NULL)
       last = last->next;

   last->next = node;

   return;
}


/**
  * Function to write all the solutions saved in the file.
*/
void showSolutions() {
    FILE *file = fopen("./rainha.out.txt", "w");

    fprintf(file, "Total of soluction matrices: %d\n\n", numberOfSolutions);

    while (head != NULL) {
        for(int row = 0; row < boardDimension; row++) {
            for(int column = 0; column < boardDimension; column++)
                fprintf(file, "%d ", head->board[row][column]);
        
            fprintf(file, "\n");
        }

        fprintf(file, "\n\n");
        
        head = head->next;
    }
}


/**
  * Function that verify if the queen can be safely placed in the position.
  * 
  * @param board[]: current state of the board.
  * @param row: row coordinate of the position
  * @param column: column coordinate of the position
  * 
  * @return true, if the queen can be placed safely
  * @return false, if the queen can't be placed safely
*/
bool safeToPlace(int board[boardDimension][boardDimension], int row, int column) {
    int rowIndex, columnIndex;
 
    for (rowIndex = 0; rowIndex < column; rowIndex++)
        if (board[row][rowIndex])
            return false;
 
    for (rowIndex=row, columnIndex=column; rowIndex>=0 && columnIndex>=0; rowIndex--, columnIndex--)
        if (board[rowIndex][columnIndex])
            return false;
 
    for (rowIndex=row, columnIndex=column; columnIndex>=0 && rowIndex < boardDimension; rowIndex++, columnIndex--)
        if (board[rowIndex][columnIndex])
            return false;
 
    return true;
}


/**
  * Recursive function that checks if there is a solution through Backtracking.
  * 
  * @param board[]: current state of the board.
  * @param currentColumn: verification column (where we'll look for a place to put the queen safely)
  * 
  * @return true, if exists a solution and false if the solution not exists.
*/
bool existSolution(int board[boardDimension][boardDimension], int currentColumn) {
    if (currentColumn == boardDimension) {
        numberOfSolutions++;

        append(board);

        return true;
    }

    bool hasSolution = false;

    for (int row = 0; row < boardDimension; row++) {
        if (safeToPlace(board, row, currentColumn)) {
            board[row][currentColumn] = 1;
 
            hasSolution = existSolution(board, currentColumn + 1) || hasSolution;

            board[row][currentColumn] = 0;
        }
    }

    return hasSolution;
}


/**
  * This function read the board dimensions and check whether they are valid.
  * If they're valid, the function stores the board dimensions.
  * If not, the function show a error message.
*/
bool validDimensions() {
    printf("Enter the board dimension: ");
    scanf("%d", &boardDimension);

    if(boardDimension < 4 || boardDimension > 32) {
        printf("\nYour input is out of range.\n");

        return false;
    }
}
 

int main() {
    if(validDimensions()) {
        int board[boardDimension][boardDimension];

        // Setting all the matrix positions to 0
        for(int row = 0; row < boardDimension; row++)
            for(int column = 0; column < boardDimension; column++)
                board[row][column] = 0;
 
        if (existSolution(board, 0) == false)
            printf("Solution does not exist");

        showSolutions();
    }

    return 0;
}