#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"


void fillMatrix(matrix *m, int start_value);

matrix test_getMemMatrix() {
    matrix m = getMemMatrix(3, 3);

    assert(m.nCols == 3);
    assert(m.nRows == 3);
}

matrix test_getMemArrayOfMatrices() {
    matrix *ms = getMemArrayOfMatrices(3, 2, 2);

    for (int i = 0; i < **ms->values; i++) {
        assert(&ms[i] != NULL);
        assert(&ms->values[i] != NULL);
        assert(ms->nCols == 2);
        assert(ms->nRows == 2);
    }
}

void test_freeMemMatrix() {
    matrix m = getMemMatrix(3, 3);

    freeMemMatrix(&m);

    assert(m.values == NULL);
    assert(m.nRows == 0);
    assert(m.nCols == 0);
}

void test_freeMemMatrices() {
    matrix *ms = getMemArrayOfMatrices(3, 2, 2);

    freeMemMatrices(ms, 3);

    for (int i = 0; i < 3; i++) {
        assert(ms[i].values == NULL);
        assert(ms[i].nCols == 0);
        assert(ms[i].nRows == 0);
    }
}

void test_inputMatrix() {
    matrix m = getMemMatrix(3, 3);

    inputMatrix(&m);

    for (int i = 0; i < m.nRows; i++) {
        for (int j = 0; j < m.nCols; j++) {
            assert(m.values != NULL);
        }
    }
}

void test_inputMatrices() {
    matrix *ms = getMemArrayOfMatrices(3, 2, 2);

    inputMatrices(ms, 3);

    for (int i = 0; i < ms->nRows; i++) {
        for (int j = 0; j < ms->nCols; j++) {
            assert(ms->values != NULL);
        }
    }
}

void test_outputMatrix() {
    matrix m = getMemMatrix(3, 3);

    fillMatrix(&m, 0);

    outputMatrix(m);
}

void test_outputMatrices() {
    matrix *ms = getMemArrayOfMatrices(3, 2, 2);

    for (int k = 0; k < 3; k++) {
        fillMatrix(&ms[k], k*10);
    }

    outputMatrices(ms, 3);
}

void test_swapRows() {
    matrix m = getMemMatrix(2, 2);

    fillMatrix(&m, 0);

    int *temp = m.values[0];

    swapRows(m, 0, 1);

    assert(m.values[0] != temp);
}

void test_swapColumns() {
    matrix m = getMemMatrix(4, 4);

    fillMatrix(&m, 0);

    int *temp = m.values[0];

    swapColumns(m, 1, 3);

    outputMatrix(m);

    assert(m.values[1] != temp);
}

void fillMatrix(matrix *m, int start_value) {
    for (int i = 0; i < (*m).nRows; i++) {
        for (int j = 0; j < (*m).nCols; j++) {
            (*m).values[i][j] = i + j + start_value;
        }
    }
}


void test() {
    test_getMemMatrix();
    test_getMemArrayOfMatrices();
    test_freeMemMatrix();
    test_freeMemMatrices();
    test_outputMatrix();
    test_outputMatrices();
    test_swapRows();
    test_swapColumns();
}


    int main() {
    test();

    return 0;
}
