#ifndef CHAPTER6_H_INCLUDED
#define CHAPTER6_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>      //isalpha, isalnum, isspace functions
#include <string.h>
#include <stddef.h>     //for size_t
///in this chapter we review the structure data structure as a container can contains different types of elements
struct Point{int x, y} point1, point2;
struct Rect{struct Point p1, p2;};

///play with structs
void testStruct(void){
    struct Point p ={0,0};
    struct {int x, y;} yes, no;
    yes.x =10;
    yes.y = 20;
    no.y=5;
    printf("%d", yes.x);
}

///play with structs with functions
#define min(a, b) (a<b)? a : b
#define max(a, b) (a>b)? a : b

//path by reference to avoid copy cost in the running time
void addPoints(struct Point * p1, struct Point * p2){
    p1->x += p2->x;
    p1->y += p2->y;
}
struct Point makePoint(int x, int y){
    struct Point p;
    p.x = x;
    p.y = y;
    return p;
};

///play with arrays of structures
//count the occurrence of keywords need two parallel arrays one for keywords and one for counting
//but we can do it by just array of structures and every structures has 2 elements word, count
#define MAXWORD 200
struct KWord{
    char* word;
    int coun;
} keywords[] ={{"auto", 0},{"break", 0},{"case", 0},{"char", 0},{"const", 0}, {"continue", 0}};

#define NKEYS (sizeof(keywords)/sizeof(keywords[0]))
//the expression in #define does not evaluated by the preprocessor

//get char
#define BUFFSZ 1000
int buff[BUFFSZ];
int buffpoin=0;
int getch(){
    if(buffpoin==0) return getchar();
    else return buff[--buffpoin];
}

//unget char
void ungetch(int c){
    if(buffpoin<BUFFSZ)
        buff[buffpoin++] = c;
    else{
        printf("error is buffer overflow\n");
    }
}

//get word from the stdin input file
int getword(char* wrd, int M){
    int c;
    char* w=wrd;

    while(isspace(c=getch()));

    if(c!='$') *w++=c;
    if(!isalpha(c) && c!='_'){*w='\0'; return c;} //this char is skipped from the key

    //read the remaining of the word
    for(; --M>0; w++)
        if(!isalnum(*w=getch()) && *w!='_'){
            ungetch(*w);
            break;
        }
    *w = '\0';
    return wrd[0];
}

//binary search
int binSearch(word){
    int l, r, m, cond;
    l=0; r=NKEYS-1;
    while(l<=r){
        m= (l+r)/2;
        if((cond=strcmp(word, keywords[m].word))>0)
            l=m+1;
        else if(cond<0)
            r=m-1;
        else
            return m;
    }
    return -1;
}

//read the file of source code
void readCode(char file[]){
    int n;
    char word[MAXWORD];

    while(getword(word, MAXWORD) != '$')
        if(isalpha(word[0]) && (n=binSearch(word))>=0)
            keywords[n].coun++;

    //print counts of words
    for(n=0; n<NKEYS; n++)
        if(keywords[n].coun>0)
            printf("%s : %d\n", keywords[n].word, keywords[n].coun);

}


///play with pointers with structures

#endif // CHAPTER6_H_INCLUDED
