#include "mySort.h"

void merge(int array[], unsigned int first, unsigned int mid, unsigned int last){
    int i, j, k;
    int n1 = mid - first + 1;
    int n2 = last - mid;

    // temp arrays
    int L[MAX_SIZE_N_TO_SORT], R[MAX_SIZE_N_TO_SORT];

    // copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        myCopy(&array[first + i], &L[i]);
    for (j = 0; j < n2; j++)
        myCopy(&array[mid + 1 + j], &R[j]);

    // merge the temp arrays back into array[first..last]
    i = 0;
    j = 0;
    k = first;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            myCopy(&L[i], &array[k]);
            i++;
        }
        else {
            myCopy(&R[j], &array[k]);
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }
 
    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}

void mySort(int array[], unsigned int first, unsigned int last)
{
    int mid_index = first + (last - first ) / 2;
    if (myCompare(first, last) < 0)
    {
        mySort(array, first, mid_index);
        mySort(array, mid_index + 1, last);
        merge(array, first, mid_index, last);
    }
}
