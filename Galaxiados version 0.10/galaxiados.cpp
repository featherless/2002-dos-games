/*
 Copyright 2002, 2016 Jeff Verkoeyen. All Rights Reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

 http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

/***********************************************************************\
*	Galaxiados  v1.0													*
*																		*
*	Created By:  Jeff Verkoeyen											*
*																		*
*	All Rights Reserved													*
*																		*
*	Release Dates-														*
*		v0.1(June 14, 2002):											*
*			Includes the first level, ability to move up, down, left	*
*			and right.													*
*				Will add for v0.2:										*
*			lives | instructions | more sound effects | more levels		*
*																		*
* ragingflame.150m.com/  <<You can find all updates/versions here		*
\***********************************************************************/



#include <stdio.h>				//ahh, the lovely header files
#include <conio.h>
#include <windows.h>

void change(int x, int y);		//wow, there's a lot of functions
void changecolor(int x);
void introshoot(int x);
int createast(int x, int y);
void moveast(int x, int y);
void soundeffects(int x);
void collision(int x, int y);

int ast1=0,ast2=0,ast3=0,ast4=0,ast5=0,ast6=0,ast7=0,ast8=0,ast9=0,ast10=0; //and variables
int loc1=0,loc2=0,loc3=0,loc4=0,loc5=0,loc6=0,loc7=0,loc8=0,loc9=0,loc10=0; //too
	/********************************************************\
	*All of the above int variables are used for the         *
	*asteroids in the game, I'll add move as they're needed. *
	*so far there are going to be at least 10 in the game    *
	\********************************************************/
unsigned int score=0;
HANDLE hConsoleOutput;
COORD dwCursorPosition;
int main()			//startin' the program
{
	int a,b,c,x,y;
	char galaxiados[11]="Galaxiados";

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	changecolor(12);
		//15 for asteroid, 30 for ship, 24 for lazer, 16 for ship facing right
	system("cls");		//This is a good command, clears the screen
	Beep(654,2000);		//These beeps rock!  Beep([frequency],[length])
	a=-1;

	for(b=30;b<40;b++)
	{
		createast(60,3);	//creates some asteroids
		changecolor(12);
		a++;				//gotta have this so that the galaxiados string works
		change(b-1,10);
		printf(" ");
		change(b,10);
		changecolor(15);
		printf("%c",30);	//displays the ship, %c means a character
		changecolor(12);
		introshoot(b);		//shows the shooting animation
		change(b,1);
		printf("%c",galaxiados[a]);
		moveast(1,3);		//these two move the asteroids
		moveast(1,3);		//#2 the #3 makes it change color
	}

	for(b=39;b>27;b--)
	{
		change(b+1,10);
		printf(" ");
		change(b,10);
		changecolor(15);
		printf("%c",30);
		Sleep(20);
	}

	changecolor(14);

	for(a=0;a<27;a++)
	{
		change(a-1,3);
		printf(" ");
		change(70-a,3);
		printf(" ");
		change(a,3);
		printf("By: Jeff");		//this displays my name and makes it
		change(61-a,3);			//fly into the screen from both sides
		printf("Verkoeyen");
		Sleep(20);				//gotta pause here, or it goes too fast
	}

	printf("\n");

	while (a!=13)			//press enter to continue
		a=getch();

	system("cls");			//Clear the screen
	change(20,20);			//setting up the game
	x=y=20;					//starting x-coord for the ship
	c=0;
	unsigned int d,e,f;

	while (1)				//starting the game (FINALLY!!)
	{
		a=kbhit();				//tests to see if you pressed a button

		if (e==60)
			createast(80,3);		//this creates an asteroid about every .0001 seconds

		e++;					//increments the counter for the asteroids

		if (e==70 || e==13)		//this moves the asteroids every millisecond (about)
			moveast(1,3);

		f++;					//increments the score counter

		if (f>9000)			//the score counter resets here
			f=0;

		if (f==100)
			score=score+rand()%10;	//this adds the score up, randomly, that way you'll never have the same score

		if (e>300)				//I had to have a pause in here, or it would
			e=0;					//go WAY too fast, try lowering it from 400 to about 100, and you'll see, haha

		change(x,y);
		changecolor(15);		//makes the ship white, but nothing else
		printf("%c",30);
		changecolor(3);			//here it switches back to normal color

		if(loc1==y && ast1==x || loc2==y && ast2==x || loc3==y && ast3==x || loc4==y && ast4==x || loc5==y && ast5==x || loc6==y && ast6==x || loc7==y && ast7==x || loc8==y && ast8==x || loc9==y && ast9==x || loc10==y && ast10==x)
		{		//this is my collision detection sequence, not that hard to figure out...
			collision(x,y);	//just if the ship's coordinates equal that of any of the asteroids,
			break;		//you die, and go to the label
		}

		if (a==1)			//this is where it goes if you pressed any keys
		{
			a=getch();		//i had to do this so the loop would constantly go,

			if (a==224)	//even if you didn't press anything
			{
				b=getch();

					change(x,y);
					printf("  ");

				if (b==75 && x>1)	//move left
					x--;

				if (b==77 && x<70)	//move right
					x++;

				if (b==72 && y>15)  //move up
					y--;

				if (b==80 && y<20)  //move down
					y++;

					change(x,y);
					printf("%c",30);
			}

		}

	}

	system("cls");		//this is where you go if you die
	change(0,0);
	printf("You're dead, play again another time!\n");
	printf("Your score was %d",score);

	while(a!=13){
		a=getch();		//press enter to continue...
	}

	system("cls");	//clears the screen, and
	return 0;		//quits
}

