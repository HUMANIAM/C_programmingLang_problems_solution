#ifndef CHAPTER4_H_INCLUDED
#define CHAPTER4_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
static int a=5;

int strLength(char s[]){
    int i=0;
    while(s[i] != '\0') i++;
    return i;
}

//find the rightmost occurrence position of t in s
int strrIndex(char s[], char t[]){
    int ns = strLength(s);
    int nt = strLength(t);
    int i=ns-nt;

    while(i>=0){
        int j = i;
        int k=0;
        while(t[k] != '\0' && s[j] == t[k]){
            k++; j++;
        }
        if(t[k] == '\0') return i;
        i--;
    }
    return -1;
}

//expand the scientific notation number
double scientificNotation(char a[]){
    double n = 0.0, power=1.0;
    int i = 0, sign = 1;

    while(isspace(a[i])) i++;

    if(a[i] == '-') sign = -1;
    if(a[i] == '-' || a[i]=='+') i++;

    //integer part
    for(;isdigit(a[i]); i++)
        n = n*10.0 + (a[i]-'0');

    //processed the .
    if(a[i] == '.') i++;
    //float part
    while(isdigit(a[i])){
        n = n*10.0 + (a[i]-'0');
        power *= 10;
        i++;
    }
    //handle e , E
    if(a[i] =='e' || a[i] == 'E'){
        i++;
        int neg = 0;
        int exp = 0;
        if(a[i] == '-'){ i++; neg = 1;}

        while(isdigit(a[i]))
            exp = exp*10 + (a[i++]-'0');

        if(neg)
            while(exp--)
                power *= 10;
        else
            while(exp--)
                power /= 10;
    }
    return sign*(n/power);
}

//simple calculator using (reverse polish notation)
//*************************************************
#define MAXOP 100
#define NUMBER '0'
#define MAXVAL   100
#define BUFSIZE  100
char buf[BUFSIZE];      //for ungetch chars
int bufp = 0;
int sp = 0;
double Stack[MAXVAL];

//get possibly pushed back character
int getch(void){
return (bufp>0)? buf[--bufp] : getchar();
}

void ungetch(int c){
if(bufp>BUFSIZ)
    printf("error : too many ungetch chars\n");
else
    buf[bufp++] = c;
}

int getop(char s[]){
    int i, c;
    while((c=s[0]=getch()) == ' ' || c=='\t');
    s[1] = '\0';

    if(!isdigit(c) || c=='.')
        return c;       //not number
    i=0;
    if(isdigit(c))//get integer part
        while(isdigit(s[++i]=c=getch()));

    if(c=='.') //get fractional part
        while(isdigit(s[++i]=c=getch()));

    s[i] = '\0';

    if(c!=EOF)
        ungetch(c);
    return NUMBER;
}

void push(double v){
    if(sp < MAXVAL)
        Stack[sp++]=v;
    else printf("error : stack full can't push %g\n", v);
}

double pop(void){
    if(sp>0)
        return Stack[--sp];
    else{
        printf("error : stack is empty \n");
        return 0.0;
    }
}

//implement the Stack using structure
typedef struct Stack st,  *stpr;
struct Stack{
    int sp;
    int* arr;

    //helper methods
    void (*pop)(stpr);
    void (*push)(stpr, int);
    int  (*top) (stpr);
    void (*duplicate)(stpr);
    void (*topSwap) (stpr);
    void (*sclear) (stpr);
};

void sclearStack(stpr s){
    s->sp =0;
}

void topswapStack(stpr s){
    int x = s->top(s);
    s->pop(s);
    int y = s->top(s);
    s->pop(s);
    s->push(s, x);
    s->push(s, y);
}

void duplicateStack(stpr s){
    s->push(s, s->top(s));
}

int topStack(stpr s){
    if((s->sp) > 0) return (s->arr)[(s->sp)-1];
    else printf("error : stack is empty\n");
}

void pushStack(stpr s, int n){
    if((s->sp) < 100) (s->arr)[(s->sp)++] = n;
    else printf("error : stack is full\n");
}

void popStack(stpr s){
    //init stack
    if((s->sp) > 0) --(s->sp);
    else printf("error : stack is empty\n");
}

//to use this functions you need to pair them with the struct functions
void initStack(stpr s){
    s->sp = 0;
    s->arr = (int*) malloc(100*sizeof(int));
    s->duplicate = duplicateStack;
    s->pop = popStack;
    s->push = pushStack;
    s->top = topStack;
    s->sclear = sclearStack;
    s->topSwap = topswapStack;
}
//****************************************************
void itoA(int n, char arr[], int len){
    static int i = 0;
    if(len==0) return;

    i++;
    itoA(n/10, arr, len-1);
    arr[len-1] = n%10+'\0';
}

#endif // CHAPTER4_H_INCLUDED
