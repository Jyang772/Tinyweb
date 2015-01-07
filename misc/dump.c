//HexDump function
#include <stdio.h>

void dump(char *buffer, int length){
    
    int i,j;
    char byte;
    for(i=0; i<length; i++){
        
        if(i%16 == 0)
            printf("%08x ",i);
        printf("%02x ",buffer[i]);
        
        if( (i%16==15) || (i==length-1)){ 
            for(j=0;j<15-(i%16);j++)              //Fill remaining spaces
                printf("   "); 
            printf("| ");
            
            for(j=(i-(i%16));j<=i;j++){        //Print out characters. 
                byte = buffer[j];
                if(byte > 31 && byte < 127)  //Printable range
                    printf("%c",byte);
                else
                    printf(".");
            }
            printf("\n");
        }
    }
}
