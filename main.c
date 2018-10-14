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
struct s{unsigned int x : 2;} ss;
ss.x = 3;

printf("%d", ss.x);

	return 0;
}
