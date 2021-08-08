#ifndef SCAFE_ARRAYS_H
#define SCAFE_ARRAYS_H

// for printf, stderr
#include <stdio.h>
#include <stdlib.h>

// include predefined SCAFE macros
#include "scafe/scafe_array_basics.h"

// configure SCAFE array access
#define SCAFE_ORDER SCAFE_ROW_MAJOR

// primitive error handling: print to stderr
void scafe_error(const char* what) {
    fprintf(stderr, "error: %s\n", what);
}

// include main SCAFE array access library
#include "scafe/scafe_array_access.h"

#endif // SCAFE_ARRAYS_H
