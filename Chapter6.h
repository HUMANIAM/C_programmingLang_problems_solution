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

///play with self referential structures
//using binary search tree to count unexpected number of words
// this coming program is provide the following features
/**
1- read c program from stdin or from file
2- sort words in groups every group has words that has the same initial n chars
3- ignore comments, constant strings, <*> and keywords{const, int, default case, if, else, while for, int, float, long, double, include, define, .....}
4- print groups in ascending order lexicographically
*/
#define MAXWORD 200         //maximum length of word
#define BUFFSZ 1000         //for ungetch function
int buff[BUFFSZ];
int buffpoin=0;

typedef struct Word{    //every word points to the next word to it in the same group
    char* word;
    struct Word * nextWord;
} Word;

typedef struct Node{    //every node in the tree represent its group so it is a tree of groups of words not word
    Word * wrordsInGroup;
    int coun;
    struct Node * left, * right;
} Node;

typedef struct Key{
    char* key;
    struct Key * left, * right;
} KeyNode;

char* keywords[] = { "include", "define", "main", "typedef", "int", "return", "float", "double", "unsigned", "signed"
                      "if", "else", "for", "while", "case", "switch", "default", "volatile", "struct", "union", "enum",
                      "ifdef", "ifndef", "break", "continue", "char"
                    };
#define KEYWORDS sizeof(keywords) / sizeof(keywords[0])
int first_match_chars = 1;

KeyNode * keysRoot = NULL;  //for representing bst of keywords to search if word is in keywords or not

