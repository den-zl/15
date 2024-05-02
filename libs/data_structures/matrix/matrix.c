#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

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


void outputMatrix(matrix m) {
    for(int i = 0; i < m.nRows; i++) {
        for(int j = 0; j < m.nCols; j++) {
            printf("%d ", m.values[i][j]);
        }
        printf("\n");
    }
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