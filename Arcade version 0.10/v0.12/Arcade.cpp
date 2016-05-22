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
-	Arcade v0.12													   -
-																	   -
-	Created By:  Jeff Verkoeyen										   -
-																	   -
-	All Rights Reserved												   -
-																	   -
-	Release Dates-													   -
-		v0.10(July 2, 2002)											   -
-			There is only one game so far, Hover Pong, but I am basing -
-			the entire game on my calculator version of my Arcade that -
-			I made about 3 or 4 months ago, it will be very fun once   -
-			finished.												   -
-				Will add for v0.20									   -
-			a LOT more games | Instructions | A better load menu	   -
-			an overall scorekeeper, with high scores				   -
-		v0.11(July 13, 2002)										   -
-			Made the entire program a little more functional, added    -
-			the instructions and the better load menu.  Also, the	   -
-			overall scorekeeper is finished, however, I might have to  -
-			slightly fix it...										   -
-		v0.12(July 15, 2002)										   -
-			Added a WHOLE lot more functionality, high scores menu,    -
-			and it works too!  Also the ability to change the speed in -
-			Hover Pong.  Oh, and I promise I'll add more games soon!!  -
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

int pong();
void drawpong(int paddle);
int recordhighs(int game);
int recordscores(int game, int game2);

/***************************************************\
*	Don't mess with this junk...it's for the		*
*	random numbers, thanks to Josh Kasten!			*
\***************************************************/
int ranint(int fr,int tr);
void int_s();
int num_mm();

static int rgi[57];
/*ends here*/

int overall=0;
int pongscore[1] [10];
int pong1;
int ingame=0;
int speed=1000;

HANDLE hConsoleOutput;
COORD dwCursorPosition;

io az;

int main()
{
	
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	
	int_s();
	
	int a=0;
	
	int b=500;
	
	for(a=1;a<11;a++)
	{
		
		pongscore[1] [a] = b;
		
		b = b-50;
		
	}
	
start:

	ingame = 0;
	
	system("cls");
	
	az.box(40,20,13,16,1,1,0);
	az.hline(16,3,40,13,1,2,0);
	az.change(24,2);
	printf("Jeff Verkoeyen's ARCADE!");
	az.change(25,5);
	printf("Start");
	az.change(18,6);
	printf("Instructions");
	az.change(19,7);
	printf("High Scores");
	az.change(26,8);
	printf("Quit");
	az.change(29,19);
	printf("Your score is %d",overall);
	
	a = az.cursor(17,13,31,5,4);

	if(a==3)
	{

		system("cls");

		az.change(0,0);
		printf("High Scores\nPong-");

		for(b=1;b<11;b++)
		{

			az.change(0,b+3);
			printf("%d",pongscore[1] [b]);

		}

		b=0;

		while(b!=13)
			b = getch();

		goto start;

	}
	
	if(a==1)
	{
		
		system("cls");
		
		az.box(40,20,13,16,1,1,0);
		az.hline(16,3,40,13,1,2,0);
		
		az.change(24,2);
		printf("Jeff Verkoeyen's ARCADE!");
		az.change(18,5);
		printf("Hover Pong");
		az.change(24,6);
		printf("Back");
		az.change(29,19);
		printf("Your score is %d",overall);
		
		a = az.cursor(17,13,29,5,2);
		
		if(a==1)
		{
			
			system("cls");
			
			overall = overall + pong();
			
			a = 0;
			
		}
		
		goto start;
		
	}
	
	if(a==2)
	{
		
		system("cls");
		
		az.box(40,20,13,16,1,1,0);
		az.hline(16,3,40,13,1,2,0);
		
		az.change(24,2);
		printf("Jeff Verkoeyen's ARCADE!");
		
		az.change(18,5);
		printf("Instructions");
		
		az.change(18,7);
		printf("The Arcade is pretty simple to figure");
		
		az.change(18,8);
		printf("out.");
		
		az.change(18,9);
		printf("Hover Pong-");
		
		az.change(18,10);
		printf("Just like classic Pong, you use");
		
		az.change(18,11);
		printf("arrow keys to move.");
		
		a = 0;
		
		while(a!=13)
			a = getch();
		
		system("cls");
		
		az.box(40,20,13,16,1,1,0);
		az.hline(16,3,40,13,1,2,0);
		
		az.change(24,2);
		printf("Jeff Verkoeyen's ARCADE!");
		
		az.change(18,5);
		printf("In all of the games, you can press");
		
		az.change(18,6);
		printf("Enter to pause, and Escape to quit.");
		
		a = 0;
		
		while(a!=13)
			a = getch();
		
		goto start;
		
	}
	
	return 0;
	
}

void drawpong(int paddle)
{
	
	az.box(42,20,13,1,1,2,0);
	az.changecolor(10);
	az.change(paddle,20);
	printf("---");
	
	az.change(50,2);
	printf("Instructions");
	az.change(50,3);
	printf("Left and Right arrows move");
	az.change(50,4);
	printf("Try and keep the ball from");
	az.change(50,5);
	printf("hitting the end");
	az.change(50,6);
	printf("+/- change speed");
	
}

int recordhighs(int game)
{
	
	int a;

	if(game)
	{

		for(a=1;a<11;a++)
		{

			if(pong1>pongscore[1] [a])
			{

				if(ingame)
					return a;

				recordscores(1,a);
				break;

			}

		}

	}

	return 0;

}

int recordscores(int game, int game2)
{

	int a;

	system("cls");
	az.change(20,0);
	printf("HIGH SCORE!");
	
	a = 0;
	
	while(a!=13)
		a =getch();

	if(game)
	{

		for(a=10;a>game2;a--)
		{

			pongscore[1] [a] = pongscore[1] [a-1];

		}

		pongscore[1] [game2] = pong1;

		return 0;

	}

	return 0;

}

int pong()
{

	ingame = 1;
	
	int a;
	
	int paddle;
	
	COORD ball,direction;
	
	ball.X = 4;
	ball.Y = 8;
	
	a=2;

	while(a==2)
		a = ranint(1,3);

	pongscore[1] [1]--;

	direction.X = a-2;
	
	direction.Y = a-2;
	
	paddle = 4;
	
	drawpong(paddle);
	
	int dead=0,b,count=0,score=0;
	
	while(dead!=1 && score<1000)
	{
		
		count++;

		az.change(50,11);
		printf("Current Place- %d ",recordhighs(1));
		
		if(count==1)
		{
			
			score++;

			pong1 = score;
			
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
		
		if(count>speed)
			count = 0;
		
		a = kbhit();
		
		if(a==1)
		{
			
			a = getch();
			
			if(a==27)
				break;
			
			if(a==13)
			{
				
				az.pause(13);
				
				drawpong(paddle);
				
			}

			if(a==45 && speed<3500)
				speed = speed + 100;

			if(a==61 && speed>500)
				speed = speed - 100;
			
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
	
	ingame = 0;
	recordhighs(1);
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