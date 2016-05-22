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

/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*\
*																	   *
-	Roidian v0.11													   -
-																	   -
-	Created By:  Jeff Verkoeyen										   -
-																	   -
-	All Rights Reserved												   -
-																	   -
-	Release Dates-													   -
-		v0.1(June 18, 2002)											   -
-			Includes two levels in Arcade mode, along with a level	   -
-			editor.  Use arrow keys to move and jump, etc.			   -
-				Will add for v0.2:									   -
-			save feature with levels | more levels					   -
-		v0.11(June 18, 2002)										   -
-			Created another level for Arcade mode.					   -
-																	   -
-	ragingflame.150m.com/  <<You can find all updates/versions here	   -
*																	   *
\*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <iostream.h>

void change(int x, int y);
void changecolor(int x);
void convert(char line1[31], int b);
void draw(int x);
int detect(int a, int b);
void detectchest();
int create();

int platform[50] [21];
int custom[50] [21];
int customscore=0;
int score=0;

HANDLE hConsoleOutput;
COORD dwCursorPosition;
COORD mainchar;
COORD customstart;
int main()
{
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int a=0,b;

	while(1)
	{
		
		a = 0;
		
		system("cls");
		
		change(30,0);
		changecolor(15);
		printf("Welcome to Roidian!");
		change(20,1);
		printf("Press 1 to play normal arcade mode");
		change(20,2);
		printf("Press 2 to create your own level");
		change(20,3);
		printf("Press 3 to play the level you've created");
		change(30,4);
		printf("Press Escape to quit");
		change(10,6);
		printf("Left and Right arrow keys move left and right");
		change(10,7);
		printf("Up arrow jumps, and spacebar picks up items");
		change(30,9);
		printf("By Jeff Verkoeyen");
		change(20,10);
		printf("Please press alt-enter to go full screen");
		
		while(a!=49 && a!=50 && a!=51 && a!=27)
			a = getch();
		
		system("cls");
		
		if(a==27)
			return 0;

		if(a==50)
			create();
		
		if(a==51)
		{

			draw(2);
			
			for(b=0;b<21;b++)
			{
				
				for(a=0;a<50;a++)
				{
					
					if(custom[a] [b]==3)
						customscore++;

					platform[a] [b] = custom[a] [b];
					
				}
				
			}

			mainchar = customstart;

			score = 0;

			while(score<customscore)
			{
				
				change(60,0);
				printf("Your score is %d",score);
				
				a = kbhit();
				
				if (a==1)
				{
					
					a = getch();
					
					if (a==27)
						break;

					if (a==224)
					{
						
						b = getch();
						
					}
					
					if (a==32)
						detectchest();
					
				}
				
				detect(a,b);
				
				change(mainchar.X, mainchar.Y);
				printf("%c",21);
				
				
			}

			if(customscore==0)
			{

				change(0,0);
				printf("There are no points on the level, please create a new one");
				a = 0;
				while(a!=13)
					a = getch();

			}

		}

		if(a==49)
		{

			convert("|------------------------------------------------|", 1);
			convert("|                                |               |", 2);
			convert("|                                |     3         |", 3);
			convert("|                               3|    ---        |", 4);
			convert("|----------           -----------|               |", 5);
			convert("|                     |                       3  |", 6);
			convert("|           ----------|              ------------|", 7);
			convert("|          |                        -            |", 8);
			convert("|                                  -             |", 9);
			convert("|                            ---  -              |", 10);	
			convert("|                                                |", 11);
			convert("|                                                |", 12);
			convert("|               3            3|                  |", 13);
			convert("|               --          ----     3           |", 14);
			convert("|                                   --           |", 15);
			convert("|       |                                        |", 16);
			convert("|       |                                        |", 17);
			convert("|       |         3        |                     |", 18);
			convert("|       |        333      ---                    |", 19);
			convert("|------------------------------------------------|", 20);
			
			/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*\
			*																	 *
			- You can create your own levels very easily using a subroutine i've -
			- created.  There is very little syntax to execute the subroutine-   -
			- convert("|                               3|    ---        |", 4)   -
			- the long line of symbols is what the convert routine uses to       -
			- convert them into numbers and then draw them on the screen         -
			- 3=  [chest]														 -
			- Then you run the draw routine to make it put the array on the		 -
			- screen.															 -
			*																	 *
			\*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
			
			draw(1);
			
			mainchar.X=3;
			mainchar.Y=3;
			
			//	^^ These are your starting coordinates on the screen
			
			while(score<10)
			{
				
				change(60,0);
				printf("Your score is %d",score);
				
				a = kbhit();
				
				if (a==1)
				{
					
					a = getch();

					if (a==27)
						break;

					if (a==224)
					{
						
						b = getch();
						
					}
					
					if (a==32)
						detectchest();
					
				}
				
				detect(a,b);
				
				change(mainchar.X, mainchar.Y);
				printf("%c",21);
				
				
			}

			if(a!=27)
			{

				convert("|------------------------------------------------|", 1);
				convert("|    3                                           |", 2);
				convert("|------              3        3                  |", 3);
				convert("|                --------- ----------            |", 4);
				convert("|       ----------        -                      |", 5);
				convert("|                                                |", 6);
				convert("|         3                                      |", 7);
				convert("|   --------                                 3  3|", 8);
				convert("|                                        --------|", 9);
				convert("|                                       |        |", 10);	
				convert("|                                             3  |", 11);
				convert("|                                     ---   ---  |", 12);
				convert("|                               -----            |", 13);
				convert("|                 3         -------              |", 14);
				convert("|              ----   --------                   |", 15);
				convert("|                                          3     |", 16);
				convert("|            |                            333    |", 17);
				convert("|            3                        -------  3 |", 18);
				convert("|           333           --------           ----|", 19);
				convert("|------------------------------------------------|", 20);
				
				draw(1);
				
				mainchar.X=1;
				mainchar.Y=2;
				
				while(score<27)
				{
					
					change(60,0);
					printf("Your score is %d",score);
					
					a = kbhit();
					
					if (a==1)
					{
						
						a = getch();

						if (a==27)
							break;

						if (a==224)
						{
							
							b = getch();
							
						}
						
						if (a==32)
							detectchest();
						
					}
					
					detect(a,b);
					
					change(mainchar.X, mainchar.Y);
					printf("%c",21);
					
					
				}

			}

			if(a!=27)
			{

				convert("|------------------------------------------------|", 1);
				convert("|         3                                      |", 2);
				convert("|        33                                      |", 3);
				convert("|       333    -------                           |", 4);
				convert("|----- -----                                     |", 5);
				convert("|    |-|                                         |", 6);
				convert("|          -----                                 |", 7);
				convert("|                                               3|", 8);
				convert("|                                    ------------|", 9);
				convert("|                                                |", 10);	
				convert("|                                 3              |", 11);
				convert("|                   3             3              |", 12);
				convert("|                  33            33              |", 13);
				convert("|                 333            33              |", 14);
				convert("|           ---------     ---------              |", 15);
				convert("|                                                |", 16);
				convert("|                                                |", 17);
				convert("|  ----------                                    |", 18);
				convert("|3                                               |", 19);
				convert("|------------------------------------------------|", 20);
				
				draw(1);
				
				mainchar.X=17;
				mainchar.Y=2;
				
				while(score<47)
				{
					
					change(60,0);
					printf("Your score is %d",score);
					
					a = kbhit();
					
					if (a==1)
					{
						
						a = getch();

						if (a==27)
							break;

						if (a==224)
						{
							
							b = getch();
							
						}
						
						if (a==32)
							detectchest();
						
					}
					
					detect(a,b);
					
					change(mainchar.X, mainchar.Y);
					printf("%c",21);
					
					
				}

			}

		}

	}

}

