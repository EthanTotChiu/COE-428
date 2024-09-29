#include <stdio.h>
/**
 *  The functions in this module implement a Heapdata structure
 *  of integers.
 */
static int size = 0;
static int heap[1000];


/**
 * swap() swaps two elements in the heap
*/
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * printXML() prints out the elements in the heap using node id tags
*/
void printXML(int i) {
    int left = (2 * i) + 1;
    int right = (2 * i) + 2;

    if (i < size) {
        fprintf(stderr,"<node id=\"%d\">", heap[i]);
        printXML(left);
        printXML(right);
        fprintf(stderr,"</node>");
    }
}


/**
 * heapify() heapify's the largest to the bottom
*/
void heapify(int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    // Find the largest of left and right child
    if (heap[left] > heap[largest] && left < size )
        largest = left;

    if (heap[right] > heap[largest] && right < size)
        largest = right;

    // If the largest is not the current index swap and continue heapifying
    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        heapify(largest);
    }
}


/**
 * buildHeap() builds max heap
*/
void buildHeap() {
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(i);
}



/**
 * heapDelete() removes the biggest integer in the heap and returns it.
 *
 */

int heapDelete()
{
  if (size == 0){
    return -1;
  }
  // Store the maximum value
  int root = heap[0];
  heap[0] = heap[size-1];
  heap[size-1] = 0;
  size--;
  heapify(0);
  return root;
}

/**
 *  addHeap(thing2add) adds the "thing2add" to the Heap.
 *
 */
void addHeap(int thing2add)
{
  heap[size++] = thing2add;
}

/**
 * heapSize() returns the number of items in the Heap.
 *
 */
int heapSize()
{
  return size;  
}
