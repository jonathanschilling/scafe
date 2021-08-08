# scafe

`scafe` (pronounced *seɪf*) is a C library designed to safeguard array accesses at runtime with controllable performance overhead.
The basic idea is to perform array operations (de-/allocation, read/write of individual elements)
through a security layer provided by `scafe`.

* In **inactive** mode, this layer defaults to a set of preprocessor macros
  which boil down to the default un-checked behaviour of array access in C.
* In **active** mode, the `scafe` layer provides array operations
  through functions that explicitly check the size and index values for validity and compatibility.

## Basic Example

Consider a two-dimensional array laid out as a flat array of `int` in row-major order:

```C
int rows = 5;
int cols = 4;

int* arr = (int*) malloc(rows*cols*sizeof(int));
```

In row-major order, the (`i`,`j`)-th element would be accessed (e.g., set to `5`) in the following way:

```C
arr[i*cols+j] = 5;
```

However, no check is performed on the values of `i` and `j`.
This can lead to problems in large-scale programs where probably the indices `i` and `j` are computed on-the-fly.

In this example, one needs to make sure
that `i` is in the range `[0, rows-1]` and
that `j` is in the range `[0, cols-1]`.

Using `scafe`, above operation would be formulated as follows:

```C
scafe_set_int_2d(arr, rows, cols, i, j, 5);
```

## Usage

`scafe` consists of two C header files:
* `scafe_array_basics.h` provides the macros `SCAFE_ROW_MAJOR` and `SCAFE_ROW_MAJOR`
  to indicate the memory layout used for multi-dimensional arrays.
  It also provides a function prototype `void scafe_error(const char* what);`
  to implement custom error handling.
  `scafe_error` gets called in case an invalid array operation was detected by `scafe`.
* `scafe_array_access.h` provides the `scafe` API.

In order to adapt `scafe` for your needs, you are adivsed to create a customized header file `scafe_configured.h`:

```C
#ifndef SCAFE_CONFIGURED_H
#define SCAFE_CONFIGURED_H

// for printf, stderr
#include <stdio.h>
#include <stdlib.h>

// include predefined SCAFE macros
#include "scafe/scafe_array_basics.h"

// configure SCAFE array access
// can be SCAFE_ROW_MAJOR or SCAFE_COL_MAJOR
#define SCAFE_ORDER SCAFE_ROW_MAJOR

// primitive error handling: print to stderr
void scafe_error(const char* what) {
    fprintf(stderr, "error: %s\n", what);
}

// include main SCAFE array access library
#include "scafe/scafe_array_access.h"

#endif // SCAFE_CONFIGURED_H
```

You can download this template file here: [`scafe_configured.h`](https://raw.githubusercontent.com/jonathanschilling/scafe/master/scafe_configured.h).
This *configured* file can then be used in your own project.
`scafe` is then activated in the build by defining the preprocessor macro `SCAFE_ACTIVE`
either via a `#define` in the source code or via a compiler/preprocessor flag.

A demo project is available in [`scafe_demo.c`](scafe_demo.c).

## Concluding Remarks

Note that for `scafe` to really work in practise it is necessary that a complete set of (unit) tests
is available to trigger all program paths related to array access at least once.
