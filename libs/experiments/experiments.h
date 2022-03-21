//
// Created by 1 on 14.03.2022.
//

#ifndef LAB_5C_EXPERIMENTS_H
#define LAB_5C_EXPERIMENTS_H

#include <stdio.h>

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

//функция сортировки
typedef struct SortFunc {
    void (*sort)(int *a, size_t n);

    char name[64];
} SortFunc;

//функция генерации
typedef struct GeneratingFunc {
    void (*generate)(int *a, size_t n);

    char name[64];
} GeneratingFunc;

void generateRandomArray (int *a, size_t n);

void outputArray_(const int *a, size_t n);

void bubbleSort(int *a, size_t size);

void selectionSort(int *a, size_t size);

void insertionSort(int *a, size_t size);

void combSort(int *a, size_t size);

void shellSort(int *a, size_t size);

void countSort(int *a, size_t size);

int getByte (int someNumber, int bytePos);

void radixSortPositives(int *a, size_t size);

void radixSort (int *a, size_t size);

void timeExperiment();

#endif //LAB_5C_EXPERIMENTS_H
