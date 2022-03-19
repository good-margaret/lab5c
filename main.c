#include <stdio.h>
#include "libs/experiments/experiments.h"

int main() {
    int a[] = {-8, -8, 7, -1, 0, -2, 0, 1};
    //generateRandomArray(a, ARRAY_SIZE(a));
    radixSort(a, ARRAY_SIZE(a));
    outputArray_(a, ARRAY_SIZE(a));
    //generateRandomArray(a, ARRAY_SIZE(a));
    //radixSort(a, ARRAY_SIZE(a));
    //outputArray_(a, ARRAY_SIZE(a));
    //printf("%d-%d-%d-%d", getByte(a[0], 0), getByte(a[0], 1), getByte(a[0], 2), getByte(a[0], 3));
    return 0;
}
