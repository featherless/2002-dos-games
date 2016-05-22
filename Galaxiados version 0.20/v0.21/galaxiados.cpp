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
*	Galaxiados  v0.21													*
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
*		v0.11(June 15, 2002)											*
*			I finally figured out how to get the asteroids to work with *
*			an array													*
*		v0.12(June 15, 2002)											*
*			I have added the pause feature, I'll make it as a function	*
*			probably later on.											*
*		v0.2(June 15, 2002)												*
*			Finished level two, including a smart AI that shoots at you,*
*			A little more color, *cheat codes, hehe*, a new menu,		*
*			your scores get saved in the program, but only temporary.	*
*				Will add for v0.3:										*
*			storyline! | more details | even more levels | save scores	*
*		v0.21(June 15, 2002)											*
*			I found a bug where, if you die on level two by hitting an	*
*			asteroid, but the aliens had already shot, the shot would	*
*			mysteriously keep going when you restarted.					*
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
void moveast(int y);
void soundeffects(int x);
void collision(int x, int y);
void shoot(int x, int y);
void pause();
int createalien();
void movealien();
void moveshot();
int alienshoot(int x);
void alienshootmove();
void lazercollision();

unsigned int score=1,previouscore=0,highestscore=0,level=1,funcprog=0,level1score=0,level2score=0;
int ast[40] [2],alien[10] [3],ammo=1,alienammo=1,stopmaking=0;
HANDLE hConsoleOutput;
COORD dwCursorPosition;
COORD lazer;
COORD alienlazer;
int main()			//startin' the program
{
	int a,b,c,x,y;
	char galaxiados[11]="Galaxiados";
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	changecolor(12);
		//21 for alien, 15 for asteroid, 30 for ship, 24 for lazer, 16 for ship facing right, 17 facing left
	system("cls");		//This is a good command, clears the screen
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
		moveast(3);		//these two move the asteroids
		moveast(3);		//the 3 makes it change color
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

	change(25,20);
	printf("Press Enter to continue");

	while (a!=13)			//press enter to continue
		a=getch();
	 score=0;
	
while(1)
 {

	for(b=0;b<2;b++)
	{
		for(a=0;a<39;a++)
			ast[a] [b]=0;
	}

	system("cls");			//Clear the screen

	changecolor(14);
	for(b=20;b<50;b++)
	{
		change(b,1);
		printf("%c",205);
		change(b,15);
		printf("%c",205);
		change(b,13);
		printf("%c",205);
	}
	change(19,1);
	printf("%c",201);
	change(50,1);
	printf("%c",187);
	change(19,15);
	printf("%c",200);
	change(50,15);
	printf("%c",188);

	for(b=2;b<15;b++)
	{
		change(19,b);
		printf("%c",186);
		change(50,b);
		printf("%c",186);
	}

	change(19,13);
	printf("%c",204);
	change(50,13);
	printf("%c",185);
	change(27,14);
	printf("By Jeff Verkoeyen");
	change(29,2);
	printf("Galaxiados");
	change(21,4);
	printf("Start");
	change(21,5);
	printf("Quit");
	change(24,8);
	printf("Previous score was %d",previouscore);
	change(26,9);
	printf("High score is %d",highestscore);
	change(24,11);
	printf("Press Space to select");
	change(32,12);
	printf("Level %d",level);
	change(15,0);
	printf("Please press alt-enter to go full screen");
	change(28,4);
	changecolor(15);
	printf("%c",17);
	a=0;
	b=4;
	stopmaking=0;
	while(a!=32)
	{

		a=getch();

		change(28,b);
		printf(" ");

		if(a==72 && b==5)
			b=4;

		if(a==80 && b==4)
			b=5;
		
		if(a==60){
			c=getch();
			
			if(c==49)
				level=1;
			if(c==50)
				level=2;

			change(32,12);
			printf("Level %d",level);
		}

		change(28,b);
		printf("%c",17);

	}

	system("cls");

	if(b==5)
		return 0;
a=12345;
	if(b==4 && level==1)
	{
		score=1;
		change(0,0);
		printf("Level one\nUse arrow keys to move your ship, enter pauses\n\nLaunch in \n");
		soundeffects(5);
		printf("3\n");
		soundeffects(5);
		printf("2\n");
		soundeffects(5);
		printf("1\n");
		soundeffects(5);
		printf("GO!");
		soundeffects(1);
		system("cls");
		change(20,20);			//setting up the game
		x=40;				//starting x-coord for the ship
		y=20;
		c=0;
		unsigned int e,f,g;

		while (1)				//starting the game (FINALLY!!)
		{

			if(score>=65){
				system("cls");
				change(0,0);
				printf("Congratulations commander, you made it past the\nfirst level, now on to level two!");
				soundeffects(5);
				soundeffects(5);
				a=0;
				while (a!=13)
					a=getch();
				level1score=score;				
				level=2;
				break;
			}
			a=kbhit();				//tests to see if you pressed a button

			if (e==60 || e==300)
				createast(80,3);		//this creates an asteroid about every .0001 seconds

			e++;					//increments the counter for the asteroids

			if (e==70 || e==13)		//this moves the asteroids every millisecond (about)
				moveast(3);

			f++;					//increments the score counter

			if (f>9000)			//the score counter resets here
				f=0;

			if (f==100)
				score=score+rand()%10;	//this adds the score up, randomly, that way you'll never have the same score


			if (e>400)				//I had to have a pause in here, or it would
				e=0;				//go WAY too fast, try lowering it from 400 to about 100, and you'll see, haha

			change(x,y);
			changecolor(15);		//makes the ship white, but nothing else
			printf("%c",30);
			changecolor(3);			//here it switches back to normal color

			for(g=0;g<40;g++)
			{
				if(ast[g] [1]==x && ast[g] [2]==y)
				{						//this is my collision detection sequence, not that hard to figure out...
					collision(x,y);		//just if the ship's coordinates equal that of any of the asteroids,
					break;				//you die, break
				}
			}
			
			if(ast[g] [1]==x && ast[g] [2]==y)
				break;
			
			if (a==1)			//this is where it goes if you pressed any keys
			{
				a=getch();		//i had to do this so the loop would constantly go,
				
				if (a==13)
				{
					pause();
					a=funcprog;
					if(a==12345)
						break;
					system("cls");
				}

				if (a==27)
				{
					a=12345;
					break;
				}

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

	}


	if(b==4 && level==2)
	{
		score=level1score;
		change(0,0);
		printf("Level two\nUse arrow keys to move your ship, enter pauses, spacebar shoots\n\nLaunch in \n");
		soundeffects(5);
		printf("3\n");
		soundeffects(5);
		printf("2\n");
		soundeffects(5);
		printf("1\n");
		soundeffects(5);
		printf("GO!");
		soundeffects(1);
		system("cls");
		change(20,20);
		x=40;				//starting x-coord for the ship
		y=20;
		c=0;
		unsigned int e,f,g,h;

		while (1)
		{
			h++;

			if (lazer.X!=0 && lazer.X==alienlazer.X && lazer.Y== alienlazer.Y)
				lazercollision();

			if(h>300)
				h=0;

			if(ammo==0 && h==200)
				moveshot();

			alienshoot(x);

			if(alienammo==0 && h==100)
				alienshootmove();

			if(score>=120){
				system("cls");
				change(0,0);
				printf("Congratulations commander, you made it past the\nsecond level, now on to level three!");
				soundeffects(5);
				soundeffects(5);
				a=0;
				while (a!=13)
					a=getch();
				level2score=score;
				level=3;
				break;
			}
			a=kbhit();				//tests to see if you pressed a button

			if (e==60 || e==300)
				createast(80,14);		//this creates an asteroid about every .0001 seconds

			e++;					//increments the counter for the asteroids

			if (e==70 || e==13)		//this moves the asteroids every millisecond (about)
				moveast(14);

			if (e==200)
				createalien();

			if (e==173)
				movealien();

			if (alienlazer.X==x && alienlazer.Y==y)
			{
				collision(x,y);
				break;
			}

			for(g=0;g<10;g++)
			{
				if (alien[g] [1]!=0 && alien[g] [2]!=0)
				{
					if (alien[g] [1]==lazer.X && alien[g] [2]==lazer.Y)
					{
						alien[g] [1]=0;
						alien[g] [2]=0;
						alien[g] [3]=1;
						score=score+rand()%20;
						soundeffects(1);
					}
				}
			}

			f++;					//increments the score counter

			if (f>9000)			//the score counter resets here
				f=0;

			if (f==100)
				score=score+rand()%8;	//this adds the score up, randomly, that way you'll never have the same score

			if (e>400)				//I had to have a pause in here, or it would
				e=0;				//go WAY too fast, try lowering it from 400 to about 100, and you'll see, haha

			change(x,y);
			changecolor(15);		//makes the ship white, but nothing else
			printf("%c",30);
			changecolor(3);			//here it switches back to normal color

			for(g=0;g<40;g++)
			{
				if(ast[g] [1]==x && ast[g] [2]==y)
				{						//this is my collision detection sequence, not that hard to figure out...
					collision(x,y);		//just if the ship's coordinates equal that of any of the asteroids,
					break;				//you die, break
				}
			}
			
			if(ast[g] [1]==x && ast[g] [2]==y)
				break;
			
			if (a==1)			//this is where it goes if you pressed any keys
			{
				a=getch();		//i had to do this so the loop would constantly go,
				
				if (a==13)
				{
					pause();
					a=funcprog;
					if(a==12345)
						break;
					system("cls");
				}

				if (a==32)
				{
					if(ammo==1)
						shoot(x,y);
				}

				if (a==27)
				{
					a=12345;
					break;
				}

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

	}


	if (a!=12345)
	{
		system("cls");		//this is where you go if you die
		change(0,0);
		printf("You're dead\n");
		printf("Your score was %d",score);
		previouscore=score;

		if(score>highestscore)
		{
			change(0,2);
			printf("New high!");
			highestscore=score;
		}
		
		while(a!=13){
			a=getch();		//press enter to continue...
		}

	}
		lazer.X=lazer.Y=alienlazer.X=alienlazer.Y=0;
		alienammo=ammo=1;
	system("cls");	//clears the screen, and
 }
}

void lazercollision()
{
	if (lazer.X!=0 && lazer.X==alienlazer.X && lazer.Y== alienlazer.Y)
	{
		ammo=alienammo=1;
		change(lazer.X,lazer.Y);
		printf(" ");
		lazer.X=alienlazer.X=lazer.Y=alienlazer.Y=0;
	}

}

int alienshoot(int x)
{
	int a,y;
	for(a=0;a<10;a++)
	{
		if(alien[a] [1]==x && alienammo==1)
		{
			alienammo=0;
			x=alienlazer.X=alien[a] [1];
			y=alienlazer.Y=alien[a] [2];
			change(x,y+1);
			changecolor(12);
			printf("%c",25);
			return 0;
		}
	}
	return 0;
}
void shoot(int x, int y)
{
	if(ammo==1)
	{
		ammo=0;
		lazer.X=x;
		lazer.Y=y;
		change(x,y-1);
		changecolor(12);
		printf("%c",24);
	}

}

void alienshootmove()
{
int x,y;
	if(alienammo==0)
	{
		x=alienlazer.X;
		y=alienlazer.Y;
		change(x,y);
		printf(" ");
		y++;
		change(x,y);
		changecolor(12);
		printf("%c",25);
		alienlazer.X=x;
		alienlazer.Y=y;
		if(y>20)
		{
			alienammo=1;
			change(x,y);
			printf(" ");
		}
	}

}

void moveshot()
{
int x,y;

	if(ammo==0)
	{
		x=lazer.X;
		y=lazer.Y;
		change(x,y);
		printf(" ");
		y--;
		change(x,y);
		changecolor(12);
		printf("%c",24);
		lazer.X=x;
		lazer.Y=y;
		if(y<3)
		{
			ammo=1;
			change(x,y);
			printf(" ");
		}
	}

}

void collision(int x, int y)	//this is what happens when you hit an asteroid,
{								//it draws out the explosion, taking the
	int a,b;					//coordinate from above, and drawing it from there,
								//so it looks like the ship exploded
	changecolor(12);
	
	change(x,y);
	printf("*");

	for(a=x;a<x+5;a++)
	{
		change(a,y);
		printf("*");
		change(a-5,y);
		printf("*");
	}

	for(a=y+5;a>y-5;a--)
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

	b=y;

	for(a=x;a<x+8;a=a+2)
	{
		b++;
		change(a,b);
		printf("*");
		change(x+x-a,b);
		printf("*");
	}

	for(a=0;a<2;a++)
		soundeffects(5);

	Sleep(1000);
}

void pause()
{
	int b,a;
	changecolor(15);
	for(b=6;b<12;b++)
	{
		for(a=25;a<52;a++)
		{
			change(a,b);
			printf(" ");
		}
	}
	for(a=25;a<52;a++)
	{
		change(a,5);
		printf("*");
		change(a,12);
		printf("*");
	}
	for(a=6;a<12;a++)
	{
		change(25,a);
		printf("*");
		change(51,a);
		printf("*");
	}
	change(35,6);
	printf("Paused");
	change(27,8);
	printf("Press Enter to continue");
	change(32,9);
	printf("Escape to quit");
	change(32,11);
	printf("Score is %d",score);
	a=0;
	while (a!=13)
	{
		a=getch();
		if(a==27)
		{
			a=12345;
			break;
		}
	}
	funcprog=a;

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
			moveast(1);
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

int createalien()
{
	COORD temp;
	temp=dwCursorPosition;

	changecolor(15);
	int a;
	for(a=0;a<10;a++)
	{
		if (a==9)
			stopmaking=1;
		if(alien[a] [1]==0 && stopmaking==0)
		{
			alien[a] [1]=rand()%67;
			alien[a] [2]=3;
			change(alien[a] [1],3);
			printf("%c",21);
			dwCursorPosition=temp;
			return 0;
		}

	}
	dwCursorPosition=temp;
	return 0;

}

int createast(int b, int c){	//creates an asteroid
	COORD temp;
	temp=dwCursorPosition;

	changecolor(c);				//int y is what the color of the
	int a;						//asteroid is going to be
	for(a=0;a<40;a++){			//and int x is the random number

		if(ast[a] [1]==0)
		{
			ast[a] [1]=rand()%b;
			change(ast[a] [1],0);
			printf("%c",15);
			dwCursorPosition=temp;
			return 0;
		}

	}
	/*******************************************\
	*You can have up to as many asteroids on the*
	*screen as you want.						*
	\*******************************************/
	dwCursorPosition=temp;
	return 0;
}

void movealien()
{
	COORD temp;
	temp=dwCursorPosition;
	changecolor(15);
int a,c,d;
	for(a=0;a<10;a++)
	{
		if(alien[a] [1]!=0)
		{
			c=alien[a] [1];
			d=alien[a] [2];
			change(c,d);
			printf(" ");
			if (alien[a] [3]==0)
				alien[a] [1]--;
			else
				alien[a] [1]++;
			if (alien[a] [1]<=4 && alien[a] [3]==0)
				alien[a] [3]=1;
			if (alien[a] [1]>=70 && alien[a] [3]==1)
				alien[a] [3]=0;
			c=alien[a] [1];
			d=alien[a] [2];
			change(c,d);
			printf("%c",21);
		}
	}
	changecolor(12);
	dwCursorPosition=temp;
}

void moveast(int b)		//b is the color of the asteroid
{
	COORD temp;
	temp=dwCursorPosition;
	changecolor(b);
int a,c,d;
	for(a=0;a<40;a++)
	{
		if(ast[a] [1]!=0)
		{
			c=ast[a] [1];
			d=ast[a] [2];
			change(c,d);
			printf(" ");
			ast[a] [2]++;
			d=ast[a] [2];
			change(c,d);
			printf("%c",15);

			if(d>20)
			{
				change(c,d);
				printf(" ");
				ast[a] [1]=0;
				ast[a] [2]=0;
			}

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
