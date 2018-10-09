#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Chapter6.h"

struct p{
int x, y;
//char c;
} x;
int main(int argv, char** argc)
{

    int n = 1;
    char file[100] = "";
    readArgs(argv, argc, &n, file);
    //read from input
    readWords(file, n);

	return 0;
}
