/*
 * Created by Duncan on 03/05/2025.
 */

#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>

#include "c_array_define.h"
#include "c_array.h"

ARRAY_H_DEFINE_ARRAY(int)

void printArrayNewDetails(void* array);
void printArrayIntTDetails(const array_int_t* array);

void array_test_1d_int();
void array_test_2d_int();

void testArrayNewAvg(uint64_t times, bool debugOut);
void testArrayIntTAvg(uint64_t times, bool debugOut);

void testArrayNewStruct();
void testArrayNew();

int main()
{
	printf("Hello, World!\n");

	printf("Clock started now\n");
	// const clock_t start = clock();
	struct timespec start, end;
	clock_gettime(CLOCK_MONOTONIC, &start);

	// const uint64_t times = 1000;
	// const bool debugOut = false;
	// testArrayNewAvg(times, debugOut);
	// testArrayIntTAvg(times, debugOut);

	testArrayNewStruct();
	// testArrayNew();

	// array_test_1d_int();
	// array_test_2d_int();

	// Adjust struct size
	// int i = 2;
	// for (int s = 1; s <= 12; s++)
	// {
	// 	// Take 1 off size for correct adjusted size
	// 	int o = (s - 1) % i; // size - 1 % increment
	// 	o = s - 1 - o + i; // size - 1 - result + increment
	// 	// s - 1 - (s % i) + i
	// 	printf("%d, %d\n", s, o);
	// }

	// const clock_t end = clock();
	// printf("\nElapsed time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
	clock_gettime(CLOCK_MONOTONIC, &end);
	const uint64_t time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
	printf("Elapsed time: %lluus\n", time);

	return 0;
}

void printArrayNewDetails(void* array)
{
	printf("----------\n" \
		"Array length: %llu\n" \
		"Array capacity: %llu\n" \
		"Array increment: %llu\n" \
		"Array stride: %llu\n" \
		"----------\n",
		arrayGetLength(array),
		arrayGetCapacity(array),
		arrayGetIncrement(array),
		arrayGetStride(array));
}

void printArrayIntTDetails(const array_int_t* array)
{
	printf("----------\n" \
		"Array size: %llu\n" \
		"Array capacity: %llu\n" \
		"Array increment: %llu\n" \
		"----------\n",
		array->size,
		array->capacity,
		array->capacityIncrement);
}

int compare(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}

static void array_int_shift_left(array_int_t** array, size_t shift)
{
	if (shift <= 0 || (*array)->size <= 0)
	{
		fprintf(stderr, "Can't shift array by 0!\n");
		return;
	}
	if (shift > (*array)->size)
		shift = (*array)->size;
	if ((*array)->size - shift > 0)
	{
		const size_t segmentSize = ((*array)->size - shift) * sizeof(int);
		memcpy((*array)->array, &(*array)->array[shift], segmentSize);
	}
	(*array)->size -= shift;
}

void array_test_1d_int()
{
	// int array
	// srand(time(NULL));
	array_int_t* array_int = array_int_create(10);
	printArrayIntTDetails(array_int);

	int i;
	for (i = 0; i < 11; i++) // Add more than initial capacity
		array_int_push(&array_int, (i + 1) * 2);
		// array_int_push(array_int, rand() % 40);

	// qsort(array_int->array, array_int->size, sizeof(int), compare);

	// printf("%d\n", *(array_int->array + 1)); // returns 4 1-index
	// printf("%d\n", array_int->array[*(array_int->array + 1)]); // returns 10 4-index

	printArrayIntTDetails(array_int);

	for (i = 0; i < array_int->size; i++)
		printf("%d ", array_int->array[i]);
	printf("\n\n");

	// printf("%llu\n", sizeof(array_int->capacityIncrement));	// 8 unsigned long long
	// printf("%llu\n", sizeof(int));							// 4
	// printf("%p\n", &array_int->capacityIncrement);			// 0...80
	// printf("%p\n", &array_int->array[-1]);					// 0...8c 'random' data from end of capacityIncrement
	// printf("%p\n", &array_int->array[0]);					// 0...90
	// printf("%p\n", &array_int->array[1]);					// 0...94

	printf("Removed: %d FIRST\n", array_int_remove_at(&array_int, 0));
	printf("Removed: %d END\n", array_int_remove_at(&array_int, array_int->size - 1));
	printf("Removed: %d MIDDLE\n", array_int_remove_at(&array_int, array_int->size / 2));

	// const int j = array_int->size;
	// for (i = j; i > j / 2; i--)
	// 	array_int_remove_at(array_int, i);

	printArrayIntTDetails(array_int);
	array_int_adjust(&array_int);
	// array_int_push(array_int, 0);

	printArrayIntTDetails(array_int);

	// array_int_push(array_int, 1);
	// qsort(array_int->array, array_int->size, sizeof(int), compare);

	for (i = 0; i < array_int->size; i++)
		printf("%d ", array_int->array[i]);
	printf("\n");

	printf("\nShift left 2\n");
	array_int_shift_left(&array_int, 2);
	array_int_adjust(&array_int);
	for (i = 0; i < array_int->size; i++)
		printf("%d ", array_int->array[i]);
	printf("\nShift left 6\n");
	array_int_shift_left(&array_int, 6);
	array_int_adjust(&array_int);
	for (i = 0; i < array_int->size; i++)
		printf("%d ", array_int->array[i]);

	printArrayIntTDetails(array_int);
	array_int_delete(array_int);
}

