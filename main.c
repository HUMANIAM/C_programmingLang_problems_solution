#include <stdio.h>
#include <stdlib.h>
#include "Chapter6.h"

struct p{
int x, y;
//char c;
} x;
int main(int argv, char** argc)
{
   printf("%d", sizeof x);
	return 0;
}
