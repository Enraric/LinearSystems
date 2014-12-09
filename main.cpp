// Alex's job: Math Things
// Harry's job: parsing
// Wilson's job: File stuff + misc...

#include "stdafx.h" // Comment this out if this appears in your stuff, it's for my weird compiler thing -Wilson
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"
#include "iostream"

#define FILE_NAME "Test.txt" // Change this if you want to change the file name.
#define MAX_SYSTEMS 200
#define MAX_CHARS 50

struct Line {
       int a;
       int b;
       int e;
	   char eqn [MAX_CHARS]; // This is somewhere to stick the whole string before it gets parsed. Also useful to actually display it later and stuff. -Wilson
};

struct System {
       Line one;
       Line two;
};

System systs [MAX_SYSTEMS];
int numSysts = 0; // I'm not sure if this should be global, it seems like this could mess stuff up real bad -Wilson

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

    if (systs[i].one.b*systs[i].two.a - systs[i].one.a*systs[i].two.b == 0 && systs[i].two.a*systs[i].one.e - systs[i].one.a*systs[i].two.e == 0){
        printf ("Same line"); //iunno how you file guys store this shit but that's how you check if it's the same line
    }
    else if (systs[i].one.b*systs[i].two.a - systs[i].one.a*systs[i].two.b == 0 && systs[i].two.a*systs[i].one.e - systs[i].one.a*systs[i].two.e == 0){
        printf ("No solutions"); //iunno how you file guys store this shit but that's how you check if it's the same line
    }

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

int parse (char str[80], int expNum){//when calling parse function, you can pass it systs[expNum].one.eqn
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

	return 1; // I have to put this here to get it to compile wat -Wilson
}
//_____________________________________________________________________End Parse

int readFiles (){
	FILE *fp;

	fp = fopen(FILE_NAME,"r");

	if (fp) {

		for (int i = 0;i<=MAX_SYSTEMS;i++){
			
			if (fgets (systs[i].one.eqn,MAX_CHARS,fp) && fgets (systs[i].two.eqn,MAX_CHARS,fp) ){
				//fgets (systs[i].one.eqn,MAX_CHARS,fp);
				//fgets (systs[i].two.eqn,MAX_CHARS,fp);

				if (systs[i].one.eqn[0] == '\n' ){
				printf ("Some whitespace found\n");
				while (fgets (systs[i].one.eqn,MAX_CHARS,fp) && systs[i].one.eqn[0] == '\n' ){
				}
			}

			else if (systs[i].two.eqn[0] == '\n' ) {
				printf ("Some whitespace found\n");
				while (fgets (systs[i].two.eqn,MAX_CHARS,fp)&& systs[i].two.eqn[0] == '\n'){
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

	for (int i = 0; i<= numSysts;i++){
			printf ("%s",systs[i].one.eqn); // Test code
			printf ("%s",systs[i].two.eqn);
	}
    printf ("Equations strings after being read: %s\t%s\n",systs[0].one.eqn, systs[0].two.eqn);
	parse (systs[0].one.eqn, 0);
	parse (systs[0].two.eqn, 0);
	printf ("Equations after being parsed: %i\t%i\n%i\t%i\n",systs[0].one.a, systs[0].one.b, systs[0].two.a, systs[0].two.b);
    system ("PAUSE");
	return 0;
}
