/*
 * Created by Duncan on 03/05/2025.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 *
 * Changelog 1.0:
 *	- Initial code
 *
 * 17/11/2025
 * Changelog 1.1:
 *	- Added arrayPushBack & arrayPopBack for clarity
 */

#ifndef ARRAY_NEW_H
#define ARRAY_NEW_H

#include <stdlib.h>

// struct array
// {
// 	size_t length;
// 	size_t capacity;
// 	size_t increment;
//	size_t stride;
// 	void* array;
// };

enum ArrayFields
{
	LENGTH,
	CAPACITY,
	INCREMENT,
	STRIDE,
	ARRAY
};

void* _arrayCreate(size_t capacity, size_t increment, size_t stride);
void arrayDestroy(void* array);

size_t _arrayFieldGet(void* array, size_t field);
void _arrayFieldSet(void* array, size_t field, size_t value);

void* _arrayResize(void* array, size_t capacity);

// void* _arrayPush(void* array, const void* element);
// void* _arrayPushFront(void* array, const void* element);
void* _arrayPushAt(void* array, size_t index, const void* element);

// void arrayPop(void* array, void* dest);
// void arrayPopFront(void* array, void* dest);
void _arrayPopAt(void* array, size_t index, void* dest);

#define arrayCreate(type) _arrayCreate(2, 2, sizeof(type))
#define arrayCreatePrealloc(type, capacity, increment) _arrayCreate(capacity, increment, sizeof(type))

#define arrayGetLength(array) _arrayFieldGet(array, LENGTH)
#define arrayGetCapacity(array) _arrayFieldGet(array, CAPACITY)
#define arrayGetIncrement(array) _arrayFieldGet(array, INCREMENT)
#define arrayGetStride(array) _arrayFieldGet(array, STRIDE)

#define arrayCapacityIncrement(array) (array = _arrayResize(array, _arrayFieldGet(array, CAPACITY) + _arrayFieldGet(array, INCREMENT)))
#define arrayCapacityDeflate(array) \
	do \
	{ \
		const size_t length = _arrayFieldGet(array, LENGTH); \
		const size_t increment = _arrayFieldGet(array, INCREMENT); \
		const size_t capacityAdjusted = length - 1 - ((length - 1) % increment) + increment; \
		array = _arrayResize(array, capacityAdjusted); \
	} while(0)

#define arrayPushBack(array, element) (array = _arrayPushAt(array, _arrayFieldGet(array, LENGTH), &element))
#define arrayPush(array, element) arrayPushBack(array, element)
#define arrayPushFront(array, element) (array = _arrayPushAt(array, 0, &element))
#define arrayPushAt(array, index, element) (array = _arrayPushAt(array, index, &element))

#define arrayPopBack(array, dest) _arrayPopAt(array, _arrayFieldGet(array, LENGTH) - 1, &dest)
#define arrayPop(array, dest) arrayPopBack(array, dest)
#define arrayPopFront(array, dest) _arrayPopAt(array, 0, &dest)
#define arrayPopAt(array, index, element) _arrayPopAt(array, index, &element)

#endif //ARRAY_NEW_H
