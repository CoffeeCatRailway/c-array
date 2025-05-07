# c-array
A generic dynamic array in C.

## Example 1
`c_array_define.h` is my own implementation

```c
#include "c_array_define.h"

ARRAY_H_DEFINE_ARRAY(int)

void main()
{
    array_int_t* array = array_int_create(10); // Create an array of size 10
    array->capacityIncrement = 1; // `capacityIncrement` determines how much the capacity changes when resizing, default 2
    
    for (int i = 0; i < 10; i++)
    {
        array_int_push(array, i);
        
        array_int_push(array, 0 - i);
    }
    
    for (int i = 0; i < array->size; i++)
    {
        printf("%d\n", array->array[i]);
    }
    
    array_int_delete(array);
}
```
Output:
```c
0
0
1
-1
...
9
-9
```

## Example 2
`c_array.c/h` is inspired by [Eignnx' Dynarray](https://github.com/eignnx/dynarray)<br>

```c
#include "c_array.h"

void main()
{
    int* array = arrayCreate(int); // Create an array of size 2 with increment 2
    // int* array = arrayCreatePrealloc(int, 10, 5); // Create an array of size 10 with increment 5
    
    for (int i = 0; i < 4; i++)
    {
        arrayPush(array, i); // Pushes to back
        arrayPushFront(array, i); // Pushes to front
        arrayPushAt(array, 1, i); // Pushes to 2nd index
        
        const int n = 0 - i;
        arrayPush(array, n); // Passing a 'real value' requires a variable as it takes a pointer internally
    }
    
    for (int i = 0; i < arrayGetLength(array); i++)
    {
        printf("%d\n", array[i]);
    }
    
    arrayDestroy(array);
}
```
Output:
```c
3
3
2
2
1
1
0
0
0
0
1
-1
2
-2
3
-3
```
