
#define SCAFE_ACTIVE

#include "scafe_configured.h"

int main(int argc, char** argv) {

    int rows = 5;
    int cols = 4;

    int* mat = scafe_alloc_int_2d(rows, cols);


//     int* arr = scafe_alloc_int_1d(12);
//     int* arr2 = scafe_alloc_int_1d(0);
    //int* arr3 = scafe_alloc_int(-1);


    for (int i=0; i<rows; ++i) {
        for (int j=0; j<=cols; ++j) {

            // mat[i*cols+j] = i+j;
            scafe_set_int_2d(mat, rows, cols, i, j, i+j);

        }
    }





//     scafe_free_int(&arr);
//     scafe_free_int(&arr);
//
//     scafe_free_int(&arr2);
    //scafe_free_int(&arr3);

    scafe_free_int(&mat);

    return 0;
}
