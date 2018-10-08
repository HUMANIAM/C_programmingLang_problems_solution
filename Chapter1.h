#ifndef CHAPTER1_H_INCLUDED
#define CHAPTER1_H_INCLUDED

//print format
void printFormat(){
    //the size of these objects are machine-dependent
    int x = 0;
    float y = 0.0;
    double z = 0.0;
    char c = 'a';
    unsigned int xx = 0;
    short s;
    long l;

    //printf("string format", parameters)
    /*
        int : %d, %i
        float : %int_digits.floatPoint_digitsf
        double : %f   (double precision float)
        long : %ld
        char : %c
        octal : %o
        hexa  : %x
        string : %s
        %      : %%

    */
}


//variables and arithmetic expressions
void fahTOCeluis(int from, int to){
    int fahr, lower, upper, step;
    float celsius;
    lower = from;
    upper = to;
    step = 20;

    fahr = from;

    while(fahr <= upper){
            //c = (5/9)*(f-32)
        celsius = (5.0*(fahr - 32))/9.0;
        printf("%3d\t%3.3f\n", fahr, celsius);
        fahr += step;
    }
}

//looping and symbolic constants
#define LOWER 0
#define UPPER 300
#define STEP 20

void fahTOCeluis_For(){
    int fahr;
    for(fahr = LOWER; fahr<=UPPER; fahr += STEP)
        printf("%d\t%6.1f\n", fahr, (5.0/9.0)*(fahr-32));
}

//character input/output functions to deal with text stream

void readStream(){
    #define SIZE 50
    char sentence [SIZE];
    int c;
    unsigned int  coun = 1, i=0;
    while((c = getchar()) != EOF && coun<SIZE){
        sentence[i++] = c;
        c = getchar();
    }
    sentence[i] = '\0';
    printf("\n%s\n", sentence);
}


//word/char count
void wrdCharCount(){
    #define IN 1
    #define OUT 0
    int wc, cc, nlc, c, state;
    wc = cc = nlc = 0;
    state = OUT;

    while((c = getchar()) != EOF){
        cc++;
        if(c == '\n') nlc++;
        if(c == ' ' || c == '\n' || c == '\t')  state = OUT;
        else if (state = OUT){
            state = IN;
            wc++;
        }
    }
    printf("%d\t%d\t%d\n", cc, wc, nlc);
}

// character array
#define MAXLENGTH 1000
//read line from the input file descriptor
int getline(char* str, int lim){
    char c;
    int i = 0;

    while((c = getchar()) != '@' && (i+1) < lim && c != '\n')
            str[i++] = c;


    if(c == '\n')
        str[i++] = c;

    str[i] = '\0';
    return i;
}

//copy content of string 1  to string 2
void copyca(char to[], char from[]){
    int i = 0;
    while((to[i] =from[i++]) != '\0');
}

//reverse content of string
void reverseStr(char str[], int n){
    int i, j;
    char c;
    for(i=0, j=n-2; i<j; i++, j--){
        c = str[i];
        str[i] = str[j];
        str[j] = c;
    }
}

#endif // CHAPTER1_H_INCLUDED
