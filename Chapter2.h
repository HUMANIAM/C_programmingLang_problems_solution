#ifndef CHAPTER2_H_INCLUDED
#define CHAPTER2_H_INCLUDED
#define LEN 30
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <math.h>       //using double precision parameters
enum spectrum {red, orange, yellow, green, blue, violet};
const char * colors[] = {"red", "orange", "yellow", "green", "blue", "violet"};

//test the enumeration type and how to deal with it as an alternative for #define
void testEnumeration(){
    char choice[LEN];
    enum spectrum color;
    bool color_is_found = false;
    puts("Enter a color (empty line to quit):");
    while (gets(choice) != NULL && choice[0] != '\0')
    {
        for (color = red; color <= violet; color++)
        {
            if (strcmp(choice, colors[color]) == 0)
            {
                color_is_found = true;
                break;
            }
        }
        if(color_is_found){
            switch(color){
            case red :
                puts("red");
                break;
            case orange:
                puts("orange");
                break;
            case green:
                puts("green");
                break;
            case violet:
                puts("violet");
                break;
            }
        } else puts("enter correct one");
    }
}

//convert from character string to integer
int atoiMin(char * digits){
    int i = 0, res = 0;
    for(; digits[i]>= '0' && digits[i]<='9'; i++){
        res = res * 10 + (digits[i]-'0');
    }
    return res;
}

//convert from character string to hexadecimal
int htoi(char* digits){
    int i = 2, res=0;
    if(strlen(digits)<=2)
        return 0;

    while(digits[i]){
        if(digits[i] >= '0' && digits[i]<='9')
            res = res*16 + (digits[i] - '0');
        else if(digits[i] >= 'a' && digits[i]<='f')
            res = res*16 + (digits[i] - 'a' + 10);
        else if(digits[i] >= 'A' && digits[i]<='F')
            res = res*16 + (digits[i] - 'A' + 10);
        i++;
    }
    return res;
}

//squeeze
void squeeze(char s1[], char s2[]){
    int i, j, k;
    i=j=0;

   while(s1[i] != '\0'){
        k = 0;
        while(s2[k] != '\0' && s2[k] != s1[i] ) k++;

        if(!s2[k])  s1[j++] = s1[i];

        i++;
    }
    s1[j] = '\0';
}

//getbites
unsigned getbites(unsigned x, int p, int n){
    //bits[n, n-1, n-2, ............., 3, 2, 1, 0]
    //p :: position
    //n :: number to left of position
    return ~(1<<n) & (x>>(p-n+1));
}

//setsbites
unsigned setbits(unsigned x, int p, int n, unsigned y){
     int k = p-n+1;
     return ((y&(~(-1<<n)))<<k) ^ (x&(~(-1<<k))) ^ ((x>>(p+1))<<(p+1));
}

//invert specific bits in number
unsigned invert(unsigned x, int p, int n){
    return ((-1&(~(-1<<n)))<<(p-n+1)) ^ x;
}

//bitcount counts the number of 1 bit in an integer
int bitCount(unsigned x){
    int b = 0;
    while(x !=0){
        if(x & 01) b++;
        x >>= 1;
    }
    return b;
}
#endif // CHAPTER2_H_INCLUDED
