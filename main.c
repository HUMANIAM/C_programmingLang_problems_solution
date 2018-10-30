#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Chapter7.h"

void printscreen(char* line){
while(putc(*line++, stdout));
}

int main(int argc, char **argv)
{
    //findPattern(argc, argv);
    printf("%i\n", RAND_MAX);
    printf("%i", rand());
  return 0;
}
