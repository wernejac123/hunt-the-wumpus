#include <stdlib.h> //size_t, NULL, rand(), srand()
#include <time.h>
#include "fisher_yates.h"

//Fisher-Yates shuffle algorithm

void swap(int *a, int *b){
        int temp = *a;
        *a = *b;
        *b = temp;
}

void randomize(int *arr, size_t n){
        srand((unsigned int)time(NULL));

        for(size_t i = n-1; i > 0; i--){
                size_t j = (size_t)rand() % (i+1); //random index from 0 to i
                swap(&arr[i], &arr[j]);
        }
}
