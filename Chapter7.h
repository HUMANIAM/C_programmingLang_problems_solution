#ifndef CHAPTER7_H_INCLUDED
#define CHAPTER7_H_INCLUDED
/// in this chapter we practice c with the std library. Dealing with piping, redirection and other funny topics in c
///include libraries
#include <stdio.h>
#include <ctype.h>
#include <string.h>
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

///playing with file access
// this cat program take content of files and copy it to the std output file
void filecopy(FILE* input, FILE* output){
    int c;
    while((c=getc(input)) != EOF){
        putc(c, output);
    }
}

// return 1 there is an error but return 0 there is no error
int copyFiles(int argc, const char** argv){
    FILE*fp;
    const char* prog = argv[0];

    if(argc == 1)
        filecopy(stdin, stdout);    //if there is no input file then read from the std input file
    else{
        while(--argc > 0){
            if((fp = fopen(*++argv, "r")) != NULL){
                filecopy(fp, stdout);
                fclose(fp);
            }else{
                fprintf( stderr,"%s can't open %s\n", prog, *++argv);
                return 1;
            }
        }
    }

    if(ferror(stdout)){ //check there is no error during the streaming process
        fprintf(stderr, "%s : error writing stdout\n", prog);
        exit(2);
    }
    return 0;
}

// dealing with fgets and fputs functions
char* fGets(char* line, int maxsz, FILE* fp){
    register int c;
    register char* p = line;

    while(--maxsz > 0 && (c=getc(fp)) != EOF)
        if((*p++=c) == '\n') break;

    *p = '\0';

    //if c = EOF and we did not read any char from the file pointer input
    return (c==EOF && p==fp)? NULL : line;
}

//fputs
int fPuts(const char* line, FILE* fp){
    while(putc(*line++, fp));
    return ferror(fp)? EOF : 0;
}

//simple version of read from the stdin file
int getline(char* line, int maxsz){
    if(fGets(line, maxsz, stdin) != NULL)
        return strlen(line);
    return 0;
}

/// this program is take two files and compare their content print the line where they are different
int compareFiles(int argc, char** argv){
    if(argc < 3){
        fputs("run the program with this command >> programName file1 file2\n", stderr);
        exit(1);

    }else{
        FILE* fp1, * fp2;
        const int MAX = 200;
        int lineNumber = 0;
        char* line1 = (char*) malloc(MAX*sizeof(char));
        char* line2 = (char*) malloc(MAX*sizeof(char));

        //open the first file and second file
        if((fp1=fopen(argv[1], "r")) == NULL  || (fp2=fopen(argv[2], "r")) == NULL){
            fprintf(stderr, "%s can't open one of the files %s or %s", argv[0], argv[1], argv[2]);
            exit(1);
        }

        //compare files content line by line
        while(fgets(line1, MAX, fp1) != NULL && fgets(line2, MAX, fp2) != NULL){
            if(strcmp(line1, line2) != 0){
                printf("The Files are different in line %d\n", ++lineNumber);
                printf("%s | %s\n", argv[1], line1);
                printf("%s | %s\n", argv[2], line2);

                //close the files before return
                fclose(fp1);
                fclose(fp2);
                return 1;
            }
            lineNumber++;
        }

        // two files are identical
        fclose(fp1);
        fclose(fp2);
        printf("%s and %s Has the same content\n", argv[1], argv[2]);
   }
}

/// This program take pattern and n files then searching for the pattern in those files
/// print the file name and line number where the pattern found
#define MAXSZ 200

int fileFindPattern(FILE* fp, const char* pattern){
    int lineNumber = 1;
    int m = strlen(pattern);
    char* line = (char*) malloc(MAXSZ*sizeof(char));

    //read line by line and in every line search for the pattern
    while((line=fgets(line, MAXSZ, fp)) != NULL){
        //search for the pattern in the line. this will take O(m*(n-m+1))
        int i, j;
        int n = strlen(line);

        for(i=0; i<=n-m; i++){
            int k=i;
            for(j=0; j<m; j++)
                if(pattern[j] != line[k++])
                    break;

            if(j==m){
                printf("line : %d \n", lineNumber);
            }
        }

        //read the next line of the file
        lineNumber++;
    }
    return 0;
}

int findPattern(int argc, const char** argv){
    if(argc < 2){
        fputs("run the program with this command >> programName pattern {file1 file2 ..... filen}\n", stderr);
        exit(1);

    }else if(argc == 2){
        fileFindPattern(stdin, argv[1]);

    }else{
        FILE* fp;
        int fileNumber = 1;

        argc--;

        //read files file by file
        while(--argc){
            fileNumber++;

            //print the file name as a header of matched positions
            printf("%s\n-----------------\n\n", argv[fileNumber]);

            //open file
            if((fp = fopen(argv[fileNumber], "r")) == NULL){
                fprintf(stderr, "%s can't open %s file\n", argv[0], argv[fileNumber]);
                exit(1);
            }

            //find lines where the pattern occurs in the file
            fileFindPattern(fp, argv[1]);

            //close the file
            fclose(fp);

        }
    }

    return 0;
}


#endif // CHAPTER7_H_INCLUDED
