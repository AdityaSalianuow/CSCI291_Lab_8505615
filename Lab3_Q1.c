#include <stdio.h>
#include <stdbool.h>

#define SIZE 10

bool isValid(const int arr[], int length, int pos) {
    return (pos >= 0 && pos < length);
}

void remove_element(int arr[], int length, int pos) {
    if (!isValid(arr, length, pos)) {
        printf("Error: Index %d is out of range.\n", pos);
        return;
    }
    for (int i = pos; i < length - 1; i++) {
        arr[i] = arr[i + 1];
    }
    arr[length - 1] = 0;
}

void insert_element(int arr[], int length, int pos, int value) {
    if (!isValid(arr, length, pos)) {
        printf("Error: Index %d is out of range.\n", pos);
        return;
    }
    for (int i = length - 1; i > pos; i--) {
        arr[i] = arr[i - 1];
    }
    arr[pos] = value;
}

void reshape(const int arr[], int length, int nRows, int nCols, int arr2d[nRows][nCols]) {
    if (length != nRows * nCols) {
        printf("Error: Array size does not match matrix dimensions.\n");
        return;
    }
    int k = 0;
    for (int j = 0; j < nCols; j++) {
        for (int i = 0; i < nRows; i++) {
            arr2d[i][j] = arr[k++];
        }
    }
}

void trans_matrix(int nRows, int nCols, const int mat[nRows][nCols], int mat_transp[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            mat_transp[j][i] = mat[i][j];
        }
    }
}

bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    int arr[SIZE] = {10, 20, 30, 40, 50, 0, 0, 0, 0, 0};
    int arr2d[2][5];
    int transposed[5][2];

    printf("Testing isValid:\n");
    printf("Position 2 is %s\n", isValid(arr, SIZE, 2) ? "valid" : "invalid");
    printf("Position 10 is %s\n", isValid(arr, SIZE, 10) ? "valid" : "invalid");

    printf("\nTesting remove_element:\n");
    printf("Array before removing element at position 2:\n");
    for (int i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    printf("\n");

    remove_element(arr, SIZE, 2);
    printf("Array after removing element at position 2:\n");
    for (int i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    printf("\n");

    int arr_reset[SIZE] = {10, 20, 30, 40, 50, 0, 0, 0, 0, 0};
    for (int i = 0; i < SIZE; i++) arr[i] = arr_reset[i];

    printf("\nTesting insert_element:\n");
    printf("Array before inserting 80 at position 2:\n");
    for (int i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    printf("\n");

    insert_element(arr, SIZE, 2, 80);
    printf("Array after inserting 80 at position 2:\n");
    for (int i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    printf("\n");

    printf("\nTesting reshape:\n");
    reshape(arr, 10, 2, 5, arr2d);
    printf("Reshaped 2D array:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", arr2d[i][j]);
        }
        printf("\n");
    }

    printf("\nTesting trans_matrix:\n");
    trans_matrix(2, 5, arr2d, transposed);
    printf("Transposed 2D array:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", transposed[i][j]);
        }
        printf("\n");
    }

    printf("\nTesting found_duplicate:\n");
    bool hasDuplicate = found_duplicate(arr, SIZE);
    printf("Array has duplicates: %s\n", hasDuplicate ? "Yes" : "No");

    return 0;
}
