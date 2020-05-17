#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> 

char* printascii(int n){
    switch(n){
        case 0: 
            return "NUL";
        case 1:
            return "SOH";
        case 2: 
            return "STX";
        case 3:
            return "ETX";
        case 4: 
            return "EOT";
        case 5:
            return "ENQ";
        case 6: 
            return "ACK";
        case 7:
            return "BEL";
        case 8: 
            return "BS";
        case 9:
            return "HT";
        case 10: 
            return "LF";
        case 11:
            return "VT";
        case 12: 
            return "FF";
        case 13:
            return "CR";
        case 14: 
            return "SO";
        case 15:
            return "SI";
        case 16: 
            return "DLE";
        case 17:
            return "DC1";
        case 18: 
            return "DC2";
        case 19:
            return "DC3";
        case 20: 
            return "DC4";
        case 21:
            return "NAK";
        case 22: 
            return "SYN";
        case 23:
            return "ETB";
        case 24: 
            return "CAN";
        case 25:
            return "EM";
        case 26: 
            return "SUB";
        case 27:
            return "ESC";
        case 28: 
            return "FS";
        case 29:
            return "GS";
        case 30: 
            return "RS";
        case 31:
            return "US";
        case 127: 
            return "DEL";  
    }
    return " ";
}

void printchar(char* input){
        for (int i = strlen(input); i < 8; ++i)
                input[i] = '0';
        input[8] = '\0';
        int parity = 0;
        int decimal = 0;    
        for (int i = 0; i < 8; ++i) {
            int d = input[i] - '0';
            decimal += d * 1 << (7 - i);
            parity ^= d;
        }
        decimal &= 0x7F;
        if(decimal<=32||decimal==127){
            char* ascii = printascii(decimal);
            printf("%8s  %5s  %7d  %6s\n", input, ascii, decimal,
                                       parity ? "ODD" : "EVEN");
        }else{
        printf("%8s  %5c  %7d  %6s\n", input, decimal, decimal,
                                       parity ? "ODD" : "EVEN");
        }
}

int main(int argc, char* argv[]) {
    int filedesc = open(argv[1], O_RDONLY);
    if (filedesc<0) {
    char** arg=argv+1;
    if(*argv[1]=='-')
        arg=argv+2;   
    puts("Original  ASCII  Decimal  Parity");
    puts("--------  -----  -------  ------");
    for(; *arg!=argv[argc]; arg++){
         printchar(*arg);
    } //end for
  } //end of if no file found statement
    else{   
    char byte;
    char input[9];
    int index=0;
    puts("Original  ASCII  Decimal  Parity");
    puts("--------  -----  -------  ------");
    while (read(filedesc, &byte, 1) > 0) {
        if(byte!=' '&&byte!='\n'){
            input[index]=byte;
            index++;
        }else{
            printchar(input);
            index=0;
            memset(&input[0], 0, sizeof(input));
            } 
        } //end while
        printchar(input);
    } //end else
    
    return 0;
    }
