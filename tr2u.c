#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char*argv[]){
    if(argc != 3){
        fprintf(stderr, "Error with given arguments. Please provide 2 strings");
        exit(1);
    }
    const char* from = argv[1];
    const char* to = argv[2];   
    int flen = strlen(from);
    int tlen = strlen(to);
    //check same length
    if(flen != tlen){
        fprintf(stderr, "Error with arguments. From/To must be the same length");
        exit(1);
    } 
    //check for dupes in from
    int i;
    for(i=0; i<flen; i++){
        const char c = from[i];
        int j;
        for(j=i+1;j<flen;j++){
            if(c==from[j]){
                fprintf(stderr, "Error with from. From cannot have duplicates\n");
                exit(1);
            }
        }
    }

    //tr translate using system calls
    while (1){
        char* cc = (char *) malloc(sizeof(char));
        ssize_t readin = read(0, cc, 1);
        if (read < 0)
        {
            fprintf(stderr, "Error with input");
            exit(1);
        }
        if (readin == 0) break; //reached end of file
        char cout = *cc;
        int i;
        for (i = 0; i < flen; i++)
        {
            if (cout == from[i])
            {
                cout = to[i];
                break;
            }
        }
        ssize_t writeout = write(1, &cout, 1);
        if (writeout <= 0)
        {
            fprintf(stderr, "Error with output");
            exit(1);
        }
    }
}
