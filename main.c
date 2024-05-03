#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "libs/data_structures/matrix/matrix.h"


void fillMatrix(matrix *m, int start_value) {
    for (int i = 0; i < (*m).nRows; i++) {
        for (int j = 0; j < (*m).nCols; j++) {
            (*m).values[i][j] = i + j + start_value;
        }
    }
}

void fillRandomMatrix(matrix *m, int start_value) {
    for (int i = 0; i < (*m).nRows; i++) {
        for (int j = 0; j < (*m).nCols; j++) {
            int r = rand();
            (*m).values[i][j] = r;
        }
    }
}


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
        fillMatrix(&ms[k], k * 10);
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

void test_insertionSortRowsMatrixByRowCriteria() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 9, 6, 2,
                    13, 8, 9, 18,
                    4, 5, 8, 3,
                    1, 5, 17, 16,
            },
            4, 4
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 9, 6, 2,
                    4, 5, 8, 3,
                    1, 5, 17, 16,
                    13, 8, 9, 18,
            },
            4, 4
    );

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    29, 9, 6, 2,
                    4, 5, 8, 3,
                    1, 5, 17, 16,
                    13, 8, 9, 18,
            },
            4, 4
    );
    insertionSortRowsMatrixByRowCriteria(m1, &getSum);

    bool res1 = areTwoMatricesEqual(&m1, &m2);
    assert(res1);

    bool res2 = areTwoMatricesEqual(&m1, &m3);
    assert(!res2);
}

void test_selectionSortColsMatrixByColCriteria() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 9, 6, 2,
                    13, 8, 9, 18,
                    4, 5, 8, 3,
                    1, 5, 17, 16,
            },
            4, 4
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 9, 2, 6,
                    13, 8, 18, 9,
                    4, 5, 3, 8,
                    1, 5, 16, 17,
            },
            4, 4
    );

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    29, 9, 6, 2,
                    4, 5, 8, 3,
                    1, 5, 17, 16,
                    13, 8, 9, 18,
            },
            4, 4
    );

    selectionSortColsMatrixByColCriteria(m1, &getSum);

    bool res1 = areTwoMatricesEqual(&m1, &m2);
    assert(res1);

    bool res2 = areTwoMatricesEqual(&m1, &m3);
    assert(!res2);
}

bool test_isSquareMatrix() {
    matrix m1 = getMemMatrix(3, 3);
    matrix m2 = getMemMatrix(9, 3);

    bool res1 = isSquareMatrix(&m1);
    assert(res1);

    bool res2 = isSquareMatrix(&m2);
    assert(!res2);
}

bool test_areTwoMatricesEqual() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3
    );

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    29, 9, 6, 2,
                    4, 5, 8, 3,
                    1, 5, 17, 16,
                    13, 8, 9, 18,
            },
            4, 4
    );

    bool res1 = areTwoMatricesEqual(&m1, &m2);
    assert(res1);

    bool res2 = areTwoMatricesEqual(&m1, &m3);
    assert(!res2);
}

bool test_isEMatrix() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1,
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3
    );

    bool res1 = isEMatrix(&m1);
    assert(res1);

    bool res2 = isEMatrix(&m2);
    assert(!res2);
}

bool test_isSymmetricMatrix() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    2, 1, 5,
                    1, 3, 6,
                    5, 6, 4,
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 4, 7,
                    2, 5, 8,
                    3, 6, 9,
            },
            3, 3
    );

    bool res1 = isSymmetricMatrix(&m1);
    assert(res1);

    bool res2 = isSymmetricMatrix(&m2);
    assert(!res2);
}

void test_transposeSquareMatrix() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3,
                    4, 5, 6,
                    7, 8, 9,
            },
            3, 3
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 4, 7,
                    2, 5, 8,
                    3, 6, 9,
            },
            3, 3
    );

    matrix m3 = createMatrixFromArray(
            (int[]) {
                    1, 0, 0,
                    0, 1, 0,
                    0, 0, 1,
            },
            3, 3
    );

    transposeSquareMatrix(&m1);

    bool res1 = areTwoMatricesEqual(&m1, &m2);
    assert(res1);

    bool res2 = areTwoMatricesEqual(&m1, &m3);
    assert(!res2);
}

void test_transposeMatrix() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    1, 2, 3, 4,
                    5, 6, 7, 8,
            },
            2, 4
    );

    matrix m2 = createMatrixFromArray(
            (int[]) {
                    1, 5,
                    2, 6,
                    3, 7,
                    4, 8,
            },
            4, 2
    );

    transposeMatrix(&m1);

    bool res1 = areTwoMatricesEqual(&m1, &m2);
    assert(res1);
}

void test_getMinValuePos() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 4, 5,
                    6, 7, 1,
                    8, 11, 14,
            },
            3, 3
    );

    position res = getMinValuePos(m1);
    assert(res.rowIndex == 1 && res.colIndex == 2);
}

void test_getMaxValuePos() {
    matrix m1 = createMatrixFromArray(
            (int[]) {
                    3, 4, 5,
                    6, 7, 1,
                    14, 11, 8,
            },
            3, 3
    );

    position res = getMaxValuePos(m1);
    assert(res.rowIndex == 2 && res.colIndex == 0);
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
    test_insertionSortRowsMatrixByRowCriteria();
    test_selectionSortColsMatrixByColCriteria();
    test_isSquareMatrix();
    test_areTwoMatricesEqual();
    test_isEMatrix();
    test_isSymmetricMatrix();
    test_transposeSquareMatrix();
    test_transposeMatrix();
    test_getMinValuePos();
    test_getMaxValuePos();
}


    int main() {
        test();

    return 0;
}
