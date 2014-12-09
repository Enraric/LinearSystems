// Alex's job: Math Things
// Harry's job: parsing
// Wilson's job: File stuff + misc...

//#include "stdafx.h" // Comment this out if this appears in your stuff, it's for my weird compiler thing -Wilson
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "iostream"

#define FILE_NAME "Test.txt" // Change this if you want to change the file name.
#define MAX_SYSTEMS 200
#define MAX_CHARS 50

struct Line { // this is bad
       int a;
       int b;
       int e;
};

struct System { // this is also bad
       Line one;
       Line two;
       char eqn [MAX_CHARS];
};

System systs [MAX_SYSTEMS]; // cysts FTFY
int numSysts = 0; // I'm not sure if this should be global, it seems like this could mess stuff up real bad -Wilson
//why for the love of god is this global, and the naming too syst > systs

//Alex's Mathemagical Mathland of Math//////////////////////////////////////////////////////////////////////////////

Line LineMult (Line A, int B){ //screw naming convention
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

    if (systs[i].one.b*systs[i].two.a - systs[i].one.a*systs[i].two.b == 0 && systs[i].two.a*systs[i].one.e - systs[i].one.a*systs[i].two.e == 0){
        printf ("Same line"); //iunno how you file guys store this shit but that's how you check if it's the same line
    }
    else if (systs[i].one.b*systs[i].two.a - systs[i].one.a*systs[i].two.b == 0 && systs[i].two.a*systs[i].one.e - systs[i].one.a*systs[i].two.e == 0){
        printf ("No solutions"); //iunno how you file guys store this shit but that's how you check if it's the same line
    }

    lineC = LineMult(systs[i].one, systs[i].two.a);
    lineD = LineMult(systs[i].two, systs[i].one.a);

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
    return (character >= 48 && character <= 57 || character == '-' || character == '+');
}

int parse (int expNum){
    printf ("\n\nBegin Parse with passed string of:\t%s\n", systs[expNum].eqn);
    //when calling parse function, you pass it which SYSTEM you want parsed
    //Parse returns:
    //  0 for success
    //  1 for fail (should print error message including which failed)
    int SScount = 0;
    int section = 0;
    char temp [80] = {""};
    //potential additions: fractions for slope (feel free to add more, guys)
    for (int i = 0; systs[expNum].eqn[i] != 0; i++){
        printf ("%i\t%c\t%i\n", i, systs[expNum].eqn[i], section);
        //NEED TO TURN THESE CASES INTO FUNCTIONS
        switch (section){
        case 0: //adds numbers to a temp string until x
            if (validInt (systs[expNum].eqn[i])){
                temp[SScount] = systs[expNum].eqn[i];
                SScount ++;
            }
            else if (systs[expNum].eqn[i] == 'x'){
                temp [SScount] = 0;
                systs[expNum].one.a = atoi (temp);
                SScount=0;
                section ++;
            }
            break;
        case 1: //finds y intercept
            if (validInt (systs[expNum].eqn[i])){
                temp[SScount] = systs[expNum].eqn[i];
                SScount ++;
            }
            else if (systs[expNum].eqn[i] == '='){
                systs[expNum].one.b = atoi (temp);
                SScount=0;
                section ++;
            }
            break;
        case 2:
            if (validInt (systs[expNum].eqn[i])){
                temp[SScount] = systs[expNum].eqn[i];
                SScount ++;
            }
            else if (systs[expNum].eqn[i] == ','){
                systs[expNum].one.e = atoi (temp);
                SScount=0;
                section ++;
            }
        case 3:
            if (validInt (systs[expNum].eqn[i])){
                temp[SScount] = systs[expNum].eqn[i];
                SScount ++;
            }
            else if (systs[expNum].eqn[i] == 'x'){
                systs[expNum].two.a = atoi (temp);
                SScount=0;
                section ++;
            }
        case 4:
            if (validInt (systs[expNum].eqn[i])){
                temp[SScount] = systs[expNum].eqn[i];
                SScount ++;
            }
            else if (systs[expNum].eqn[i] == '='){
                systs[expNum].two.b = atoi (temp);
                SScount=0;
                section ++;
            }
        case 5:
            if (validInt (systs[expNum].eqn[i])){
                temp[SScount] = systs[expNum].eqn[i];
                SScount ++;
            }
            else if (systs[expNum].eqn[i] == '\n'){
                systs[expNum].two.e = atoi (temp);
                SScount=0;
                section ++;
                printf ("parse succeeded");
                return 1;
            }
        }
    }
    printf ("Parse failed\n");
	return 0;
}
//_____________________________________________________________________End Parse

int readFiles (){
	FILE *fp;

	fp = fopen(FILE_NAME,"r");

	if (fp) {

		for (int i = 0;i<=MAX_SYSTEMS;i++){

			if (fgets (systs[i].eqn,MAX_CHARS,fp )){
				while (parse (i)!=0){
					if (fgets (systs[i].eqn,MAX_CHARS,fp ) == "NULL"){
						numSysts = i; // THIS IS IMPORTANT
						return i;
					}
				}
			}

			else{
				numSysts = i; // THIS IS IMPORTANT
				return i;
			}
		}

	}
	else{
		numSysts = 0; // THIS IS IMPORTANT
		return 0; // Indicates that opening the file failed...
	}
	return MAX_SYSTEMS;
}

int main (){
    printf ("Hello, world...\n");
	printf ("%i Valid systems\n",readFiles());

	printf ("Printing all read in things.\n");

	for (int i = 0; i< numSysts;i++){
			printf ("%s",systs[i].eqn); // Test code
	}
	/*
    printf ("Equation string after being read: %s\n",systs[expNum].eqn[i]);
	parse (systs[2].one.eqn, 0);
	printf ("Equation after being parsed: %i\t%i\n",systs[2].one.a, systs[2].one.b);
	*/
    system ("PAUSE");
	return 0;
}
