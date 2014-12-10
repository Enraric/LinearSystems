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
#define FILE_NAME2 "Output.txt"
#define MAX_SYSTEMS 200
#define MAX_CHARS 50

struct Line {
       int a;
       int b;
       int e;
};

struct System {
       Line one;
       Line two;
       char eqn [MAX_CHARS];
	   float x;
	   float y;
	   char ans[MAX_CHARS];
};

System systs [MAX_SYSTEMS];
int numSysts = 0;

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

    if (systs[i].one.b*systs[i].two.a - systs[i].one.a*systs[i].two.b == 0 && systs[i].two.a*systs[i].one.e - systs[i].one.a*systs[i].two.e == 0){
        printf ("Same line"); //iunno how you file guys store this shit but that's how you check if it's the same line
		sprintf (systs[i].ans,"Same Line.\n");
    }
    else if (systs[i].one.b*systs[i].two.a - systs[i].one.a*systs[i].two.b == 0 && systs[i].two.a*systs[i].one.e - systs[i].one.a*systs[i].two.e == 0){
        printf ("No solutions"); //iunno how you file guys store this shit but that's how you check if it's the same line
		sprintf (systs[i].ans,"No Solutions.\n");
    }
	else{
    lineC = LineMult(systs[i].one, systs[i].two.a);
    lineD = LineMult(systs[i].two, systs[i].one.a);

    systs[i].y = systSolve (lineC, lineD);
    systs[i].x = lineSub (systs[i].y, systs[i].one);
	sprintf (systs[i].ans,"%f,%f\n",systs[i].x,systs[i].y);
	}

}

void mathHandler(){

    for (int i = 0; i < numSysts; i++){
        mathStuff (i);
    }

}

//___________________________________________________________________Begin Parse

bool validInt (char character) {//functions are handy
    return (character >= 48 && character <= 57 || character == '-' || character == '+');
}

int parseCore (char sentinel, int expNum, int i, int* section) {
    int SScount = 0;
    char temp[80] = "";
    //printf ("%c\t%i\t%i\t%i\t%c\n", sentinel,  expNum,  i, *section, systs[expNum].eqn[i]);
    if (validInt (systs[expNum].eqn[i])) {
        temp[SScount] = systs[expNum].eqn[i];
        SScount++;
    }
    else if (systs[expNum].eqn[i] == sentinel) {
        temp [SScount] = 0;
        (*section)++;
        return (atoi (temp));
    }
    return 0; //if invalid, should return this
}

int parse (int expNum){
    printf ("\n\nBegin Parse with passed string of:\t%s\n", systs[expNum].eqn);
    //when calling parse function, you pass it which SYSTEM you want parsed, it does the rest :D
    //returns 1 if the expression is acceptable, 0 if not
    int SScount = 0;
    int section = 0;
    char temp [80] = {""};
    //potential additions: fractions for slope (feel free to add more, guys)
    for (int i = 0; systs[expNum].eqn[i] != 0; i++){
        //printf ("%i\t%c\t%i\n", i, systs[expNum].eqn[i], section);
        switch (section){
        case 0: //adds numbers to a temp string until x
            systs[expNum].one.a = parseCore('x', expNum, i, &section);
            break;
        case 1: //finds y intercept
            systs[expNum].one.b = parseCore('=', expNum, i, &section);
            break;
        case 2://finds answer to equation, ending before the comma
            systs[expNum].one.e = parseCore(',', expNum, i, &section);
            break;
        case 3://start second line
            systs[expNum].two.a = parseCore('x', expNum, i, &section);
            break;
        case 4:
            systs[expNum].two.b = parseCore('=', expNum, i, &section);
            break;
        case 5:
            systs[expNum].two.e = parseCore('\n', expNum, i, &section);
            break;
        }
    }
    return 1;
    printf ("Parse failed\n");
    return 0;
}
//_____________________________________________________________________End Parse

int readFiles (){
	FILE *fp;

	fp = fopen(FILE_NAME,"r");

	if (fp) {

		for (int i = 0;i <= MAX_SYSTEMS;i++){

			if (fgets (systs[i].eqn,MAX_CHARS,fp )){
				while (parse (i)!=1){
					if (fgets (systs[i].eqn,MAX_CHARS,fp ) == "NULL"){
						numSysts = i; // THIS IS IMPORTANT (AND MAY NOT WORK PROPERLY!!!!!)*printf in main for proof
						fclose (fp);
						return i;
					}
				}
			}

			else{
				numSysts = i; // THIS IS IMPORTANT
				fclose (fp);
				return i;
			}
		}

	}
	else{
		numSysts = 0; // THIS IS IMPORTANT
		fclose (fp);
		return 0; // Indicates that opening the file failed...
	}
	return MAX_SYSTEMS;
}

void writeFiles(){
	FILE *fp;

	fp = fopen(FILE_NAME2,"w");

	if (fp){
		for (int i = 0;i<numSysts;i++){
			fputs (systs[i].ans,fp);
		}
		fclose (fp);
	}

}

int main (){
    printf ("Hello, world...\n");
	printf ("%i Valid systems\n",readFiles());

	for (int i = 0; i< numSysts;i++){
			printf ("number 1:\t%i\nnumber 2:\t%i\nanswer is:\t%i\n",systs[i].one.a, systs[i].one.b, systs[i].one.e ); // Test code
			printf ("number 1:\t%i\nnumber 2:\t%i\nanswer is:\t%i\n\n",systs[i].two.a, systs[i].two.b, systs[i].two.e ); // Test code
	}


	mathHandler();
	writeFiles();
    system ("PAUSE");
	return 0;
}
