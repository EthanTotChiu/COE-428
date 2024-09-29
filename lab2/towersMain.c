#include <stdlib.h>
#include <stdio.h>
#include "towers.h"

int main(int argc, char *argv[])
{
    int n = 3;
    int from = 1;
    int dest = 2;

    if (argc == 2) {
        n = atoi(argv[1]);
    }
    else if (argc == 4) {
     if((atoi(argv[2])<= 3 && atoi(argv[2])>= 1) && (atoi(argv[3])<= 3 && atoi(argv[3])>= 1) && (atoi(argv[2])!= atoi(argv[3])))
      {
       n =  atoi(argv[1]);
       from = atoi(argv[2]);
       dest = atoi(argv[3]);
      }
      else{
	fprintf(stderr,"Incorrect inputs");
	exit(1);
      }
      
    }
    else if(argc == 3|| argc > 4){
      fprintf(stderr,"Incorrect input format");
      exit(1);
    }
    towers(n, from, dest);
    exit(0);
}
