#ifndef CHAPTER3_H_INCLUDED
#define CHAPTER3_H_INCLUDED
#include <ctype.h>
#include <string.h>
//example on using switch case
void escape(char s[], char t[]){
    int i;
    for(i=0; t[i] != '\0'; i++){
        switch(t[i]){
            case '\n':
                s[i] = '\\n';
            break;
            case '\t':
                s[i] = '\\t';
            break;
            default:
                s[i] = t[i];
            break;

        }
    }
}

int aToi(char s[]){
    int i, n=0, sign;
    for(i=0; isspace(s[i]); i++);

    sign = (s[i] == '-')? -1 : 1;
    (s[i] == '-' || s[i] == '+')? i++ : false;

    for(; s[i]!= '\0'; i++){
        n = n*10 + (s[i] - '0');
    }

    return sign*n;

}

void shellSort(int arr[], int n){

    int i, j, gap, c;

    for(gap=n/2; gap>0; gap/=2)
        for(i=gap; i<n; i++)
            for(j=i-gap; j>=0 && arr[j]>arr[j+gap]; j-=gap)
                c = arr[j], arr[j] = arr[j+gap], arr[j+gap] = c;
}

void swap2e(int v[], int l, int r){
    int t = v[r];
    v[r] = v[l];
    v[l] = t;
}

void qsort(int a[], int l, int r){
    int i, last;
    //solution in the book is better
    if(l>=r) return;

    swap(v, l, (l+r)/2);        //choose the pivot put it in the beginning
    //make all elements after pivot bigger and less pivot smaller
    last = l;
    for(i=l+1; i<=r; i++)
        if(a[i]<a[l])
            swap(a, ++last, i);

    swap(v, last, l);   //last has value <= left so swap them
    qsort(a, l, last-1);
    qsort(a, last+1, r);
}

int findHyphen(int p, char* s){
    while( s[p] != '-' && s[p] !='\0') p++;

    if(s[p] == '\0')
        return -1;
    return p;
}

void extends(char s1[], char s2[]){
    char alphaSmall[26] = "abcdefgHijklmnopqrstuvwxyz";
    char alphaCap [26]   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char digits [10] = "0123456789";

    int n = strlen(s1);
    int i = 0, nd0 = 0;

    if(n==0) return;

      while( ( nd0 = findHyphen(++nd0, s1)) != -1){

        if((nd0-1>=0) && (nd0+1)<n){
            //assuming the range is identical family such as a-z A-Z not a-Z
            char from = s1[nd0-1];
            char to  = s1[nd0+1];

            if(from>='a' && from<='z'){
                while(from<=to){
                    s2[i++] = alphaSmall[from-'a'];
                    from++;
                }
            }else if(from>='A' && from<='Z'){
                while(from<=to){
                    s2[i++] = alphaCap[from-'A'];
                    from++;
                }

            }else if(from>='0' && from<='9'){
                while(from<=to){
                    s2[i++] = digits[from-'0'];
                    from++;
                }

            }else{
                printf("range at %d to %d is not valid\n", from+1, to+1);
            }

        }
    }
    s2[i] = '\0';

}

void reversea(char s[]){
    int i;
    char t;
    int n = strlen(s);
    for(i=0; i<n/2; i++)
         t=s[i], s[i] = s[n-1-i], s[n-1-i]=t;
}

void itob(int n, char s[], int b){
    char* Digits = "0123456789ABCDEF";
    int i=0;
    while(n/b){
        s[i++] = Digits[n%b];
        n /= b;
    }
    s[i++] = Digits[n];
    s[i] = '\0';
    reversea(s);
}

#endif // CHAPTER3_H_INCLUDED
