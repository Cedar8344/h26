#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

int frobcmp(char const * a, char const * b);
int cmp(const void * a, const void * b);
void printw(char const* a);

int flag = 0; //global, to be used in frobcmp
//seriously have no idea why the autograder is returning 1/8 passed. I'm realtively sure I
// dont have the errors described, and the manual test cases worked for sfrobu.c
int main(int argc, char* argv[])
{
    //check for flag
    if(argc == 2){
        char * correctflag = "-f";
        if(strcmp(argv[1], correctflag) == 0){
            flag = 1;
        }
        else{
            char* err = "Error with flag, use -f";
            write(2, err, strlen(err));
            exit(1);
        }
    }
    //check size
    if(argc > 2){
        char* err ="Error with arguments, too many passed";
        write(2, err, strlen(err));
        exit(1);
    }

    //get filedata
    struct stat fileData;
    //exit if we have error with fstat
    if(fstat(STDIN_FILENO, &fileData) < 0){
        char* err = "Error with fstat";
        write(2, err, strlen(err));
        exit(1);
    }

    //if we are using a regular file
    int usingFile = S_ISREG(fileData.st_mode);
    // defualt to 8192 byte buffer
    int buffer = 8192*sizeof(char);
    //if we are using regular file, set buffer size to file size
    if(usingFile){
        buffer = fileData.st_size*sizeof(char)+2;
    }
    //create buffer
    char* b = (char*) malloc(buffer);

    int nc = 1;
    b[0] = ' ';
    char c;

    if(usingFile){
        nc = fileData.st_size;
        read(0, b+1,nc++);
        lseek(0,0,SEEK_CUR);
    }
    //read in characters, 1 at a time
    while(read(0,&c, 1)){
        // double buffer if needed
        if(nc >= buffer-1){
            buffer *= 2;
            b = (char*) realloc(b, buffer);
            if(b==NULL){
                char* err = "Error with memory";
                write(2, err, strlen(err));
                exit(1);
            }
        }
        b[nc++] = c;
    }
    b[nc++] = ' ';

    char** lines = (char**) malloc(sizeof(char**));
    if(lines == NULL){
        char* err = "Error with memory";
        write(2, err, strlen(err));
        exit(1);
    }
    char* tempWord = b;
    int temp = 0;
    int i;
    for(i=1; i<nc; i++){
        if(b[i-1] == ' '){
            lines = (char**) realloc(lines, sizeof(char*) * ++temp);
            tempWord = b + i;
            lines[temp-1] = tempWord;
        }
    }

    //Sort
    int (* fptr) (const void *, const void *) = &cmp;
    qsort(lines, temp, sizeof(char *), fptr);

    for(i=0; i<temp; i++){
        printw(lines[i]);
    }
    
    free(lines);
    free(b);
    return 0;  
}


int frobcmp(char const * a, char const * b)
{
    while (*a != ' ' && *b != ' ')
    {
        if (*a == ' ') return -1;
        if (*b == ' ') return 1;
        char x = *a ^ 42;
        char y = *b ^ 42;

        if (flag == 1)
        {
            x = toupper((unsigned char) x);
            y = toupper((unsigned char) y);
        }

        if (x < y)
            return -1;
        if (y > x)
            return 1;
        a++;
        b++;
    }
    return 0;
}

int cmp(const void * a, const void * b)
{
    return frobcmp(* (const char**) a, * (const char**) b);
}

void printw(const char* word){
  while(*word != ' '){
    write(1, word, 1);
    word++;
  }
  write(1, " ", 1);
}
