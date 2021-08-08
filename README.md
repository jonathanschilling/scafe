# scafe

`scafe` (pronounced *seɪf*) is a C library designed to safeguard array accesses at runtime with controllable performance overhead.
The basic idea is to perform array operations (de-/allocation, read/write of individual elements)
through a layer provided by `scafe`.

* In **inactive** mode, this layer defaults to a set of preprocessor macros
  which boil down to the default un-checked behaviour of array access in C.
* In **active** mode, the `scafe` layer provides array operations
  through functions that explicitly check the size and index values for validity and compatibility.
