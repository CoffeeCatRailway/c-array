/*
 * Created by Duncan on 03/05/2025.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#include "c_array.h"

#include <stdio.h>
#include <string.h>

void* _arrayCreate(const size_t capacity, const size_t increment, const size_t stride)
{
	const size_t header = ARRAY * sizeof(size_t);
	const size_t size = capacity * stride;
	size_t* array = (size_t*) malloc(header + size);
	if (array == NULL)
	{
		fprintf(stderr, "Memory allocation failed\n");
		free(array);
		exit(EXIT_FAILURE);
	}
	array[LENGTH] = 0;
	array[CAPACITY] = capacity;
	array[INCREMENT] = increment;
	array[STRIDE] = stride;
	return (void*) (array + ARRAY);
}

void arrayDestroy(void* array)
{
	free(array - ARRAY * sizeof(size_t));
}

size_t _arrayFieldGet(void* array, const size_t field)
{
	return ((size_t*) array - ARRAY)[field];
}

void _arrayFieldSet(void* array, const size_t field, const size_t value)
{
	((size_t*) array - ARRAY)[field] = value;
}

void* _arrayResize(void* array, const size_t capacity)
{
	const size_t length = arrayGetLength(array);
	const size_t stride = arrayGetStride(array);

	void* newArray = _arrayCreate(
		capacity,
		arrayGetIncrement(array),
		stride
		);
	memcpy(newArray, array, length * stride);
	_arrayFieldSet(newArray, LENGTH, length);
	arrayDestroy(array);
	return newArray;
}

// void* _arrayPush(void* array, const void* element)
// {
// 	const size_t length = arrayGetLength(array);
// 	const size_t stride = arrayGetStride(array);
//
// 	if (length >= arrayGetCapacity(array))
// 		arrayCapacityIncrement(array);
//
// 	memcpy(array + length * stride, element, stride);
// 	_arrayFieldSet(array, LENGTH, length + 1);
// 	return array;
// }

//  void* _arrayPushFront(void* array, const void* element)
//  {
// 	const size_t length = arrayGetLength(array);
// 	const size_t stride = arrayGetStride(array);
//
// 	if (length >= arrayGetCapacity(array))
// 		arrayCapacityIncrement(array);
//
// 	// Shift whole array right by 1
// 	memcpy(array + 1 * stride, array, length * stride);
// 	// Copy element to index 0
// 	memcpy(array, element, stride);
// 	_arrayFieldSet(array, LENGTH, length + 1);
// 	return array;
// }

void* _arrayPushAt(void* array, const size_t index, const void* element)
{
	const size_t length = arrayGetLength(array);
	const size_t stride = arrayGetStride(array);

	if (length >= arrayGetCapacity(array))
		arrayCapacityIncrement(array);

	const size_t offset = index * stride;
	// Shift array from index right by 1
	if (index < length)
		memcpy(array + (index + 1) * stride, array + offset, (length - index) * stride);
	// Copy element to index
	memcpy(array + offset, element, stride);
	_arrayFieldSet(array, LENGTH, length + 1);
	return array;
}

// void arrayPop(void* array, void* dest)
// {
// 	const size_t length = arrayGetLength(array);
// 	const size_t stride = arrayGetStride(array);
//
// 	if (dest)
// 		memcpy(dest, array + (length - 1) * stride, stride);
// 	_arrayFieldSet(array, LENGTH, length - 1);
// }

// void arrayPopFront(void* array, void* dest)
// {
// 	const size_t length = arrayGetLength(array);
// 	const size_t stride = arrayGetStride(array);
//
// 	// Copy front element to dest
// 	if (dest)
// 		memcpy(dest, array, stride);
// 	// Shift whole array left by 1
// 	memcpy(array, array + 1 * stride, (length - 1) * stride);
// 	_arrayFieldSet(array, LENGTH, length - 1);
// }

void arrayPopAt(void* array, const size_t index, void* dest)
{
	const size_t length = arrayGetLength(array);
	const size_t stride = arrayGetStride(array);

	const size_t offset = index * stride;
	// Copy element to dest
	if (dest)
		memcpy(dest, array + offset, stride);
	// Shift array from index left by 1
	if (index < length - 1)
		memcpy(array + offset, array + (index + 1) * stride, (length - index - 1) * stride);
	_arrayFieldSet(array, LENGTH, length - 1);
}