typedef array_int_t* array_intptr_t;
ARRAY_H_DEFINE_ARRAY(array_intptr_t) // array_array_intptr_t_t

void array_test_2d_int()
{
	// 2d int array
	int i;
	const unsigned int width = 3, height = 3;
	array_array_intptr_t_t* array_array_int = array_array_intptr_t_create(width);

	for (i = 0; i < width; i++)
	{
		array_int_t* a = array_int_create(height);
		for (int j = 0; j < height; j++)
			array_int_push(&a, j);
		array_array_intptr_t_push(&array_array_int, a);
	}

	for (i = 0; i < width; i++)
		printf("%p ", array_array_int->array[i]);
	printf("\n");

	for (i = 0; i < width; i++)
	{
		const array_int_t* a = array_array_int->array[i];
		for (int j = 0; j < height; j++)
			printf("%d ", a->array[j]);
		printf("\n");
	}
	printf("\n");

	for (i = 0; i < width; i++)
		array_int_delete(array_array_int->array[i]);
	array_array_intptr_t_delete(array_array_int);
}

void testArrayNewAvg(const uint64_t times, const bool debugOut)
{
	uint64_t totalTime = 0l;

	for (int i = 0; i < times; i++)
	{
		struct timespec start, end;
		clock_gettime(CLOCK_MONOTONIC, &start);

		array_int_t* array = array_int_create(1);
		if (debugOut)
			printArrayIntTDetails(array);

		for (int j = 0; j < 100; j++)
		{
			const int n = (j + 1) * 2;
			array_int_push(&array, n);
		}

		if (debugOut)
		{
			for (int j = 0; j < 100; j++)
				printf("%d ", array->array[j]);
			printf("\n");
		}

		if (debugOut)
			printArrayIntTDetails(array);
		array_int_delete(array);

		clock_gettime(CLOCK_MONOTONIC, &end);
		const uint64_t time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
		totalTime += time;
		if (debugOut)
			printf("Time %d: %lluus\n", i, time);
	}

	totalTime /= times;
	printf("Average time \"array_new\" (%llu): %lluus\n", times, totalTime);
}

void testArrayIntTAvg(const uint64_t times, const bool debugOut)
{
	uint64_t totalTime = 0l;

	for (int i = 0; i < times; i++)
	{
		struct timespec start, end;
		clock_gettime(CLOCK_MONOTONIC, &start);

		int* array = arrayCreate(int);
		if (debugOut)
			printArrayNewDetails(array);

		for (int j = 0; j < 100; j++)
		{
			const int n = (j + 1) * 2;
			arrayPushBack(array, n);
		}

		if (debugOut)
		{
			for (int j = 0; j < 100; j++)
				printf("%d ", array[j]);
			printf("\n");
		}

		if (debugOut)
			printArrayNewDetails(array);
		arrayDestroy(array);

		clock_gettime(CLOCK_MONOTONIC, &end);
		const uint64_t time = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_nsec - start.tv_nsec) / 1000;
		totalTime += time;
		if (debugOut)
			printf("Time %d: %lluus\n", i, time);
	}

	totalTime /= times;
	printf("Average time \"array_int_t\" (%llu): %lluus\n", times, totalTime);
}

void testArrayNewStruct()
{
	struct somestruct
	{
		int a;
		int b;
		float c;
	};
	const int n = 11;
	struct somestruct* array = arrayCreate(struct somestruct);
	printArrayNewDetails(array);

	// printf("%llu %llu\n", sizeof(int), sizeof(float));

	int i;
	for (i = 0; i < n; i++)
	{
		struct somestruct s = {
			i,
			(i + 1) * 2,
			(float) i / (float) n
		};
		arrayPushBack(array, s);
	}

	for (i = 0; i < arrayGetLength(array); i++)
		printf("(%d, %d, %f)\n", array[i].a, array[i].b, array[i].c);
	printf("\n");

	struct somestruct front;
	arrayPopAt(array, 1, front);
	// arrayPopBack(array, front);
	printf("Pop index 1: (%d, %d, %f)\n", front.a, front.b, front.c);
	_arrayPopAt(array, 0, NULL);
	printf("Pop front NULL dest\n");

	for (i = 0; i < arrayGetLength(array); i++)
		printf("(%d, %d, %f)\n", array[i].a, array[i].b, array[i].c);
	printf("\n");

	printArrayNewDetails(array);

	arrayCapacityDeflate(array);
	printf("Deflate array\n");
	printArrayNewDetails(array);
	
	arrayDestroy(array);
}

void testArrayNew()
{
	int* array = arrayCreate(int);
	printArrayNewDetails(array);

	int i;
	for (i = 0; i < 10; i++)
	{
		const int n = (i + 1) * 2;
		arrayPushBack(array, n);
		// arrayPushFront(array, n);

		// array = _arrayPushAt(array, arrayGetLength(array), &n);
		// arrayPushAt(array, arrayGetLength(array), n);
	}

	for (i = 0; i < arrayGetLength(array); i++)
		printf("%d ", array[i]);
	printf("\n");

	int front;
	arrayPopAt(array, 1, front);
	// arrayPopBack(array, front);
	printf("Pop index 1: %d\n", front);
	_arrayPopAt(array, 0, NULL);
	printf("Pop front NULL dest\n");

	for (i = 0; i < arrayGetLength(array); i++)
		printf("%d ", array[i]);
	printf("\n");

	printArrayNewDetails(array);

	arrayCapacityDeflate(array);
	printf("Deflate array\n");
	printArrayNewDetails(array);

	arrayDestroy(array);
}
