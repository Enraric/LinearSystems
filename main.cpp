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

System systs [30];
int numSysts = 0;

//Alex's Mathemagical Mathland//////////////////////////////////////////////////////////////////////////////

Line lineMult (Line A, int B){ //screw naming convention
    A.a = A.a * B;
    A.b = A.b * B;
    A.e = A.e * B;
    return A;
}

float systSolve (Line lineA, Line lineB){
    return (lineA.e - lineB.e)/(lineA.b - lineB.b);
}

float lineSub (float y, Line line){
    return (line.e - line.b*y)/line.a;
}

void mathStuff (int i){

    Line lineC;
    Line lineD;
    float x, y;

    lineC = lineMult(systs[i].one, systs[i].two.a);
    lineD = lineMult(systs[i].two, systs[i].one.a);

    y = systSolve (lineC, lineD);
    x = lineSub (y, systs[i].one);

}

void mathHandler(){

    for (int i = 0; i < numSysts; i++){
        mathStuff (i);
    }

}

//___________________________________________________________________Begin Parse

bool validInt (char character){//functions are handy and stuff
    return (character >= 48 && character <= 57);
}

int parse (char str[80], int expNum){
    int SScount = 0;
    int partition = 0;
    char temp [80] = {""};
    //Looks like Ill have time to actually turn this mess into functions this time: yay
    //attempting to handle format of "slopex+-intercept/slopex+-intercept"
    //walks through array, looking for a different sentinels (#, x, + or -, #, /, #, x, + or -, #)
    //example valid expression: "12x+4/6x-2"
    //potential additions: fractions for slope (feel free to add more, guys)
    for (int i = 0; str[i] != 0; i++){
        printf ("%i\t%c\t%i\n", i, str[i], partition);
        switch (partition){
        case 0: //adds numbers to a temp string until x
            if (validInt (str [i])){
                temp[SScount] = str[i];
                SScount ++;
            }
            else if (str[i] == 'x'){
                temp [SScount] = 0;
                systs[expNum].one.a = atoi (temp);
                SScount=0;
                partition ++;
            }
        case 1: //finds operator (neccesary?)
            if (str[i] == '-' || str[i] == '+')
                partition ++;
        case 2: //finds y intercept
            if (validInt (str [i])){
                temp[SScount] = str[i];
                SScount ++;
            }
            else if (str[i] == '/'){
                temp [SScount] = 0;
                systs[expNum].one.b = atoi (temp);
                SScount=0;
                partition ++;
            }
        case 3: //begin number search for second line
            if (validInt (str [i])){
                temp[SScount] = str[i];
                SScount ++;
            }
            else if (str[i] == 'x'){
                temp [SScount] = 0;
                systs[expNum].two.a = atoi (temp);
                SScount=0;
                partition ++;
            }
        case 4: //finds operator (neccesary?)
            if (str[i] == '-' || str[i] == '+')
                partition ++;
        case 5: //finds y intercept
            if (validInt (str [i])){
                temp[SScount] = str[i];
                SScount ++;
            }
            if (str[i+1] == 0){
                temp [SScount] = 0;
                systs[expNum].one.b = atoi (temp);
                SScount=0;
                partition ++;
            }

        }
    }
}

////////////////////////////////////////////////////////////////////////////////
/*
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
