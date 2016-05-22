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
-	Roidian v0.20													   -
-																	   -
-	Header files:													   -
-		stream.h  Required version: v0.12 or higher					   -
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
-		v0.20(November 15, 2002)									   -
-			I have now added the ability to save and load your levels  -
-			in the format *.rdl.  This is a great advance in the game, -
-			that's why it is now v0.20.  If you would like to add	   -
-			levels to the arcade mode, send your rdl files to me, and  -
-			I will add them to the arcade mode.						   -
-																	   -
-	ragingflame.150m.com/  <<You can find all updates/versions here	   -
*																	   *
\*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

#include <stream.h>

io az;

void convert(char line1[31], int b, int c);
void draw(int x);
int detect(int a, int b);
void detectchest();
int create();
int execute(int endscore);
void writefile(char filename[20]);
void readfile();

int platform[50] [21];
int custom[50] [21];
int customscore=0;
int score=0;
int quit=0;

char str1[10] = " |-3O";

HANDLE hConsoleOutput;
COORD dwCursorPosition;
COORD mainchar;
COORD customstart;

int main()
{

	str1[3]=15;
	
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

	writefile("Demo.rdl");

	convert("                                                  ", 1, 2);
	convert("                                                  ", 2, 2);
	convert("                                                  ", 3, 2);
	convert("                                                  ", 4, 2);
	convert("                                                  ", 5, 2);
	convert("                                                  ", 6, 2);
	convert("                                                  ", 7, 2);
	convert("                                                  ", 8, 2);
	convert("                                                  ", 9, 2);
	convert("                                                  ", 10, 2);	
	convert("                                                  ", 11, 2);
	convert("                                                  ", 12, 2);
	convert("                                                  ", 13, 2);
	convert("                                                  ", 14, 2);
	convert("                                                  ", 15, 2);
	convert("                                                  ", 16, 2);
	convert("                                                  ", 17, 2);
	convert("                                                  ", 18, 2);
	convert("                                                  ", 19, 2);
	convert("                                                  ", 20, 2);

	customstart.X = 2;
	customstart.Y = 19;

	writefile("Blank.rdl");

	while(1)
	{

		a = 0;

		az.clrscrn();
		
		az.change(30,0);
		az.changecolor(15);
		printf("Welcome to Roidian!");
		az.change(20,1);
		printf("Press 1 to play normal arcade mode");			//49
		az.change(20,2);
		printf("Press 2 to create your own level");				//50
		az.change(20,3);
		printf("Press 3 to play the level you've created");		//51
		az.change(30,4);
		printf("Press Escape to quit");							//13
		az.change(10,6);
		printf("Left and Right arrow keys move left and right");
		az.change(10,7);
		printf("Up arrow jumps");
		az.change(10,8);
		printf("spacebar picks up items ( %c ) and pushes blocks ( O )", 15);
		az.change(30,9);
		printf("By Jeff Verkoeyen");
		az.change(20,10);
		printf("Please press alt-enter to go full screen");
		
		while(a!=49 && a!=50 && a!=51 && a!=27)
			a = getch();
		
		az.clrscrn();
		
		if(a==27)
			return 0;

		if(a==50)
			create();
		
		if(a==51)
		{

			readfile();

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
				
				az.change(60,0);
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
				
				az.change(mainchar.X, mainchar.Y);
				printf("%c",21);
				
			}

			if(!customscore)
			{

				az.change(0,0);
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

			score = 0;

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
		
		az.change(60,0);
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
				b = getch();

			if (a==32)
				detectchest();

		}

		detect(a,b);

		az.change(mainchar.X, mainchar.Y);
		printf("%c",21);
		
	}

	return 0;

}

