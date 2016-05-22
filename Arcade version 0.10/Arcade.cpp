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
-	Arcade v0.10													   -
-																	   -
-	Created By:  Jeff Verkoeyen										   -
-																	   -
-	All Rights Reserved												   -
-																	   -
-	Release Dates-													   -
-		v0.1(July 2, 2002)											   -
-			There is only one game so far, Hover Pong, but I am basing -
-			the entire game on my calculator version of my Arcade that -
-			I made about 3 or 4 months ago, it will be very fun once   -
-			finished.												   -
-				Will add for v0.2									   -
-			a LOT more games | Instructions | A better load menu	   -
-			an overall scorekeeper, with high scores				   -
-																	   -
-	ragingflame.150m.com/  <<You can find all updates/versions here	   -
*																	   *
\*||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||*/

/***************************************************************\
*				Numbers for the table pattern-					*
*	single-														*
*												   _	    =|  *
*	179  |    180  -|	181  =|   182	-||   183  ||  184   |  *
*																*
*							==||		 ||			||		  |	*
*	185  =||  186  ||	187   ||  188  ==||	  189  -||	190  =|	*
*																*
*		 _		  |			  |		   ___						*
*	191   |   192  -	193  ---  194	|	  195  |-	196  -	*
*																*
*		 |							  ||			==		||	*
*	197 ---	  198  |=	199 ||-   200  ==	  201  ||  202 ==== *
*		 |														*
*																*
*		====										|		||	*
*	203  ||	  204  ||=	205  ==	  206  -||-   207  === 208 ---- *
*																*
*		===		  ____	    ||		   |			=		_	*
*	209  |	  210  ||	211  --	  212   =	  213  |   214 ||	*
*																*
*				   |		  |			_						*
*	215  -||- 216 ===	217  -	  218  |						*
*				   |											*
*																*
\***************************************************************/


#include <stream.h>

void change(int x, int y);
void changecolor(int x);
void box(int length, int height, int color, int xpos, int ypos, int single);
int pong();

/***************************************************\
*	Don't mess with this junk...it's for the		*
*	random numbers, thanks to Josh Kasten!			*
\***************************************************/
int ranint(int fr,int tr);
void int_s();
int num_mm();

static int rgi[57];
/*ends here*/

HANDLE hConsoleOutput;
COORD dwCursorPosition;

io az;

int main()
{
	
	int a=0;
	
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	
	int_s();
	
	az.box(40,20,13,16,1,1);
	az.hline(16,3,40,13,1,2,0);
	az.change(24,2);
	printf("Jeff Verkoeyen's ARCADE!");
	az.change(25,5);
	printf("Start");
	az.change(18,6);
	printf("Instructions");
	az.change(26,7);
	printf("Quit");
	
	a = az.cursor(17,13,31,5,3);
	
	if(a==1)
	{
		
		system("cls");
		
		pong();
		
		a = 0;
		
		while(a!=13)
			a = getch();
		
	}

	return 0;
	
}

int pong()
{
	
	int a;
	
	int paddle;
	
	COORD ball,direction;
	
	ball.X = 4;
	ball.Y = 8;
	
	a = 2;
	
	while(a==2)
		a = ranint(1,3);
	
	direction.X = a-2;
	
	a = 2;
	
	while(a==2)
		a = ranint(1,3);
	
	direction.Y = a-2;
	
	paddle = 4;
	
	az.box(42,20,13,1,1,2);
	
	az.changecolor(10);
	
	az.change(paddle,20);
	printf("---");
	
	int dead=0,b,count=0,score=0;
	
	az.change(50,2);
	printf("Instructions");
	az.change(50,3);
	printf("Left and Right arrows move");
	az.change(50,4);
	printf("Try and keep the ball from");
	az.change(50,5);
	printf("hitting the end");
	
	while(dead!=1 && score<1000)
	{
		
		count++;
		
		if(count==100)
		{

			score++;

			az.change(50,10);
			printf("%d",score);

			az.change(ball.X,ball.Y);
			printf(" ");
			
			ball.X = ball.X + direction.X;
			ball.Y = ball.Y + direction.Y;
			
			az.change(ball.X,ball.Y);
			printf("%c",15);
			
			if(ball.Y>19 || ball.Y<3)
				direction.Y = -direction.Y;
			
			if(ball.Y==19 && ball.X==paddle)
			{
				
				direction.Y = -direction.Y;
				
				if(direction.X==1)
					direction.X = -direction.X;
				
			}
			
			if(ball.Y==19 && ball.X==paddle+2)
			{
				
				direction.Y = -direction.Y;
				
				if(direction.X==-1)
					direction.X = -direction.X;
				
			}
			
			if(ball.Y==19 && ball.X==paddle+1)
				direction.Y = -direction.Y;
			
			if(ball.X>40 || ball.X<3)
				direction.X = -direction.X;
			
			if(ball.Y==20)
				dead = 1;
			
		}
		
		if(count>8000)
			count = 0;
		
		a = kbhit();
		
		if(a==1)
		{

			a = getch();
			
			if(a==224)
			{
				
				b = getch();
				
				az.change(paddle,20);
				printf("   ");
				
				if(b==77 && paddle<40)
					paddle++;
				
				if(b==75 && paddle>2)
					paddle--;
				
				az.change(paddle,20);
				printf("---");
				
			}
			
		}
		
	}
	
	if(dead==1)
	{
		
		system("cls");
		az.change(0,0);
		az.changecolor(13);
		printf("You missed!");

		a = 0;

		while(a!=13)
			a = getch();
		
	}

	system("cls");

	az.change(0,0);
	printf("You score was %d",score);

	a = 0;

	while(a!=13)
		a = getch();

	return score;
	
}

/*These are all the functions for the random numbers--*/
int ranint(int fr,int tr)
{
    int num,pow;
	
    if ((tr=tr-fr+1)<=1)
		return fr;
	
    for(pow=2; pow<tr; pow<<=1){}
    while((num=num_mm()&(pow-1))>=tr){}
	
    return fr+num;
}

int num_mm()
{
    int *pi; int rani,i1,i2;
    
    pi=&rgi[2];
    i1=pi[-2];
    i2=pi[-1];
    rani=(pi[i1]+pi[i2])&((1<<30)-1);
    pi[i1]=rani;
	
    if (++i1==55)
		i1=0;
	
    if (++i2==55)
		i2=0;
	
    pi[-2]=i1;
    pi[-1]=i2;
	
    return rani;
}

void int_s()
{
    int i; int *pi;
    pi=&rgi[2]; 
	pi[-2]=0; 
	pi[-1]=31;
    pi[0]=(time(NULL))&((1<<30)-1);
    pi[1]=1;
	
    for (i=2; i<10; i++)
		pi[i]=(pi[i-1]+pi[i-2])&((1<<30)-1);
}
/*ends here*/