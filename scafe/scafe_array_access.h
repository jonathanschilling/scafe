#ifndef SCAFE_ARRAY_ACCESS_H
#define SCAFE_ARRAY_ACCESS_H

#include "scafe_array_basics.h"

#ifndef SCAFE_ORDER
#error SCAFE_ORDER undefined (SCAFE_ROW_MAJOR or SCAFE_COL_MAJOR)
#elif ((SCAFE_ORDER!=SCAFE_ROW_MAJOR)&&(SCAFE_ORDER!=SCAFE_COL_MAJOR))
#error SCAFE_ORDER needs to be one of SCAFE_ROW_MAJOR or SCAFE_COL_MAJOR
#endif

#ifdef SCAFE_ACTIVE
int scafe_check_size(const int size) {
    if (size <= 0) {
        scafe_error("non-positive size");
        return 1;
    }
    return 0;
}

int scafe_check_index(const int size, const int index) {
    if (index < 0) {
        scafe_error("negative index");
        return 1;
    } else if (index > size-1) {
        scafe_error("index out of range");
        return 1;
    }
    return 0;
}
#endif // SCAFE_ACTIVE

// _scafe_alloc_int
#ifdef SCAFE_ACTIVE
int* _scafe_alloc_int(int size) {
    if (scafe_check_size(size)) {
        return 0x0;
    }
    int* mem = (int*) malloc(size*sizeof(int));
    if (mem == 0x0) {
        scafe_error("allocation error; out of memory?");
        return 0x0;
    }
    return mem;
}
#else // SCAFE_ACTIVE
#define _scafe_alloc_int(size) \
        (int*)malloc((size)*sizeof(int))
#endif // SCAFE_ACTIVE

// scafe_alloc_int_1d
#ifdef SCAFE_ACTIVE
int* scafe_alloc_int_1d(int size) {
    if (scafe_check_size(size)) {
        return 0x0;
    }
    return _scafe_alloc_int(size);
}
#else // SCAFE_ACTIVE
#define scafe_alloc_int_1d(size) \
        (int*)malloc((size)*sizeof(int))
#endif // SCAFE_ACTIVE

// scafe_alloc_int_2d
#ifdef SCAFE_ACTIVE
int* scafe_alloc_int_2d(int rows, int cols) {
    if (scafe_check_size(rows)) {
        return 0x0;
    }
    if (scafe_check_size(cols)) {
        return 0x0;
    }
    return _scafe_alloc_int(rows*cols);
}
#else // SCAFE_ACTIVE
#define scafe_alloc_int_2d(rows, cols) \
        (int*)malloc((rows)*(cols)*sizeof(int))
#endif // SCAFE_ACTIVE

// scafe_set_int_2d
#ifdef SCAFE_ACTIVE
void scafe_set_int_2d(int* arr,
                      int numRows, int numCols,
                      int row,     int col,
                      int value) {

    if (arr == 0x0) {
        scafe_error("target array not allocated");
        return;
    }

    int indexError = 0;
    indexError |= scafe_check_size(numRows);
    indexError |= scafe_check_size(numCols);
    indexError |= scafe_check_index(numRows, row);
    indexError |= scafe_check_index(numCols, col);
    if (indexError != 0) {
        return;
    }

#if SCAFE_ORDER==SCAFE_ROW_MAJOR
    arr[row*numCols+col] = value;
#elif SCAFE_ORDER==SCAFE_COL_MAJOR
    arr[col*numRows+row] = value;
#endif // SCAFE_ORDER
}
#else // SCAFE_ACTIVE
#if SCAFE_ORDER==SCAFE_ROW_MAJOR
#define scafe_set_int_2d(arr, numRows, numCols, row, col, value) \
        (arr)[(row)*(numCols)+(col)]=(value)
#elif SCAFE_ORDER==SCAFE_COL_MAJOR
#define scafe_set_int_2d(arr, numRows, numCols, row, col, value) \
        (arr)[(col)*(numRows)+(row)]=(value)
#endif // SCAFE_ORDER
#endif // SCAFE_ACTIVE

// scafe_get_int_2d
#ifdef SCAFE_ACTIVE
int scafe_get_int_2d(int* arr,
                     int numRows, int numCols,
                     int row,     int col) {

    if (arr == 0x0) {
        scafe_error("source array not allocated");
        return 0;
    }

    int indexError = 0;
    indexError |= scafe_check_size(numRows);
    indexError |= scafe_check_size(numCols);
    indexError |= scafe_check_index(numRows, row);
    indexError |= scafe_check_index(numCols, col);
    if (indexError != 0) {
        return 0;
    }

#if SCAFE_ORDER==SCAFE_ROW_MAJOR
    return arr[row*numCols+col];
#elif SCAFE_ORDER==SCAFE_COL_MAJOR
    return arr[col*numRows+row];
#endif // SCAFE_ORDER
}
#else // SCAFE_ACTIVE
#if SCAFE_ORDER==SCAFE_ROW_MAJOR
#define scafe_get_int_2d(arr, numRows, numCols, row, col) \
        (arr)[(row)*(numCols)+(col)]
#elif SCAFE_ORDER==SCAFE_COL_MAJOR
#define scafe_get_int_2d(arr, numRows, numCols, row, col) \
        (arr)[(col)*(numRows)+(row)]
#endif // SCAFE_ORDER
#endif // SCAFE_ACTIVE



// scafe_free_int
#ifdef SCAFE_ACTIVE
void scafe_free_int(int** mem) {
    if (*mem != 0x0) {
        free(*mem);
        *mem = 0x0;
    } else {
        scafe_error("tried to free null pointer");
    }
}
#else // SCAFE_ACTIVE
#define scafe_free_int(mem) \
        free(*mem)
#endif // SCAFE_ACTIVE









#endif // SCAFE_ARRAY_ACCESS_H