int create()
{

	readfile();

	az.clrscrn();
	
	az.change(0,22);
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
	az.change(53,5);
	printf("Plus/minus change tile");
	COORD a1;
	a1.X = 0;
	a1.Y = 1;
	az.change(a1.X,a1.Y);
	int b=1;
	draw(3);
	printf("%c",str1[b]);

	az.change(49,20);
	printf("  ");

	int n,m;
		
	while(z!=13)
	{
		
		az.change(a1.X,a1.Y);
		printf("%c",str1[b]);
		
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
						az.change(n,m);
						printf(" ");
						
					}
					
				}

			}
			
		}
		
	}

	az.clrscrn();

	draw(2);

	z = 0;

	while(z!=13)
		z = getch();

	az.clrscrn();

	customstart.X=customstart.Y=1;

	az.change(0,0);
	printf("Starting position, press enter when you've chosen");

	z=0;
	draw(2);
	while(z!=13)
	{
		
		z=az.getkey();

		if(z)
			draw(2);

		customstart.X+=(z==377)*(customstart.X<49)-(z==375)*(customstart.X>0);
		customstart.Y+=(z==380)*(customstart.Y<20)-(z==372)*(customstart.Y>1);

		az.change(customstart.X,customstart.Y);
		printf("+");

	}
	
	az.clrscrn();

	az.change(0,0);
	
	int aob=0;
	while(aob!=1 && aob!=2)
	{
		printf("Would you like to save your file? 1:Yes  2:No ");
		cin >> aob;
	}

	if(aob==1)
	{

		printf("Please enter a name for your file: ");
		char filename[18];
		cin.ignore(80,'\n');
		cin.get(filename,17);
		strcat(filename,".rdl");
		writefile(filename);
	}

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

			az.change(x+1,y);
			printf(" ");
			platform[x+1] [y] = 0;
			az.change(x+2,y);
			printf("O");
			platform[x+2] [y] = 4;

		}

		if(platform[x-1] [y]==4 && platform[x-2] [y]==0)
		{

			az.change(x-1,y);
			printf(" ");
			platform[x-1] [y] = 0;
			az.change(x-2,y);
			printf("O");
			platform[x-2] [y] = 4;

		}

	}

	if(platform[x+1] [y]==3 || platform[x-1] [y]==3)
	{

		if(platform[x+1] [y]==3)
		{
			az.change(x+1,y);
			printf(" ");
			platform[x+1] [y] = 0;
		}

		if(platform[x-1] [y]==3)
		{
			az.change(x-1,y);
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
		Sleep(150);
		az.change(x,y);
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

				az.change(c,d);
				printf(" ");
				platform[c] [d]=0;
				az.change(c,d+1);
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
				
				az.change(x,y);
				printf(" ");
				
				for(z=y;z>y-5;z--)
				{
					if(platform[x] [z-1]!=0)
					{
						mainchar.Y = z;
						return 0;
					}
					az.change(x,z);
					printf("%c",21);
					Sleep(100);
					az.change(x,z);
					printf(" ");
				}
				
				mainchar.Y = z;
				return 0;
				
			}

		}

		if(b==77 && platform[mainchar.X+1] [mainchar.Y]==0)
		{

				az.change(x,y);
				printf(" ");
				mainchar.X++;
				return 0;

		}

		if(b==75 && platform[mainchar.X-1] [mainchar.Y]==0)
		{

				az.change(x,y);
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

			az.change(a,b);

			if(x==1)
				printf("%c",str1[platform[a] [b]]);

			if(x==2 || x==3)
				printf("%c",str1[custom[a] [b]]);

		}

	}

}

void convert(char line1[50], int b, int c)
{

	for(int a=0;a<50;a++)
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

void writefile(char filename[20])
{

	struct tm *newtime;
	time_t long_time;
	int hours, minutes, seconds, day_of_month, month, year;

	time( &long_time );

	newtime = localtime( &long_time );

	year = newtime->tm_year;
	month = newtime->tm_mon;
	day_of_month = newtime->tm_mday;
	minutes = newtime->tm_min;
	seconds = newtime->tm_sec;
	hours = newtime->tm_hour;
	
	ofstream file;

	if(filename=="Demo.rdl" || filename=="Blank.rdl")
		file.open(filename, ios::out);
	else
		file.open(filename, ios::out | ios::noreplace);
	
	if(file)
	{
		
		for(int loopb=1;loopb<21;loopb++)
		{
			
			for(int loopa=0;loopa<50;loopa++)
			{
				file << str1[custom[loopa] [loopb]];
				
			}
			
			file << endl;
			
		}

		file << "Xpos:" << customstart.X << "\nYpos:" << customstart.Y << endl;
		
		file << "Last edited on: " << day_of_month << '/' << month+1 << '/' << year
			<< " " << hours << ':' << minutes << ':' << seconds << '\n';

		file << "Filename: " << filename << endl;
		
		file.close();
		
	}
	else
	{
		
		int aob=0;

		while(aob!=1 && aob!=2)
		{
			printf("Error, this file already exists, would you like to overight? 1:Yes 2:No ");
			cin >> aob;
		}
		
		if(aob==1)
		{
			
			ofstream file;
			file.open(filename, ios::out);
			
			if(file)
			{
				
				for(int loopb=1;loopb<21;loopb++)
				{
					
					for(int loopa=0;loopa<50;loopa++)
					{
						file << str1[custom[loopa] [loopb]];
					}
					
					file << endl;
					
				}
				
				file << "Xpos:" << customstart.X << "\nYpos:" << customstart.Y << endl;
				
				file << "Last edited on: " << day_of_month << '/' << month+1 << '/' << year
					<< " " << hours << ':' << minutes << ':' << seconds << '\n';
				
				file << "Filename: " << filename << endl;
				
				file.close();
				
			}

		}

	}

}

void readfile()
{

	az.change(0,0);
	cout << "Please enter the name of the file you'd like to load, or just type Demo\nor blank if you haven't made any " << endl;
	char filename[18];
	
	cin.get(filename,17);
	cin.ignore(120,'\n');
	
	strcat(filename,".rdl");
	
	az.clrscrn();
	
	ifstream file;
	file.open(filename, ios::in | ios::nocreate);
	
	if(file)
	{

		char buff[53];
		
		for(int loopb=1;loopb<21;loopb++)
		{
			file.getline(buff,52);
			convert(buff,loopb,2);
		}

		file.ignore(1000,':');
		file.getline(buff,3);

		customstart.X = atoi(buff);
		
		file.ignore(10,':');
		file.getline(buff,3);

		customstart.Y = atoi(buff);

		file.close();

	}
	else
	{

		az.change(0,0);
		printf("The file does not exist");
		int aoc=0;

		while(aoc!=13)
			aoc=getch();

	}

	az.clrscrn();

}
