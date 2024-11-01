#include <stdio.h>
#include <stdbool.h>

#define SIZE 24
#define nRows 8
#define nCols 3

void print_array(int array[], int length);
void print_matrix(int mat[][nCols], int rows);
bool isValid(const int arr[], int length, int pos);
void remove_element(int arr[], int length, int pos);
void insert_element(int arr[], int length, int pos, int value);

int main() {
    int arr[SIZE] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 
                     130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240};
    int arr2d[nRows][nCols] = {0};

    printf("Initial array:\n");
    print_array(arr, SIZE);

    printf("\nRemoving element at position 2:\n");
    remove_element(arr, SIZE, 2);
    print_array(arr, SIZE);

    printf("\nInserting value 500 at position 2:\n");
    insert_element(arr, SIZE, 2, 500);
    print_array(arr, SIZE);

    printf("\nAttempting to insert at invalid position 30:\n");
    insert_element(arr, SIZE, 30, 500);

    printf("\nAttempting to remove at invalid position 30:\n");
    remove_element(arr, SIZE, 30);

    return 0;
}

void print_array(int array[], int length) {
    for (int i = 0; i < length; i++) {
        printf("array[%d] = %d\n", i, array[i]);
    }
}

void print_matrix(int mat[][nCols], int rows) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < nCols; j++) {
            printf("mat[%d][%d] = %d ", i, j, mat[i][j]);
        }
        puts("");
    }
}

bool isValid(const int arr[], int length, int pos) {
    return pos >= 0 && pos < length;
}

void remove_element(int arr[], int length, int pos) {
    if (!isValid(arr, length, pos)) {
        printf("Error: Position %d is out of bounds.\n", pos);
        return;
    }
    for (int i = pos; i < length - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[length - 1] = 0;
}

void insert_element(int arr[], int length, int pos, int value) {
    if (!isValid(arr, length, pos)) {
        printf("Error: Position %d is out of bounds.\n", pos);
        return;
    }
    for (int i = length - 1; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
}
