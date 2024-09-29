#include "mySort.h"

void mySort(int array[], unsigned int first, unsigned int last){
	for(int i = first + 1  ; i <= last; i++){
		int key = array[i];
		int j = i-1; //set j to the first element in the array
		while(j >= 0 && myCompare(key,array[j]) < 0){//while j is less than the last element in the array and the current element is greater than the key value
			mySwap(&array[j+1],&array[j]); //copy the current element to the next 
			j--;
			}
		myCopy(&array[j + 1], &key);
	}
    
}