int create()
{

	system("cls");
	
	change(0,0);
	printf("Welcome to the Roidian level editor!\n");
	printf("Move around the cursor using the\n");
	printf("arrow keys.\n");
	printf("|  to create a wall,\n");
	printf("-  to create a floor or ceiling,\n");
	printf("3  to make items\n");
	printf("spaces to make spaces :)\n");
	printf("Plus and minus change which thing you are using\n");
	printf("Press Enter when you are finished, and press Enter to start working!");
	
	int z=0;
	
	while(z!=13)
		z = getch();
	
	z = 0;
	int y=0;
	char blah[5] = " -|3";
	COORD a1;
	a1.X = 0;
	a1.Y = 10;
	change(a1.X,a1.Y);
	int b=1;
	printf("%c",blah[b]);
	
	while(z!=13)
	{
		
		change(a1.X,a1.Y);
		printf("%c",blah[b]);
		
		if(b==0)
			custom[a1.X] [a1.Y-9] = 0;
		
		if(b==1)
			custom[a1.X] [a1.Y-9] = 2;
		
		if(b==2)
			custom[a1.X] [a1.Y-9] = 1;
		
		if(b==3)
			custom[a1.X] [a1.Y-9] = 3;

		z = getch();

		if(z==27)
			return 0;
		
		if(z==61 && b<3)
			b++;
		
		if(z==45 && b>0)
			b--;

		if(z==224)
		{
			
			y = getch();
			
			if(y==77 && a1.X<49)
				a1.X++;
			
			if(y==75 && a1.X>0)
				a1.X--;
			
			if(y==72 && a1.Y>10)
				a1.Y--;
			
			if(y==80 && a1.Y<29)
				a1.Y++;
			
		}
		
	}

	system("cls");

	draw(2);

	z = 0;

	while(z!=13)
		z = getch();

	system("cls");

	change(0,0);
	printf("Starting X-position- ");
	cin >> customstart.X;
	change(0,1);
	printf("Starting Y-position- ");
	cin >> customstart.Y;
	
	system("cls");

	return 0;

}

