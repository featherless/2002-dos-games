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
-	Roidian v0.12													   -
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
-		v0.12(June 19, 2002)										   -
-			Added a demo level with the level creator, added another   -
-			obstacle, The Block!, you can push that around, and it	   -
-			falls!  Also made the program slightly smaller and fixed a -
-			glitch with the level editor.							   -
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
void convert(char line1[31], int b, int c);
void draw(int x);
int detect(int a, int b);
void detectchest();
int create();
int execute(int endscore);

int platform[50] [21];
int custom[50] [21];
int customscore=0;
int score=0;
int quit=0;

HANDLE hConsoleOutput;
COORD dwCursorPosition;
COORD mainchar;
COORD customstart;
int main()
{
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	int a=0,b;
	
	convert("|------------------------------------------------|", 1, 2);
	convert("|                                                |", 2, 2);
	convert("| |-------                               O       |", 3, 2);
	convert("| |      --3 - -                                 |", 4, 2);
	convert("| |       --- - -                                |", 5, 2);
	convert("| |        -                             --- --- |", 6, 2);
	convert("| |        -                                     |", 7, 2);
	convert("| |        -                                     |", 8, 2);
	convert("| |        -  33----   --- ---   -----           |", 9, 2);
	convert("| |        - -- 333-- |   |   | |     |       ---|", 10, 2);	
	convert("| |        - -------- |   |   | |     |          |", 11, 2);
	convert("| |        - --       |   |   | |     |     O    |", 12, 2);
	convert("| |        - --       |   |   | |     |     O    |", 13, 2);
	convert("| |        -  --   -- |   |   | |     |     -----|", 14, 2);
	convert("| |        -   -----  |   |   |  -----           |", 15, 2);
	convert("| |       --                                     |", 16, 2);
	convert("| |      --                               ----   |", 17, 2);
	convert("| |-------                                       |", 18, 2);
	convert("|                            333                 |", 19, 2);
	convert("|------------------------------------------------|", 20, 2);

	customstart.X = 2;
	customstart.Y = 19;


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
		printf("Up arrow jumps");
		change(10,8);
		printf("spacebar picks up items ( %c ) and pushes blocks ( O )", 15);
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

			customscore = 0;
			
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

			convert("|------------------------------------------------|", 1, 1);
			convert("|                                |               |", 2, 1);
			convert("|         O                      |     3         |", 3, 1);
			convert("|     O O O                     3|    ---        |", 4, 1);
			convert("|----------           -----------|               |", 5, 1);
			convert("|                     |                       3  |", 6, 1);
			convert("|           ----------|              ------------|", 7, 1);
			convert("|          |                        -            |", 8, 1);
			convert("|                                  -             |", 9, 1);
			convert("|                            ---  -              |", 10, 1);	
			convert("|                                                |", 11, 1);
			convert("|                                                |", 12, 1);
			convert("|               3            3|                  |", 13, 1);
			convert("|               --          ----     3           |", 14, 1);
			convert("|                                   --           |", 15, 1);
			convert("|       |                                        |", 16, 1);
			convert("|       |                                        |", 17, 1);
			convert("|       |         3        |                     |", 18, 1);
			convert("|       |        333      ---                    |", 19, 1);
			convert("|------------------------------------------------|", 20, 1);
			
			/*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*\
			*																	 *
			- You can create your own levels very easily using a subroutine i've -
			- created.  There is very little syntax to execute the subroutine-   -
			- convert("|     O O O                     3|    ---        |", 4, 1)-
			- the long line of symbols is what the convert routine uses to       -
			- convert them into numbers and then draw them on the screen         -
			- 3=  [chest]	O= [block]											 -
			- Then you run the draw routine to make it put the array on the		 -
			- screen.	(Oh, and don't worry about the last two numbers,		 -
			- KEEP 'em).														 -
			*																	 *
			\*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/
			
			draw(1);
			
			mainchar.X=3;
			mainchar.Y=3;
			
			//	^^ These are your starting coordinates on the screen
			
			execute(10);

			if(quit!=1)
			{

				convert("|------------------------------------------------|", 1, 1);
				convert("|    3                                           |", 2, 1);
				convert("|------              3        3                  |", 3, 1);
				convert("|                --------- ----------            |", 4, 1);
				convert("|       ----------        -                      |", 5, 1);
				convert("|                                                |", 6, 1);
				convert("|         3                                      |", 7, 1);
				convert("|   --------                                 3  3|", 8, 1);
				convert("|                                        --------|", 9, 1);
				convert("|                                       |        |", 10, 1);	
				convert("|                                             3  |", 11, 1);
				convert("|                                     ---   ---  |", 12, 1);
				convert("|                               -----            |", 13, 1);
				convert("|                 3         -------              |", 14, 1);
				convert("|              ----   --------                   |", 15, 1);
				convert("|                                          3     |", 16, 1);
				convert("|            |                            333    |", 17, 1);
				convert("|            3                        -------  3 |", 18, 1);
				convert("|           333           --------           ----|", 19, 1);
				convert("|------------------------------------------------|", 20, 1);
				
				draw(1);
				
				mainchar.X=1;
				mainchar.Y=2;
				
				execute(27);

			}

			if(quit!=1)
			{

				convert("|------------------------------------------------|", 1, 1);
				convert("|         3                                      |", 2, 1);
				convert("|        33                                      |", 3, 1);
				convert("|       333    -------                           |", 4, 1);
				convert("|----- -----                                     |", 5, 1);
				convert("|    |-|                                         |", 6, 1);
				convert("|          -----                                 |", 7, 1);
				convert("|                                               3|", 8, 1);
				convert("|                                    ------------|", 9, 1);
				convert("|                                                |", 10, 1);	
				convert("|                                 3              |", 11, 1);
				convert("|                   3             3              |", 12, 1);
				convert("|                  33            33              |", 13, 1);
				convert("|                 333            33              |", 14, 1);
				convert("|           ---------     ---------              |", 15, 1);
				convert("|                                                |", 16, 1);
				convert("|                                                |", 17, 1);
				convert("|  ----------                                    |", 18, 1);
				convert("|3                                               |", 19, 1);
				convert("|------------------------------------------------|", 20, 1);
				
				draw(1);
				
				mainchar.X=17;
				mainchar.Y=2;

				execute(47);

			}

		}

	}

	quit = 0;
	score = 0;

}

int execute(int endscore)
{
	int a,b;

	while(score<endscore)
	{
		
		change(60,0);
		printf("Your score is %d",score);
		
		a = kbhit();
		
		if (a==1)
		{
			
			a = getch();

			if (a==27)
			{
				quit = 1;
				return 0;
			}

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

	return 0;

}

int create()
{

	system("cls");
	
	change(0,22);
	printf("Welcome to the Roidian level editor!\n");
	printf("Move around the cursor using the\n");
	printf("arrow keys.\n");
	printf("|  to create a wall,  -  to create a floor or ceiling,\n");
	printf("3  to make items,     O  to create a block\n");
	printf("spaces to make spaces :)\n");
	printf("Plus and minus change which thing you are using\n");
	printf("Press Enter when you are finished, and press Enter to start working!\n");
	printf("Delete clears the entire screen, ONLY DO THIS IF YOU WANT TO START OVER!");

	int z=0;
	
	while(z!=13)
		z = getch();
	
	z = 0;
	int y=0;
	char blah[10] = " |-3O";
	COORD a1;
	a1.X = 0;
	a1.Y = 1;
	change(a1.X,a1.Y);
	int b=1;
	draw(3);
	printf("%c",blah[b]);

	change(49,20);
	printf("  ");

	int n,m;
		
	while(z!=13)
	{
		
		change(a1.X,a1.Y);
		printf("%c",blah[b]);
		
		custom[a1.X] [a1.Y] = b;

		z = getch();

		if(z==27)
			return 0;
		
		if(z==61 && b<4)
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
			
			if(y==72 && a1.Y>1)
				a1.Y--;
			
			if(y==80 && a1.Y<20)
				a1.Y++;

			if(y==83)
			{

				for(m=0;m<21;m++)
				{
					
					for(n=0;n<50;n++)
					{
						
						platform[n] [m] = custom[n] [m] = 0;
						change(n,m);
						printf(" ");
						
					}
					
				}

			}
			
		}
		
	}

	system("cls");

	draw(2);

	z = 0;

	while(z!=13)
		z = getch();

	system("cls");

	customstart.X=customstart.Y=0;

	change(0,0);
	printf("Starting X-position- ");
	cin >> customstart.X;
	change(0,1);
	printf("Starting Y-position- ");
	cin >> customstart.Y;

	if(customstart.X>49)
		customstart.X = 49;

	if(customstart.X<1)
		customstart.X = 1;

	if(customstart.Y>19)
		customstart.Y = 19;

	if(customstart.Y<1)
		customstart.Y = 1;
	
	system("cls");

	return 0;

}

void detectchest()
{
	int x,y;
	x = mainchar.X;
	y = mainchar.Y;

	if(platform[x+1] [y]==4 || platform[x-1] [y]==4)
	{

		if(platform[x+1] [y]==4 && platform[x+2] [y]==0)
		{

			change(x+1,y);
			printf(" ");
			platform[x+1] [y] = 0;
			change(x+2,y);
			printf("O");
			platform[x+2] [y] = 4;

		}

		if(platform[x-1] [y]==4 && platform[x-2] [y]==0)
		{

			change(x-1,y);
			printf(" ");
			platform[x-1] [y] = 0;
			change(x-2,y);
			printf("O");
			platform[x-2] [y] = 4;

		}

	}

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

	int c,d;

	for(d=0;d<21;d++)
	{
		
		for(c=0;c<50;c++)
		{
			
			if(platform[c] [d]==4 && platform[c] [d+1]==0)
			{
				
				change(c,d);
				printf(" ");
				platform[c] [d]=0;
				change(c,d+1);
				printf("O");
				platform[c] [d+1]=4;

			}
			
		}
		
	}

	if(a==224)
	{
		if(platform[mainchar.X] [mainchar.Y+1]==1 || platform[mainchar.X] [mainchar.Y+1]==2 || platform[mainchar.X] [mainchar.Y+1]==3 || platform[mainchar.X] [mainchar.Y+1]==4)
		{
			if(b==72 && platform[mainchar.X] [mainchar.Y-1]==0)
			{
				
				change(x,y);
				printf(" ");
				
				for(z=y;z>y-5;z--)
				{
					if(platform[x] [z-1]!=0)
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

				if(platform[a] [b]==4)
					printf("O");

			}

			if(x==2 || x==3)
			{
				if(custom[a] [b]==1)
					printf("|");
				
				if(custom[a] [b]==0)
					printf(" ");
				
				if(custom[a] [b]==2)
					printf("-");
				
				if(custom[a] [b]==3)
					printf("%c",15);

				if(custom[a] [b]==4)
					printf("O");

			}

			if(x==3)
			{

				if(custom[a] [b]==3)
					printf("3");

			}

		}

	}

}

void convert(char line1[31], int b, int c)
{
	int a;

	for(a=0;a<50;a++)
	{

		if(c==1)
		{

			if(line1[a]=='|')
				platform[a] [b] = 1;
			
			if(line1[a]==' ')
				platform[a] [b] = 0;
			
			if(line1[a]=='-')
				platform[a] [b] = 2;
			
			if(line1[a]=='3')
				platform[a] [b] = 3;
			
			if(line1[a]=='O')
				platform[a] [b] = 4;

		}

		if(c==2)
		{

			if(line1[a]=='|')
				custom[a] [b] = 1;
			
			if(line1[a]==' ')
				custom[a] [b] = 0;
			
			if(line1[a]=='-')
				custom[a] [b] = 2;
			
			if(line1[a]=='3')
				custom[a] [b] = 3;
			
			if(line1[a]=='O')
				custom[a] [b] = 4;

		}

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