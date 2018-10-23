#ifndef CHAPTER7_H_INCLUDED
#define CHAPTER7_H_INCLUDED
/// in this chapter we practice c with the std library. Dealing with piping, redirection and other funny topics in c
///include libraries
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h> // to go through the unnamed argument list

/// playing with the stdio library utilities
//convert input to lower or to upper
int toLow_toCap(int argc, char** argv){
  int (*convcase[2])(int) = {toupper, tolower};
  int func, ch;
  int result = EXIT_SUCCESS;

  if(argc > 0){
    if(toupper((unsigned char)argv[0][0]) == 'U')
      func = 0;
    else
      func = 1;

    while((ch = getchar()) != EOF)
        putchar((*convcase[func])((unsigned char)ch));
  }
  else{
    fprintf(stderr, "Unknown name. Can't decide what to do.\n");
    result = EXIT_FAILURE;
  }
    return result;
}

// type conversion
void printFormats(){
int x = 5;
    char* p = "hello world";
    printf("int : 5 : %d or 10 : %i\n", 5, 1, 10);
    printf("octal : 15 : %o \n", 15);
    printf("hexa : 15 : %X \n", 15);
    printf("unsigned int : 15 : %u \n", 15);

    printf("char : \'H\' : %c\n", 'H');
    printf("string : \"hello world\" : %s\n", "hello world");

    printf("float : %5.2f\n", 55.26541561);
    printf("pointer void* : %p\n", (void*) &x);

    printf("string : \"hello world\" : %.*s\n", 3, p);
}

// variable-length argument list
void minPrintf(char* fmt, ...){
    va_list ap;      // will refer to each argument in turn
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt);  //make ap points to the first argument

    for(p=fmt; *p; p++){
        //there is no formate to print
        if(*p != '%'){
            putchar(*p);
            continue;
        }

        switch(*++p){
            case 'd' :
                ival = va_arg(ap, int);     //read the next value and then point to the next argument
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);  //read the current position as double then go to the next argument position
                printf("%f", dval);
                break;

            case 's' :
                for(sval = va_arg(ap, char*); *sval; sval++)    //read the current position as string then go to the next argument position
                    putchar(*sval);                             // iterate through the chars to print them
                break;

            case 'c':
                ival = va_arg(ap, int);
                printf("%c", ival);
                break;
            default:
                putchar(*p);
                break;
        }
    }

    va_end(ap);   // clean up when done
}

// minscanf is analog to minPrintf function
int minScanf(const char* format, ...){
    va_list ap;         //points to every unnamed argument in turn
    int* ival;           // hold the integer value
    double* dval;       // hold the double value
    char* sval;     // points to the string values
    char* p;        //used to pass through the format to find conversion specification

    va_start(ap, format);

    //scan the format
    for(p = format; *p; p++){
        //no conversion specification
        if(*p != '%'){
            //remove the char from the input buffer
            int c = getchar();
            continue;
        }

        // there is % check its type of data to read
        switch( *++p ){
            case 'd':       //read integer value
            case 'i':
                ival = va_arg(ap, int*);
                scanf("%d", ival);
                break;

            case 'f':       //read float value
                dval = va_arg(ap, float*);
                scanf("%f", dval);
                break;

            case 'c':       //read char value
                sval = va_arg(ap, char*);
                scanf("%c", sval);
                break;

            case 's':       //read string value
                sval = va_arg(ap, char*);
                while((*sval=getchar()) != EOF && !isspace(*sval) && *sval!='\n') sval++;

                if(isspace(*sval) || *sval=='\n') ungetch(*sval);
                *sval = '\0';
                break;

            default:
                break;
        }
    }

    va_end(ap);
}

// rudimentary calculator
void rudCalculator(){
    float sum=0.0, v;
    sum = 0;
    while(scanf("%f", &v) == 1)
        printf("%f\n", sum+=v);
}
#endif // CHAPTER7_H_INCLUDED
