#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>



int main()
{
regex_t regex;
int reti;
char input[100];
char msgbuf[100];


//TO-DO: Move into Misc folder of Tinyweb. Verify IP Addresses
//Current
//Email verification via REGEX
//reti = regcomp(&regex, "(\\+|-)?[[:digit:]]+",REG_EXTENDED);
reti = regcomp(&regex,"^([a-z0-9_\.-]+\@[\da-z\-]+\.[a-z\.]{2,6})$",REG_EXTENDED);
if(reti){fprintf(stderr,"Could not compile regex!\n"); exit(1);}



while(1){
        printf("Give me a valid email!\n");
        scanf("%s",input);
        printf("Inputted: %s\n",input);
        if(strcmp(input,"q") == 0)
                break;

        reti = regexec(&regex,input,0,NULL,0);
        if(!reti){
                puts("Match");
                }
        else if(reti == REG_NOMATCH){
                puts("No match");
        }
        else{
                regerror(reti, &regex, msgbuf, sizeof(msgbuf));
                fprintf(stderr,"Regex match failed: %s\n",msgbuf);
                exit(1);
        }
}
        regfree(&regex);
        return 0;
}



//int main(){
//    char buffer[1000];
//    int count = 0;
//    double sum = 0;
//    int num,num1;
//    fgets(buffer, sizeof buffer, stdin);
//    const char *p = buffer;
//    int n;

////    sscanf(p,"%d%n",&num,&num1, &n);
////    printf("characters scanned: %d\n",n);
////    printf("Number read: %d\n",num);


//    while (sscanf(p, "%d%n", &num, &n) == 1) {
//        printf("Nothing printed: %d\n",n);
//        p += n;
//        printf("Printing from p: %s",p);

//        sum += num;
//        count++;
//    }
//    printf("Average %f\n", sum/count);

//}

