#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"


void swap(int *a, int *b, matrix *m, int col1, int col2) {
    int temp = *a;
    *a = *b;
    *b = temp;

    for (int i = 0; i < m->nRows; i++) {
        int *row = m->values[i];

        int temp2 = row[col1];
        row[col1] = row[col2];
        row[col2] = temp2;
    }
}

void insertionSortBySumRows(int *rows, matrix *m) {
    for (size_t i = 1; i < m->nRows; i++) {
        int t = rows[i];
        int *row = m->values[i];
        int j = i;
        while (j > 0 && rows[j - 1] > t) {
            rows[j] = rows[j - 1];
            m->values[j] = m->values[j - 1];
            j--;
        }
        rows[j] = t;
        m->values[j] = row;
    }
}

void selectionSortBySumCols(int *a, matrix *m) {
    for (int i = 0; i < m->nCols - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < m->nCols; j++)
            if (a[j] < a[minPos])
                minPos = j;
        swap(&a[i], &a[minPos], m, i, minPos);
    }
}


matrix getMemMatrix(int nRows, int nCols) {
    int **values = (int **) malloc(sizeof(int*) * nRows);
    for (int i = 0; i < nRows; i++)
        values[i] = (int *) malloc(sizeof(int) * nCols);
    return (matrix){values, nRows, nCols};
}


matrix *getMemArrayOfMatrices(int nMatrices, int nRows, int nCols) {
    matrix *ms = (matrix*) malloc(sizeof(matrix) * nMatrices);
    for (int i = 0; i < nMatrices; i++)
        ms[i] = getMemMatrix(nRows, nCols);
    return ms;
}


void freeMemMatrix(matrix *m) {
    for(int i = 0; i < m->nRows; i++) {
        free(m->values[i]);
    }

    free(m->values);

    m->values = NULL;
    m->nRows = 0;
    m->nCols = 0;
}


void freeMemMatrices(matrix *ms, int nMatrices) {
    for (int i = 0; i < nMatrices; i++) {
        freeMemMatrix(&ms[i]);
    }
}


void inputMatrix(matrix *m) {
    for(int i = 0; i < m->nRows; i++) {
        int *row = m->values[i];
        for(int j = 0; j < m->nCols; j++) {
            scanf("%d", &row[j]);
        }
    }
}


void outputMatrixSum(matrix m, bool showSum) {
    for (int i = 0; i < m.nRows; i++) {
        int sum = 0;
        for (int i = 0; i < m.nRows; i++) {
            for (int j = 0; j < m.nCols; j++) {
                printf("%d\t", m.values[i][j]);
                sum += m.values[i][j];
            }
            if (showSum) {
                printf("=%d\n", sum);
            } else {
                printf("\n");
            }
        }
    }
}


void outputMatrix(matrix m) {
    outputMatrixSum(m, false);
}


void inputMatrices(matrix *ms, int nMatrices) {
    for (int a = 0; a < nMatrices; a++) {
        inputMatrix(&ms[a]);
    }
}


void outputMatrices(matrix *ms, int nMatrices) {
    for (int a = 0; a < nMatrices; a++) {
        outputMatrix(ms[a]);
        printf("\n");
    }
}


void swapRows(matrix m, int i1, int i2) {
    if ((i1 >= m.nRows) || (i2 >= m.nRows)) {
        fprintf(stderr, "matrix index out of bounds");
        exit(1);
    }

    int *temp = m.values[i1];
    m.values[i1] = m.values[i2];
    m.values[i2] = temp;
}

void swapColumns(matrix m, int j1, int j2) {
    for (int i = 0; i < m.nCols; i++) {
        int temp = m.values[i][j1];
        m.values[i][j1] = m.values[i][j2];
        m.values[i][j2] = temp;
    }
}


int getSum(int *a, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

int getSumCol(int **values, int nRows, int n) {
    int sum = 0;
    for (int i = 0; i < nRows; i++) {
        int *row = values[i];
        sum += row[n];
    }
    return sum;
}

void insertionSortRowsMatrixByRowCriteria(matrix m, int (*criteria)(int*, int)) {
    int arr[m.nRows];

    for (int i = 0; i < m.nRows; i++) {
        int sum = criteria(m.values[i], m.nCols);
        arr[i] = sum;
    }
    insertionSortBySumRows(arr, &m);
}

void selectionSortColsMatrixByColCriteria(matrix m, int (*criteria)(int*, int)) {
    bool debug = false;
    int arr[m.nCols];

    for (int i = 0; i < m.nCols; i++) {
        int col[m.nRows];

        for (int j = 0; j < m.nRows; j++) {
            int *row = m.values[j];
            col[j] = row[i];
        }

        int sum = criteria(col, m.nRows);
        arr[i] = sum;
        if (debug) {
            printf("%d\t", sum);
        }
    }
    if (debug) {
        printf("\n");
    }
    selectionSortBySumCols(arr, &m);
}


bool isSquareMatrix(matrix *m) {
    return m->nRows == m->nCols;
}

bool areTwoMatricesEqual(matrix *m1, matrix *m2) {
    if (m1->nRows != m2->nRows) {
        return false;
    }
    if (m1->nCols != m2->nCols) {
        return false;
    }

    for (int i = 0; i < m1->nRows; i++) {
        int *row1 = m1->values[i];
        int *row2 = m2->values[i];

        int res = memcmp(row1, row2, sizeof(int) * m1->nCols);

        if (res) {
            return false;
        }
    }
    return true;
}


bool isEMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return false;
    }
    for (int i = 0; i < m->nRows; i++) {
        int *row = m->values[i];
        for (int j = 0; j < m->nCols; j++) {
            if (i == j) {
                if(row[j] != 1) {
                    return false;
                }
            } else {
                if(row[j] != 0) {
                    return false;
                }
            }
        }
    }
    return true;

}


bool isSymmetricMatrix(matrix *m) {
    if (m->nRows != m->nCols) {
        return false;
    }

    for (int i = 0; i < m->nRows; i++) {
        for (int j = 0; j < m->nCols; j++) {
            if (m->values[i][j] != m->values[j][i]) {
                return false;
            }
        }
    }
    return true;
}