void detectchest()
{
	int x,y;
	x = mainchar.X;
	y = mainchar.Y;

	if(platform[x+1] [y]==3 || platform[x-1] [y]==3)
	{

		if(platform[x+1] [y]==3)
		{
			change(x+1,y);
			printf(" ");
			platform[x+1] [y] = 0;
		}

		if(platform[x-1] [y]==3)
		{
			change(x-1,y);
			printf(" ");
			platform[x-1] [y] = 0;
		}

		score++;

	}

}

int detect(int a, int b)
{

	int x,y,z;
	x = mainchar.X;
	y = mainchar.Y;

	if(platform[mainchar.X] [mainchar.Y+1]==0)
	{
		Sleep(200);
		change(x,y);
		printf(" ");
		mainchar.Y++;
	}

	if(a==224)
	{
		if(platform[mainchar.X] [mainchar.Y+1]==1 || platform[mainchar.X] [mainchar.Y+1]==2 || platform[mainchar.X] [mainchar.Y+1]==3)
		{
			if(b==72 && platform[mainchar.X] [mainchar.Y-1]==0)
			{
				
				change(x,y);
				printf(" ");
				
				for(z=y;z>y-5;z--)
				{
					if(platform[x] [z-1]==1 || platform[x] [z-1]==2 || platform[x] [z-1]==3)
					{
						mainchar.Y = z;
						return 0;
					}
					change(x,z);
					printf("%c",21);
					Sleep(100);
					change(x,z);
					printf(" ");
				}
				
				mainchar.Y = z;
				return 0;
				
			}

		}

		if(b==77 && platform[mainchar.X+1] [mainchar.Y]==0)
		{

				change(x,y);
				printf(" ");
				mainchar.X++;
				return 0;

		}

		if(b==75 && platform[mainchar.X-1] [mainchar.Y]==0)
		{

				change(x,y);
				printf(" ");
				mainchar.X--;
				return 0;

		}

	}
	return 0;

}

void draw(int x)
{

	int a,b;

	for(b=1;b<21;b++)
	{

		for(a=0;a<50;a++)
		{

			change(a,b);

			if(x==1)
			{

				if(platform[a] [b]==1)
					printf("|");
				
				if(platform[a] [b]==0)
					printf(" ");
				
				if(platform[a] [b]==2)
					printf("-");
				
				if(platform[a] [b]==3)
					printf("%c",15);

			}

			if(x==2)
			{
				if(custom[a] [b]==1)
					printf("|");
				
				if(custom[a] [b]==0)
					printf(" ");
				
				if(custom[a] [b]==2)
					printf("-");
				
				if(custom[a] [b]==3)
					printf("%c",15);

			}

		}

	}

}

void convert(char line1[31], int b)
{
	int a;

	for(a=0;a<50;a++)
	{

		if(line1[a]=='|')
			platform[a] [b] = 1;

		if(line1[a]==' ')
			platform[a] [b] = 0;

		if(line1[a]=='-')
			platform[a] [b] = 2;

		if(line1[a]=='3')
			platform[a] [b] = 3;

	}

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