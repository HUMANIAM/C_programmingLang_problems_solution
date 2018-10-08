#ifndef CHAPTER5_H_INCLUDED
#define CHAPTER5_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>

//getint function as example of call by reference
void getInt(int* pn){
int c, sign = 1;
while(isspace(c=getchar()));

if(c=='-') sign = -1;
if(c=='+' || c=='-') c=getchar();

for(*pn=0; isdigit(c); c=getchar()){
    *pn = 10* *pn + (c-'0');
}

*pn *= sign;

return c;
}

//another version of strlen
int strlen(char* s){
    int i=0;
    while(*s){ i++;}
    return i;
}

//define user defined malloc and mfree
#define ALLOCSZ 100000
static char allocbuf[ALLOCSZ];      //allocbuf is the free space
static char *allocp = allocbuf;     //next free position

//alloc memory
char* alloc(int n){
    if((allocbuf + ALLOCSZ - allocp) >= n){
        allocp += n;
        return allocp - n;
    }else return 0;
}

//free the memory
void afree(char *p){
    if(p>=allocbuf && p < allocbuf+ALLOCSZ) allocp = p;
}

//strcat
void strcat(char* s, char* t){
    char* tp = s;
    while(*tp) tp++;
    while(*tp++=*t++);
}

//strend
int strend(char* s, char* t){
    int l = 0;
    while(*s) s++;
    while(*t) {l++; t++;}
    l++;
    while(l-- && *s--==*t--);
    return l==-1? 1:0;
}

#define MAXLINES 5000
#define MAXLEN   200
char* lineptr[MAXLINES];        //pointers to lines

void strcpy(char* s1, char* s2){
    while(*s1++=*s2++);
}


///you can see that in the stack implementation we use a pointer to function inside the struct where in c you can't use function inside a structure
///here is another implementation to a pointer to function. used to sort strings in ascending order according to numeric values
///we add an option to use strcmp() or numcmp()
/// this program provide running option -r to sort in descending order or -n to sort numeric values no option sort in lexographically
struct Options{
    int n, r, d, f;
};
//read line
int getline(char* arr, int n){
    int i=0;
    char c;
    while((c=getchar())!='\n' && i<n) arr[i++]=c;
    arr[i] = '\0';
    return i;
}
//read lines
int readLines(char** lineptr, int mlines, int mline){
    int len=0, nlines=0;
    char line[mline];

    printf("Enter empty line break the entering mode\n");

    while((len=getline(line, mline))>0){
        if(nlines>=mlines){
            return -1;
        }else{
            char* a = alloc(len+1);
            strcpy(a, line);
            lineptr[nlines++] = a;
        }
    }

    return nlines;
}

//write lines
void writeLines(char** linesptr, int nlines){
    while(nlines--)
        printf("%s \n", *linesptr++);
}

//sort these lines using qsort
void swap2e(char** lines, int i, int j){
    char* tmp = lines[i];
    lines[i] = lines[j];
    lines[j] = tmp;
}

//srcmp
int strcmp(char* s1, char* s2){
    for(; *s1==*s2; s1++, s2++)
        if(*s1=='\0') return 0;

    return *s1 - *s2;
}

//numcmp
int numcmp(char* s1, char* s2 ){
    double v1 = atof(s1);
    double v2 = atof(s2);

    if(v1<v2)
        return -1;
    else if(v1>v2)
        return 1;
    else
        return 0;
}

void qsorta(char** lines, int l, int r, int(*cmp)(void*, void*), struct Options op){
    if(l>=r) return;

    //pick a pivot
    swap2e(lines, l, (l+r)/2);

    int i, last;
    last  = l;
    for(i=l+1; i<=r; i++)
        if(op.r==0 && (*cmp)(lines[i], lines[l]) <0 || op.r==1 && (*cmp)(lines[i], lines[l]) >0)
            swap2e(lines, i, ++last);

    swap2e(lines, l, last);
    qsorta(lines, l, last-1, cmp, op);
    qsorta(lines, last+1, r, cmp, op);

}

int linesComparator(int argv, char** argc){
    int lines, c;
    struct Options op ={0, 0, 0, 0};

    while(--argv>0 && (*++argc)[0] == '-'){
       while(c=*++argc[0])
            switch(c){
            case 'n' :
                op.n = 1;
                break;
            case 'r' :
                op.r = 1;
                break;
            case 'f' :
                op.f = 1;
                break;
            case 'd' :
                op.d = 1;
                break;
            default:
                printf("invalid option\n");
                printf("usage sort -n -r | sort -n | sort -r | sort");
                return 1;
            }
    }

    if((lines=readLines(lineptr, MAXLINES, MAXLEN))>0){
        //sort read lines
        qsorta(lineptr, 0, lines-1, (int(*)(void*, void*))op.n? numcmp:strcmp, op);
        writeLines(lineptr, lines);
        return 0;
    }else{
        return 1;
    }
}

//concatenate
char* concatenate(char* a, char* b){
    //static char *p = (char*)malloc(100);
    //sprintf(p, "%s%s", a, b);
    return NULL;
}
#endif // CHAPTER5_H_INCLUDED
