//
// Created by 1 on 14.03.2022.
//

#include "experiments.h"
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <memory.h>

#define STEP_CHANGER 1.24733
#define EIGHT_BITES_SET_AS_ONE 255
#define BITES_IN_BYTE 8

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

#define TIME_TEST(testCode, time) { \
     clock_t start_time = clock (); \
     testCode \
     clock_t end_time = clock ();\
     clock_t sort_time = end_time - start_time; \
     time = (double) sort_time / CLOCKS_PER_SEC; \
}

void outputArray_(const int *const a, const size_t n) {
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
}

bool isOrderedNonDecreasing(const int *a, size_t size) {
    for (size_t i = 1; i < size; i++)
        if (a[i] < a[i - 1])
            return false;

    return true;
}

bool isOrderedNonIncreasing(const int *a, size_t size) {
    for (size_t i = 1; i < size; i++)
        if (a[i] > a[i - 1])
            return false;

    return true;
}

bool isOrdered(const int *a, size_t size) {
    return isOrderedNonDecreasing(a, size) || isOrderedNonIncreasing(a, size);
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void getMinMax(const int *a, size_t size, int *min, int *max) {
    *min = a[0];
    *max = a[0];
    for (int i = 1; i < size; i++) {
        if (a[i] < *min)
            *min = a[i];
        else if (a[i] > *max)
            *max = a[i];
    }
}

void countSort(int *a, const size_t size) {
    int min, max;
    getMinMax(a, size, &min, &max);
    int k = max - min + 1;

    int *b = (int *) calloc(k, sizeof(int));
    for (int i = 0; i < size; i++)
        b[a[i] - min]++;

    int ind = 0;
    for (int i = 0; i < k; i++) {
        int x = b[i];
        for (int j = 0; j < x; j++)
            a[ind++] = min + i;
    }

    free(b);
}

int getByte(int someNumber, int bytePos) {
    int shift = bytePos * BITES_IN_BYTE;
    return (someNumber & EIGHT_BITES_SET_AS_ONE << shift) >> shift;
}

void radixSortPositives(int *a, const size_t size) {
    int *b = (int *) malloc(sizeof(int) * size);

    for (int i = 0; i < sizeof(int); i++) {
        int *c = (int *) calloc(EIGHT_BITES_SET_AS_ONE + 1, sizeof(int));
        for (size_t j = 0; j < size; j++)
            c[getByte(a[j], i)]++;

        for (int j = 1; j < EIGHT_BITES_SET_AS_ONE + 1; j++)
            c[j] += c[j - 1];

        for (size_t j = size; j > 0; j--)
            b[c[getByte(a[j - 1], i)]-- - 1] = a[j - 1];

        memcpy(a, b, sizeof(int) * size);

        free(c);
    }

    free(b);
}

size_t separatePosFromNeg(int *a, size_t size) {
    size_t firstNotNegIndex = 0;

    while (firstNotNegIndex < size && a[firstNotNegIndex] < 0)
        firstNotNegIndex++;

    for (size_t i = firstNotNegIndex + 1; i < size; i++)
        if (a[i] < 0)
            swap(&a[firstNotNegIndex++], &a[i]);

    return firstNotNegIndex;
}

void changeSign(int *a, size_t size) {
    for (int i = 0; i < size; i++)
        a[i] = -a[i];
}

void reverse(int *a, size_t size) {
    size_t half = size / 2;
    for (int i = 0; i < half; i++)
        swap(&a[i], &a[size - i - 1]);
}

void radixSortPositivesNonIncreasing(int *a, const size_t size) {
    int *b = (int *) malloc(sizeof(int) * size);

    for (int i = 0; i < sizeof(int); i++) {
        int *c = (int *) calloc(EIGHT_BITES_SET_AS_ONE + 1, sizeof(int));
        for (size_t j = 0; j < size; j++)
            c[getByte(a[j], i)]++;

        for (int j = EIGHT_BITES_SET_AS_ONE - 1; j >= 0; j--)
            c[j] += c[j + 1];

        for (size_t j = size; j > 0; j--)
            b[c[getByte(a[j - 1], i)]-- - 1] = a[j - 1];

        memcpy(a, b, sizeof(int) * size);

        free(c);
    }

    free(b);
}

void radixSort(int *a, size_t size) {
    size_t firstNotNegIndex = separatePosFromNeg(a, size);

    changeSign(a, size);
    radixSortPositivesNonIncreasing(a, firstNotNegIndex);
    changeSign(a, size);

    radixSortPositives(a + firstNotNegIndex, size - firstNotNegIndex);
}

void bubbleSort(int *a, size_t size) {
    for (size_t i = 0; i < size - 1; i++) {
        bool noSwap = true;
        for (size_t j = size - 1; j > i; j--)
            if (a[j - 1] > a[j]) {
                swap(&a[j - 1], &a[j]);
                noSwap = false;
            }

        if (noSwap)
            break;
    }
}

void combSort(int *a, const size_t size) {
    size_t step = size;
    bool swapped = true;
    while (step > 1 || swapped) {
        if (step > 1)
            step /= STEP_CHANGER;
        swapped = false;
        for (size_t i = 0, j = i + step; j < size; ++i, ++j)
            if (a[i] > a[j]) {
                swap(&a[i], &a[j]);
                swapped = true;
            }
    }
}

void selectionSort(int *a, const size_t size) {
    for (int i = 0; i < size - 1; i++) {
        size_t indexMin = i;

        for (int j = i; j < size; j++)
            if (a[j] < a[indexMin])
                indexMin = j;

        swap(&a[i], &a[indexMin]);
    }
}

void insertionSort(int *a, const size_t size) {
    for (size_t i = 1; i < size; i++) {
        int key = a[i];
        size_t j = i;
        while (j > 0 && a[j - 1] > key) {
            a[j] = a[j - 1];
            j--;
        }

        a[j] = key;
    }
}

void shellSort(int *a, const size_t size) {
    for (size_t step = size / 2; step > 0; step /= 2)
        for (size_t i = step; i < size; i++) {
            int key = a[i];

            size_t j = i;
            while (j >= step) {
                if (key < a[j - step])
                    a[j] = a[j - step];
                else
                    break;

                j -= step;
            }

            a[j] = key;
        }
}

void insertHeap(int *a, size_t *size, int x) {
    a[(*size)++] = x;
    size_t childIndex = *size - 1;
    size_t parentIndex = (childIndex - 1) / 2;
    while (a[childIndex] < a[parentIndex] && childIndex != 0) {
        swap(&a[childIndex], &a[parentIndex]);
        childIndex = parentIndex;
        parentIndex = (childIndex - 1) / 2;
    }
}

bool hasLeftChild(size_t parentIndex, size_t size) {
    return 2 * parentIndex + 1 < size;
}

bool hasRightChild(size_t parentIndex, size_t size) {
    return 2 * parentIndex + 2 < size;
}

size_t getLeftChildIndex(size_t parentIndex) {
    return 2 * parentIndex + 1;
}

size_t getMinChildIndex(const int *a, size_t size, size_t parentIndex) {
    size_t minChildIndex = getLeftChildIndex(parentIndex);
    size_t rightChildIndex = minChildIndex + 1;
    if (hasRightChild(parentIndex, size))
        if (a[rightChildIndex] < a[minChildIndex])
            minChildIndex = rightChildIndex;
    return minChildIndex;
}

void removeMinHeap(int *a, size_t *size) {
    *size -= 1;
    swap(&a[0], &a[*size]);
    size_t parentIndex = 0;
    while (hasLeftChild(parentIndex, *size)) {
        size_t minChildIndex = getMinChildIndex(a, *size, parentIndex);
        if (a[minChildIndex] < a[parentIndex]) {
            swap(&a[minChildIndex], &a[parentIndex]);
            parentIndex = minChildIndex;
        } else
            break;
    }
}

void heapSort(int *a, size_t size) {
    size_t heapSize = 0;
    while (heapSize != size)
        insertHeap(a, &heapSize, a[heapSize]);
    while (heapSize)
        removeMinHeap(a, &heapSize);
}

void generateRandomArray(int *a, size_t n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        a[i] = rand();
}

void generateOrderedArray(int *a, size_t n) {
    for (int i = 0; i < n; i++)
        a[i] = i;
}

void generateOrderedBackwards(int *a, size_t n) {
    for (int i = n - 1; i >= 0; i--)
        a[i] = i;
}


void checkTime(void (*sortFunc)(int *, size_t), void (*generateFunc)(int *, size_t),
               size_t size, char *experimentName) {
    static size_t runCounter = 1;

    // генерация последовательности
    static int innerBuffer[100000];
    generateFunc(innerBuffer, size);
    printf("Run #%zu| ", runCounter++);
    printf(" Name : %s\n", experimentName);
    // замер времени
    double time;
    TIME_TEST({ sortFunc(innerBuffer, size); }, time);
    // результаты замера
    printf(" Status : ");
    if (isOrdered(innerBuffer, size)) {
        printf("OK! Time : %.3f s.\n", time);

        // запись в файл
        char filename[256];
        sprintf(filename, "./data/%s.csv", experimentName); //filename -> name
        FILE *f = fopen(filename, "a");
        if (f == NULL) {
            printf(" FileOpenError %s", filename);
            exit(1);
        }
        fprintf(f, "%zu; %.3f\n", size, time);
        fclose(f);
    } else {
        printf(" Wrong!\n");

        // вывод массива, который не смог быть отсортирован
        outputArray_(innerBuffer, size);

        exit(1);
    }
}

void timeExperiment() {
    // описание функций сортировки
    SortFunc sorts[] = {
            {selectionSort, "selectionSort"},
            {insertionSort, "insertionSort"},
            {bubbleSort,    "bubbleSort"},
            {shellSort,     "shellSort"},
            {combSort,      "combSort"},
            {radixSort,     "radixSort"},
            {heapSort, "heapSort"}
    };
    const unsigned FUNCS_N = ARRAY_SIZE(sorts);
    // описание функций генерации
    GeneratingFunc generatingFuncs[] = {
            // генерируется случайный массив
            {generateRandomArray,      "random"},
            // генерируется массив 0, 1, 2, ..., n - 1
            {generateOrderedArray,     "ordered"},
            // генерируется массив n - 1, n - 2, ..., 0
            {generateOrderedBackwards, "orderedBackwards"}
    };
    const unsigned CASES_N = ARRAY_SIZE(generatingFuncs);

    // запись статистики в файл
    for (size_t size = 10000; size <= 100000; size += 10000) {
        printf("-----------------------------------------\n");
        printf(" Size : %d\n", size);
        for (int i = 0; i < FUNCS_N; i++) {
            for (int j = 0; j < CASES_N; j++) {
                // генерация имени файла
                static char filename[128];
                sprintf(filename, "%s_%s_time ",
                        sorts[i].name, generatingFuncs[j].name);
                checkTime(sorts[i].sort,
                          generatingFuncs[j].generate,
                          size, filename);
            }
        }
        printf("\n");
    }
}

