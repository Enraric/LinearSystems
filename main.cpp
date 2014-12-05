<<<<<<< HEAD
// Alex's job: Math Things
// Harry's job: parsing
// Wilson's job: File stuff + misc...

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"

int main(){
	
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <iostream>


struct Line {
       int a;
       int b;
       int e;
};

struct System {
       Line one;
       Line two;
};
<<<<<<< HEAD
>>>>>>> origin/master
=======

/*
int parse (char str[80], int expNum){
    int SScount = 0;
    int partition = 0;
    char temp [80] = {""};
    //attempting to handle format of ( - # ) OP ( - # ), with spaces between anything
    //walks through array, looking for a different sentinels
    for (int i = 0; str[i] != 0; i++){
        printf ("%i\t%c\t%i\n", i, str[i], partition);
        switch (partition){
        case 0:
             //finds beginning of expression
            if (str[i] == '(')
                partition ++;
            break;
        case 1:
             //finds any negative signs, each one switches the current sign
            //also takes all digits until the slash or bracket
            //replace with function if time allows
            if (str[i] == '-')
                exps[expNum].num1.sign = signSwap (exps[expNum].num1.sign);
            else if (validInt (str [i])){
                temp[SScount] = str[i];
                SScount ++;
            }
            else if (str[i] == '/'){
                temp [SScount+1] = 0;
                exps[expNum].num1.num = atoi (temp);
                SScount=0;
                partition ++;
            }
                break;
        case 2:
            if (str[i] == '-')
                exps[expNum].num1.sign = signSwap (exps[expNum].num1.sign);
            else if (validInt (str [i])){
                temp[SScount] = str[i];
                SScount ++;
            }
            else if (str[i] == ')'){
                temp [SScount+1] = 0;
                exps[expNum].num1.denom = atoi (temp);
                SScount=0;
                partition ++;
            }
                break;
        case 3:
             //Assigns operator type
            if (str [i] == '+' || str [i] == '-' || str [i] == '/' || str [i] == '*')
                //exps[expNum].op = str[i];  NEEDS FIXING (How are we storing the enum type of operator? what do we need it to do?)
                partition ++;
            break;
        case 4:
             //detects start of second fraction
            if (str [i] == '(')
                partition ++;
                break;
        case 5:
            if (str[i] == '-')
                exps[expNum].num2.sign = signSwap (exps[expNum].num2.sign);
            else if (validInt (str [i])){
                temp[SScount] = str[i];
                SScount ++;
            }
            else if (str[i] == '/'){
                temp [SScount+1] = 0;
                exps[expNum].num2.num = atoi (temp);
                SScount=0;
                partition ++;
            }
                break;
        case 6:
            if (str[i] == '-')
                exps[expNum].num2.sign = signSwap (exps[expNum].num2.sign);
            else if (validInt (str [i])){
                temp[SScount] = str[i];
                SScount ++;
            }
            else if (str[i] == ')'){
                temp [SScount+1] = 0;
                exps[expNum].num2.denom = atoi (temp);
                SScount=0;
                partition ++;
            }
                break;
        default:
            break;
        }
    }
    if (partition >= 7){
        printf ("parse complete\n\n");
        return 1;
    }
    else{
        printf ("Parse Failed\n");
        return 0;
    }
}
*/

int main (){
    printf ("Hello, world...\n");
    system ("PAUSE");
}
>>>>>>> origin/master