void collision(int x, int y)	//this is what happens when you hit an asteroid,
{								//it draws out the explosion, taking the
	int a,b,c;					//coordinate from above, and drawing it from there,
								//so it looks like the ship exploded
	change(x,y);
	printf("*");

	for(a=x;a<x+5;a++)
	{
		change(a,y);
		printf("*");
		change(a-5,y);
		printf("*");
	}

	for(a=y;a>y-5;a--)
	{
		change(x,a);
		printf("*");
	}

	b=y;

	for(a=x;a<x+8;a=a+2)
	{
		b--;
		change(a,b);
		printf("*");
		change(x+x-a,b);
		printf("*");
	}

	for(a=0;a<2;a++)
		soundeffects(5);

	Sleep(1000);
}

void introshoot(int x)		//x is where the shot will display
{
	int a;
	int b;

	for (a=9;a>1;a--){
		b++;
		change(x,a);
		printf("%c",24);
		Sleep(10);
		change(x,a);
		printf(" ");

		if(b==2 || b==4)
			moveast(1,1);
	}

	soundeffects(2);		//runs the sound effect for shooting
}

void change(int x, int y)		//This just changes the
{								//current position of the cursor
	dwCursorPosition.X = x;		//on the screen, allowing placement
	dwCursorPosition.Y = y;		//down to the point
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition); 
}

void changecolor(int x)	//changes color to whatever x equals
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
}

int createast(int x, int y){	//creates an asteroid
	changecolor(y);				//int y is what the color of the
								//asteroid is going to be
	if(ast1==0)					//and int x is the random number
	{
		ast1=rand()%x;
		change(ast1,0);
		printf("%c",15);
		return 0;
	}

	if(ast2==0)
	{
		ast2=rand()%x;
		change(ast2,0);
		printf("%c",15);
		return 0;
	}
	
	if(ast3==0)
	{
		ast3=rand()%x;
		change(ast3,0);
		printf("%c",15);
		return 0;
	}
	if(ast4==0)
	{
		ast4=rand()%x;
		change(ast4,0);
		printf("%c",15);
		return 0;
	}
	if(ast5==0)
	{
		ast5=rand()%x;
		change(ast5,0);
		printf("%c",15);
		return 0;
	}
	if(ast6==0)
	{
		ast6=rand()%x;
		change(ast6,0);
		printf("%c",15);
		return 0;
	}
	if(ast7==0)
	{
		ast7=rand()%x;
		change(ast7,0);
		printf("%c",15);
		return 0;
	}
	if(ast8==0)
	{
		ast8=rand()%x;
		change(ast8,0);
		printf("%c",15);
		return 0;
	}
	if(ast9==0)
	{
		ast9=rand()%x;
		change(ast9,0);
		printf("%c",15);
		return 0;
	}
	if(ast10==0)
	{
		ast10=rand()%x;
		change(ast10,0);
		printf("%c",15);
		return 0;
	}

	/*******************************************\
	*You can have up to ten asteroids on the    *
	*screen at a time.							*
	\*******************************************/
	return 0;
}

