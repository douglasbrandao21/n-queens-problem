#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int numberOfSolutions = 0;
int boardDimension;

struct Node {
	int board[32][32];
	struct Node* next;
};

struct Node* head = NULL;

void append(struct Node** head_reference, int board[boardDimension][boardDimension]) {
   struct Node* node = (struct Node*) malloc(sizeof(struct Node));

   struct Node *last = *head_reference;

   for(int row = 0; row < boardDimension; row++)
       for(int column = 0; column < boardDimension; column++)
           node->board[row][column] = board[row][column];
       

   node->next = NULL;

   if (*head_reference == NULL) {
       *head_reference = node;

       return;
   }

   while (last->next != NULL)
       last = last->next;

   last->next = node;

   return;
}

void show(struct Node *node) {
    FILE *file = fopen("./files/rainha.out.txt", "w");

    fprintf(file, "Número de matrizes solução encontradas: %d\n", numberOfSolutions);


   while (node != NULL) {
       for(int row = 0; row < boardDimension; row++) {
           for(int column = 0; column < boardDimension; column++)
               fprintf(file, "%d ", node->board[row][column]);
    
           fprintf(file, "\n");
       }

       fprintf(file, "\n\n");
       
       node = node->next;
   }
}


void writeSolution(int board[boardDimension][boardDimension]) {    
    for (int row = 0; row < boardDimension; row++) {
        for (int column = 0; column < boardDimension; column++)
            printf(" %d ", board[row][column]);

        printf("\n");
    }

    printf("\n");
}

bool canBePlaced(int board[boardDimension][boardDimension], int row, int column) {
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
 
bool verifySolution(int board[boardDimension][boardDimension], int currentColumn) {
    if (currentColumn == boardDimension) {
        numberOfSolutions++;

        append(&head, board);

        return true;
    }

    bool hasSolution = false;

    for (int row = 0; row < boardDimension; row++) {
        if (canBePlaced(board, row, currentColumn)) {
            board[row][currentColumn] = 1;
 
            hasSolution = verifySolution(board, currentColumn + 1) || hasSolution;

            board[row][currentColumn] = 0;
        }
    }

    return hasSolution;
}

void calculateQueensPositions() {
    int board[boardDimension][boardDimension];

    for(int row = 0; row < boardDimension; row++)
      for(int column = 0; column < boardDimension; column++)
        board[row][column] = 0;
 
    if (verifySolution(board, 0) == false)
        printf("Solution does not exist");

    show(head);
}

bool setBoardDimension() {
    printf("Enter the board dimension: ");
    scanf("%d", &boardDimension);

    if(boardDimension < 4 || boardDimension > 32) {
        printf("\nYour input is out of range.\n");

        return false;
    }
}
 

int main() {
    if(setBoardDimension()) {
        calculateQueensPositions();

    }

    return 0;
}