//get char
int getch(FILE * fh){
    if(buffpoin==0) return fgetc(fh);
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

//build binary search tree for the keywords
KeyNode * add2bstKey(KeyNode* node, char* wrd){
    int cond;
    if(node == NULL){
        //create node
        node = (KeyNode *) malloc(sizeof(KeyNode));
        if(node == NULL){
            perror("not enough memory to add new key\n");
            exit(1);

        }else{
            node->key = wrd;
            node->left = node->right = NULL;
        }
    }else if((cond=strcmp(node->key, wrd))>0){
        node->left = add2bstKey(node->left, wrd);

    }else if (cond < 0){
        node->right = add2bstKey(node->right, wrd);

    }else{}

    return node;
}

//build bst of key words
void build_BST_Keys(){
    int i=0;
    while(i<KEYWORDS)
        keysRoot = add2bstKey(keysRoot, keywords[i++]);
}

//binary search in key words
int bstKeys(KeyNode * node, char* wrd){
    int cond;
    if(node != NULL){
        if((cond = strcmp(wrd, node->key)) == 0)
            return 1;

        else if (cond<0)
            return bstKeys(node->left, wrd);

        else
            return bstKeys(node->right, wrd);
    }
    return -1;
}

//get word from the stdin input file
int getword(FILE* fh, char* wrd, int M){
    int c;
    char* w=wrd;

    while(isspace(c=getch(fh)));

    //skip words in ""
    if(c=='"')
        while((c=getch(fh)) != '"' && c != EOF);

    //skip <*>
    if(c=='<')
        while((c=getch(fh)) != '>' && c != EOF);

    //skip words after comments // or /*/
    else if(c=='/'){
        c=getch(fh);

        // if // comment
        if(c=='/')
            while(c!='/' && c!=EOF && c!='/n') c=getch(fh);

        else if(c=='*'){// ignore all characters between /* */
            while(1){
                c = getch(fh);
                if((c=='*' && ((c=getch(fh)=='/' || c==EOF))) || c == EOF) break;
            }

        }
        while((c=getch(fh)) != '\n' && c != EOF);
    }


    if(c != EOF) *w++=c;
    if(!isalpha(c) && c!='_'){*w='\0'; return c;} //this char is skipped from the key

    //read the remaining of the word
    for(; --M>0; w++)
        if(!isalnum(*w=getch(fh)) && *w!='_'){
            ungetch(*w);
            break;
        }
    *w = '\0';
    return wrd[0];
}

//duplicate word
char* strdup(const char* wrd){
    struct Word* pw = (struct Word *) malloc(sizeof(struct Word));

    if(pw != NULL){
        char* p = (char*) malloc(strlen(wrd)+1);

        if(p != NULL){
            strcpy(p, wrd);
            pw->word = p;
            pw->nextWord = NULL;

        }else{
           perror("there is not enough memory\n");
           exit(1);
        }

    }else{
        perror("there is not enough memory\n");
        exit(1);
    }

    return pw;
}

//create new node
struct Node * talloc(char* wrd){
    struct Node* p = (struct Node* ) malloc(sizeof(struct Node));

    if(p != NULL){
        p->wrordsInGroup = strdup(wrd);
        p->coun = 1;
        p->left = p->right = NULL;

    }else{
        perror("there is not enough memory\n");
        exit(1);
    }
    return p;
}

//building the binary search tree
struct Node * add2Goups(struct Node* node, char* wrd){
    int cond;
    if(node == NULL){
        node = talloc(wrd);
//        printf("add %s to new node\n", wrd);
    }else if((cond=strncmp(wrd, (node->wrordsInGroup)->word, first_match_chars)) == 0){  //increment the current node by 1
//        printf("add %s to group of %s\n", wrd, (node->wrordsInGroup)->word);
        node->coun++;
        Word* p = node->wrordsInGroup;
        while(p->nextWord != NULL) p = p->nextWord;

        //create new word
        p->nextWord = strdup(wrd);

    }else if(cond < 0){  //go to the left branch
        node->left = add2Goups(node->left, wrd);

    }else{  // go to the right branch
        node->right = add2Goups(node->right, wrd);
    }
    return node;
};
//
////print words occurrence dfs with in order traverse
////display them in a sorted order
void printGroups(Node* root){
    if(root == NULL) return;

    printGroups(root->left);      //left branch

    struct Word * p = root->wrordsInGroup;

    printf("This group matches in : ");
    int i = 0;
    int n = strlen(root->wrordsInGroup->word);

    while(i<first_match_chars && i<n)
        printf("%c", *((root->wrordsInGroup)->word + i++));
    printf(" and has %d words\n---------------------------------\n", root->coun);

    while(p != NULL){
        printf("%s\n", p->word);
        p = p->nextWord;
    }
    printGroups(root->right);      // right branch

}

void readWords(const char* file, int n){
    FILE * fh;
    //open the file
    if((fh = fopen(file, "r")) == NULL){
        printf("File : %s not exits check the path\n", file);
        exit(1);
    }

    first_match_chars = n;

    struct Node * root = NULL;  //root of the bst of groups
    char word[MAXWORD];

    build_BST_Keys();       //build bst of key words

    //groups words in the input file according to the first n characters match
    while(getword(fh, word, MAXWORD) != EOF)
        if(isalpha(word[0]) && bstKeys(keysRoot, word) == -1)
            root = add2Goups(root, word);


    //print groups
    printGroups(root);

}

//sort words decreasingly according to frequencies
struct Node* addWordSortByFreq(struct Node* node, const char* wrd){
    int n = strlen(wrd);
    if(node == NULL){
        node = talloc(wrd);

    }else if(strcmp(wrd, (node->wrordsInGroup)->word ) == 0){  //increment the word frequency
        node->coun++;

    }else if(n < node->coun){// add to left branch
        node->left = addWordSortByFreq(node->left, wrd);

    }else{      //add to right branch
        node->right = addWordSortByFreq(node->right, wrd);
    }
    return node;
};

//read arguments to the program
void readArgs(int argv, char** argc, int* n, char* file){
     while(--argv > 0 && **++argc=='-'){
        switch(*(++(*argc))){
            case 'n' :
                if(--argv > 0)
                    if((*n = atoi(*++argc)) == 0) *n++;
              break;

            case 'f' :
                if(--argv > 0)
                    strcpy(file, *++argc);
                break;

            default:
                printf("%s incorrect option where options -f filepath -n matched chars length", *argc);
                exit(1);
        }
    }

    if(argv > 0){
        printf("add correct options before passed arguments -f or -n\n");
        exit(1);
    }
}

#endif // CHAPTER6_H_INCLUDED
