//CADET's first C program

#include "libcgc.h"
#include "cgc_libc.h"

#define HI "\nWelcome to Palindrome Finder\n\n"
#define ASK "\tPlease enter a possible palindrome: "
#define YES "\t\tYes, that's a palindrome!\n\n"
#define NO "\t\tNope, that's not a palindrome\n\n"
#define EASTEREGG "\n\nEASTER EGG!\n\n"

int cgc_check();

int main(int cgc_argc, char *cgc_argv[]) {
    int r;

    if (cgc_transmit_all(1, HI, sizeof(HI)-1) != 0) {
        cgc__terminate(0);
    }
    
    while(1){
        if (cgc_transmit_all(1, ASK, sizeof(ASK)-1) != 0) {
            cgc__terminate(0);
        }
        r = cgc_check();
        if (r == -1){
            break;
        }
        else if (r == 0){
            if (cgc_transmit_all(1, NO, sizeof(NO)-1) != 0) {
                cgc__terminate(0);
            }
        }
        else{
            if (cgc_transmit_all(1, YES, sizeof(YES)-1) != 0) {
                cgc__terminate(0);
            }
        }
    }
    return 0;
}

int cgc_check(){
    int len = -1;
    int i;
    int pal = 1;
    char string[64];
    for (i = 0; i < sizeof(string); i++)
        string[i] = '\0';
#ifdef PATCHED
    if (cgc_receive_delim(0, string, sizeof(string), '\n') != 0)
        return -1;
#else    
    if (cgc_receive_delim(0, string, 128, '\n') != 0)
        return -1;
#endif
    for(i = 0; string[i] != '\0'; i++){
        len++;
    }
    int steps = len;
    if(len % 2 == 1){
        steps--;
    }
    for(i = 0; i <= steps/2; i++){
        if(string[i] != string[len-1-i]){
            pal = 0;
        }
    }
    if(string[0] == '^'){
        if (cgc_transmit_all(1, EASTEREGG, sizeof(EASTEREGG)-1) != 0) {
            cgc__terminate(0);
        }
    }    
    return pal;
}