void moveast(int x, int y)		//y is the color of the asteroid
{								//x does nothing
	COORD temp;
	temp=dwCursorPosition;
	changecolor(y);

	if(ast1!=0)
	{
		change(ast1,loc1);
		printf(" ");
		loc1++;
		change(ast1,loc1);
		printf("%c",15);

		if(loc1>20)
		{
			change(ast1,loc1);
			printf(" ");
			ast1=0;
			loc1=0;
		}

	}

	if(ast2!=0)
	{
		change(ast2,loc2);
		printf(" ");
		loc2++;
		change(ast2,loc2);
		printf("%c",15);

		if(loc2>20)
		{
			change(ast2,loc2);
			printf(" ");
			ast2=0;
			loc2=0;
		}

	}
	if(ast3!=0)
	{
		change(ast3,loc3);
		printf(" ");
		loc3++;
		change(ast3,loc3);
		printf("%c",15);

		if(loc3>20)
		{
			change(ast3,loc3);
			printf(" ");
			ast3=0;
			loc3=0;
		}

	}
	if(ast4!=0)
	{
		change(ast4,loc4);
		printf(" ");
		loc4++;
		change(ast4,loc4);
		printf("%c",15);

		if(loc4>20)
		{
			change(ast4,loc4);
			printf(" ");
			ast4=0;
			loc4=0;
		}

	}

	if(ast5!=0)
	{
		change(ast5,loc5);
		printf(" ");
		loc5++;
		change(ast5,loc5);
		printf("%c",15);

		if(loc5>20)
		{
			change(ast5,loc5);
			printf(" ");
			ast5=0;
			loc5=0;
		}

	}

	if(ast6!=0)
	{
		change(ast6,loc6);
		printf(" ");
		loc6++;
		change(ast6,loc6);
		printf("%c",15);

		if(loc6>20)
		{
			change(ast6,loc6);
			printf(" ");
			ast6=0;
			loc6=0;
		}

	}

	if(ast7!=0)
	{
		change(ast7,loc7);
		printf(" ");
		loc7++;
		change(ast7,loc7);
		printf("%c",15);

		if(loc7>20)
		{
			change(ast7,loc7);
			printf(" ");
			ast7=0;
			loc7=0;
		}

	}

	if(ast8!=0)
	{
		change(ast8,loc8);
		printf(" ");
		loc8++;
		change(ast8,loc8);
		printf("%c",15);

		if(loc8>20)
		{
			change(ast8,loc8);
			printf(" ");
			ast8=0;
			loc8=0;
		}

	}

	if(ast9!=0)
	{
		change(ast9,loc9);
		printf(" ");
		loc9++;
		change(ast9,loc9);
		printf("%c",15);

		if(loc9>20)
		{
			change(ast9,loc9);
			printf(" ");
			ast9=0;
			loc9=0;
		}

	}

	if(ast10!=0)
	{
		change(ast10,loc10);
		printf(" ");
		loc10++;
		change(ast10,loc10);
		printf("%c",15);

		if(loc10>20)
		{
			change(ast10,loc10);
			printf(" ");
			ast10=0;
			loc10=0;
		}

	}

	changecolor(12);
	dwCursorPosition=temp;
}

void soundeffects(int x)			//x tells which sound to play
{

	if (x==1)
	{
		for(x=40;x<600;x=x+60)		//warp sound
		Beep(x,20);
	}

	if (x==2)
	{
		for(x=600;x>50;x=x-60)		//Shooting sound
		Beep(x,20);
	}

	if (x==3)
	{
	for(x=50;x<1000;x=x*2)			//Got an Item sound
		Beep(x,20);
	}

	if (x==4)
	{
	for(x=70;x>30;x--)				//Explosion
		Beep(x,1);
	}

	if (x==5)
	{
	for(x=700;x>640;x--)			//WARNING!
		Beep(x,1);
	for(x=640;x<700;x++)
		Beep(x,1);
	}

}