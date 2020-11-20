#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void IOerror();

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
    int cin = getchar();
    IOerror();

    //tr translate
    while (cin != EOF){
        char cout = cin;
        int k;
        for (k=0; k<flen; k++)
        {
            if (cin == from[k])
            {
                cout = to[k];
                break;
            }
        }
        
        putchar(cout);
        IOerror();
        
        cin = getchar();
        IOerror();
    }


}


void IOerror(){
    if(ferror(stdout) || ferror(stdin)){
        fprintf(stderr, "Error with input/output");
        exit(1);
    }
}

