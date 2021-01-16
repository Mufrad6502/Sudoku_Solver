#include <stdio.h>

#define N 9

#define UNASSIGNED 0

int exists_in_row(int grid[N][N], int row, int num){
        for (int col = 0; col < 9; col++) {
                if (grid[row][col] == num) {
                        return 1;
                }
        }
        return 0;
}

int exists_in_col(int grid[N][N], int col, int num) {
        for (int row = 0; row < 9; row++) {
                if (grid[row][col] == num) {
                        return 1;
                }
        }
        return 0;
}

int exists_in_box(int grid[N][N], int startRow, int startCol, int num) {
        for (int row = 0; row < 3; row++) {
                for (int col = 0; col < 3; col++) {
                        if (grid[row + startRow][col + startCol] == num) {
                                return 1;
                        }
                }
        }
        return 0;
}

int is_safe(int grid[N][N], int row, int col, int num) {
        return !exists_in_row(grid, row, num) && !exists_in_col(grid, col, num) && !exists_in_box(grid, row - (row % 3), col - (col %3), num);
}

int find_unassigned(int grid[N][N], int *row, int *col) {
        for (*row = 0; *row < N; (*row)++) {
                for (*col = 0; *col < N; (*col)++) {
                        if (grid[*row][*col] == 0) {
                                return 1;
                        }
                }
        }
        return 0;
}

int solve_sudoku(int grid[N][N]) {
        int row = 0;
        int col = 0;

        if (!find_unassigned(grid, &row, &col)){
                return 1;
        }

        for (int num = 1; num <= N; num++ ) {

                if (is_safe(grid, row, col, num)) {
                        grid[row][col] = num;

                        if (solve_sudoku(grid)) {
                                return 1;
                        }

                        grid[row][col] = UNASSIGNED;
                }
        }

        return 0;
}

void print_sudoku(int grid[N][N]) {
        for (int row = 0; row < N; row++) {
                for (int col = 0; col < N; col++) {
                        printf("%2d", grid[row][col]);
                }
                printf("\n");
        }
}
int main() {

   int grid[N][N] = {
   { 3, 1, 6, 5, 7, 8, 4, 9, 2 },
{ 5, 2, 9, 1, 3, 4, 7, 6, 8 },
{ 4, 8, 7, 6, 2, 9, 5, 3, 1 },
{ 2, 6, 3, 0, 1, 5, 9, 8, 7 },
{ 9, 7, 4, 8, 6, 0, 1, 2, 5 },
{ 8, 5, 1, 7, 9, 2, 6, 4, 3 },
{ 1, 3, 8, 0, 4, 7, 2, 0, 6 },
{ 6, 9, 2, 3, 5, 1, 8, 7, 4 },
{ 7, 4, 5, 0, 8, 6, 3, 1, 0 },
};

        if (solve_sudoku(grid)) {
                print_sudoku(grid);
        }
        else {
                printf("no solution");
        }
        return 0;
}
