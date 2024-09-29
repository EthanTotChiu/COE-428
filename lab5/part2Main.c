#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

extern int pop();
extern void push(int);
extern int heapDelete();
extern void addHeap(int);
extern int heapSize();
extern int buildHeap();
extern int printXML();
extern int isEmpty();

int main(int argc, char * argv[])
{
  int value;
  while (scanf("%d\n", &value) != EOF) {
    fprintf(stderr, "READING INPUT: %d\n", value);
    addHeap(value);
  }

  fprintf(stderr, "HEAP AS XML:\n");
  buildHeap();
  printXML(0);

  fprintf(stderr, "\nPUSHING TO STACK:\n");
  while (heapSize() > 0) {
    int deletedValue = heapDelete();
    fprintf(stderr,"%d\n", deletedValue);
    push(deletedValue);
  }

  fprintf(stderr, "POPPING VALUES:\n");
  while (!isEmpty()) {
    printf("%d\n", pop());
  }
  exit(0);
}
