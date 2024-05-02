#include <stdio.h>
#include "libs/data_structures/matrix/matrix.h"


int main() {
    matrix m = getMemMatrix(3, 3);
    matrix *ms = getMemArrayOfMatrices(3, 2, 2);

    inputMatrices(ms, 3);
    outputMatrices(ms, 3);

    return 0;
}
