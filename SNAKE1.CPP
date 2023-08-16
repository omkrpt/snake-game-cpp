//============================================================================================
//============================================================================================
//                   =========================================================================
// SNAKE - THE GAME  =========================================================================
//                   =========================================================================
//============================================================================================
//============================================================================================

// By : Omkar Pote
// Date : Jan 2015

// FEATURES :
// => Multicolor GUI
// => High Score
// => In-game Sound
// => Unlimited Food
// => Boundary







//============================================================================================
// HEADER FILES ==============================================================================

#include<stdio.h>
#include<dos.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<graphics.h>
#include<string.h>

// HEADER FILES END ==========================================================================
//============================================================================================






//============================================================================================
// MACROS ====================================================================================

// Directions for snake to move

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4

// Color codes
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define CYAN 3
#define RED 4
#define MAGENTA 5
#define BROWN 6
#define LIGHTGRAY 7
#define DARKGRAY 8
#define LIGHTBLUE 9
#define LIGHTGREEN 10
#define LIGHTCYAN 11
#define LIGHTRED 12
#define LIGHTMAGENTA 13
#define YELLOW 14
#define WHITE 15

// MACROS END ================================================================================
//============================================================================================










//============================================================================================
//                ============================================================================
// GAME FUNCTIONS ============================================================================
//                ============================================================================
//============================================================================================


//============================================================================================
// BASIC DECLARATIONS ========================================================================

int score; // Keep count of the game score
int i; // General int for counting
int speed = 10; // Stores gameplay speed
int breakKey = 0; // To break to Main Menu
int highScore = 0; // Stores high score
int foodCount = 0; // To keep count of the food
int bendNum = 0;
int bendNum2 = 0;
int tries = 0;
int bonusX, bonusY;
int timer = 0;
int timerBig;
int level = 1;
int cursor;
int selected;

char highScoreStr[20]; // String containing high score
char scoreString[20]; // String containing ready-to-display score
char menuKey;
char timeString[20];
char speedInput;
char input;





//============================================================================================
// DOTTED HORIZONTAL LINE FUNCTION ===========================================================
void dotHor(int x1, int x2, int y, int gap)
{
	if(x1>=x2)
		for(i=x2; i<=x1; i=i+(2*gap))
			line(i, y, i+gap, y);
	if(x2>=x1)
		for(i=x1; i<=x2; i=i+(2*gap))
			line(i, y, i+gap, y);
}






//============================================================================================
// DOTTED VERTICAL LINE FUNCTION =============================================================
void dotVer(int y1, int y2, int x, int gap)
{
	if(y1>=y2)
		for(i=y2; i<=y1; i=i+(2*gap))
			line(x, i, x, i+gap);
	if(y2>=y1)
		for(i=y1; i<=y2; i=i+(2*gap))
			line(x, i, x, i+gap);
}



struct text
{
	int textX;
	int textY;

	char str[80];

	void disp()
	{
		outtextxy(textX, textY, str);
	}

} levMenu[5], firstMenu[5], speedMenu[6];


int cursorMenu(text strArr[], int size)
{

	 setcolor(RED);
	 strArr[0].disp();

	 setcolor(BLUE);
	 for(i = 1; i<size; i++)
		strArr[i].disp();



	 cursor = 0;
	 selected = 0;

	 while(selected != 1)
	 {
		input = getch();

		setcolor(BLUE);
		strArr[cursor].disp();

		if((cursor>0)&&((input == 72)||(input == 75)))
			cursor--;

		else if((cursor<(size-1))&&((input == 80)||(input == 77)))
			cursor++;

		else if((cursor==0)&&((input == 72)||(input == 75)))
			cursor=(size-1);

		else if((cursor==(size-1))&&((input == 80)||(input == 77)))
			cursor=0;

		else if(input == 13)
			selected = 1;

		setcolor(RED);
		strArr[cursor].disp();

		if((input == 72)||(input == 75)||(input == 80)||(input == 77))
		{
			sound(500);
			delay(20);
			nosound();
		}
		if(input == 13)
		{
			sound(800);
			delay(100);
			nosound();
		}
	 }

	 return cursor;
}



//============================================================================================
// LEVEL SELECT MENU =========================================================================
void selectLevel()
{

	 cleardevice();
	 setbkcolor(LIGHTBLUE);

	 for(i=0; i<5; i++)
	 {
		levMenu[i].textX = 35;
		levMenu[i].textY = 150 + (i*50);
	 }

	 strcpy(levMenu[0].str,"1. Level 1 : Classic");
	 strcpy(levMenu[1].str,"2. Level 2");
	 strcpy(levMenu[2].str,"3. Level 3");
	 strcpy(levMenu[3].str,"4. Level 4");
	 strcpy(levMenu[4].str,"5. Level 5 : Randomized");

	 setcolor(RED);
	 settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
	 outtextxy(20,40,"Game Level :");

	 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	 level = cursorMenu(levMenu, 5) + 1;

	 setcolor(BLUE);
	 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	 outtextxy(20,450,"Press any key to continue");

	 getch();

	 cleardevice();

}





//============================================================================================
// SPEED SELECT MENU =========================================================================
void selectSpeed()
{

	 cleardevice();
	 setbkcolor(LIGHTBLUE);

	 setcolor(RED);
	 settextstyle(DEFAULT_FONT, HORIZ_DIR, 4);
	 outtextxy(20,40,"Gameplay Speed :");

	 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	 setcolor(RED);
	 outtextxy(35,400,"   Extreme Speed!!!");
	 setcolor(BLUE);

	 for(i = 0; i<6; i++)
	 {
		speedMenu[i].textX = 35;
		speedMenu[i].textY = 150 + (i*50);
	 }

	 strcpy(speedMenu[0].str,"1. Very Fast        : Only for experts");
	 strcpy(speedMenu[1].str,"2. Fast             : For gamers");
	 strcpy(speedMenu[2].str,"3. Normal           : Perhaps for you");
	 strcpy(speedMenu[3].str,"4. Slow             : If you're scared of losing");
	 strcpy(speedMenu[4].str,"5. Kid Mode         : Very slow - Highly recommended for kids below 7");
	 strcpy(speedMenu[5].str,"6.                  : These stunts are performed only by professionals");

	 speedInput = cursorMenu(speedMenu, 6) + 1;
	 switch(speedInput)
	 {
	 case 1 :
		speed = 2;
		outtextxy(35,425,"Speed is set to Very Fast");
		break;
	 case 2 :
		speed = 5;
		outtextxy(35,425,"Speed is set to Fast");
		break;
	 case 3 :
		speed = 10;
		outtextxy(35,425,"Speed is set to Normal");
		break;
	 case 4 :
		speed = 18;
		outtextxy(35,425,"Speed is set to Slow");
		break;
	 case 5 :
		speed = 25;
		outtextxy(35,425,"Kid Mode !");
		break;
	 case 6 :
		speed = 1;
		setcolor(RED);
		outtextxy(35,425,"Beware! You are trying this at home!");
		setcolor(BLUE);
		break;
	 default :
		outtextxy(35,425,"Speed is set to Normal by default");
		speed = 10;
	 }

	 setcolor(BLUE);
	 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	 outtextxy(20,450,"Press any key to continue");

	 getch();

	 cleardevice();

}






//============================================================================================
// INSTRUCTIONS PAGE =========================================================================
void instruct()
{

	 cleardevice();
	 setbkcolor(LIGHTBLUE);


	 setcolor(RED);
	 settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
	 outtextxy(30,40,"Instructions");

	 setcolor(BLUE);
	 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);

	 outtextxy(40,120,"Control the snake using arrow keys");

	 outtextxy(40,160,"Collect as much food as you can");

	 outtextxy(40,200,"Food is in the form of red clusters and bonus purple food.");

	 outtextxy(40,240,"You have all the time in the world");

	 outtextxy(40,280,"There's only one life");

	 outtextxy(40,320,"Do not hit the boundary; to remain alive");

	 outtextxy(40,360,"Life is lost if snake bites itself or time is up");

	 outtextxy(40,400,"This game is more of a patience and reaction time test,");
	 outtextxy(40,415," than a source of entertainment");

	 outtextxy(20,450,"Press any key to continue");

	 getch();

	 cleardevice();

}






//============================================================================================
// SNAKE STRUCTURE ===========================================================================
struct
{

   int length;

   int head_x;         // Stores Head X Coordinates

   int head_y;         // Stores Head Y Coordinates

   int head_dir;       // Stores Head Direction

   int tail_x;         // Stores Tail X Coordinates

   int tail_y;         // Stores Tail Y Coordinates

   int tail_dir;       // Stores Tail Direction

   int bend_x[1000];   // Stores X Bend Coordinates

   int bend_y[1000];   // Stores Y Bend Coordinates

   int bend_dir[1000]; // Stores Bend direction (direction to be turned on reaching the bend)

} snake;     	       // Declares a variable of the structure






//============================================================================================
// RANDOM VALUE FUNCTION : Returns a random int value between end and starting parameters =====
int randomvalue(int starting, int ending)
{

	static int previous = 0;

	int answer;

	if(previous<0) previous = 0;

	int difference = starting - ending;

	time_t t;

	srand((unsigned) time(&t));

	for(int i = 0;i<previous;i++) rand();

	answer = (rand() % difference);

	previous++;

	return answer;

}






//============================================================================================
// GAME OVER FUNCTION : END GAME AND EXIT TO MAIN MENU =======================================
void gameOver()
{
		 setcolor(DARKGRAY); 								// Text Formatting
		 settextstyle(DEFAULT_FONT, HORIZ_DIR, 6);		// Text Formatting
		 sprintf(scoreString, "Score: %d", score); // Stores the subsequent string in scoreString
		 outtextxy(130,240,scoreString); // Displays scoreString
		 setcolor(BLUE);
		 settextstyle(SIMPLEX_FONT, HORIZ_DIR, 1);
		 outtextxy(470,440,"Omkar Pote 2014");



		 for(i=0;i<3;i++)
		 {
			setcolor(LIGHTRED);
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 8);
			outtextxy(40,140,"Game Over");
			sound(100); // Generates 100hz sound
			delay(250); // Waits/delays for 250 milliseconds

			setcolor(RED);
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 8);
			outtextxy(40,140,"Game Over");
			nosound();
			delay(150);
		 }

		 nosound(); // Stops the sound

		 delay(1000);

		 if((score==highScore)&&(highScore)&&(tries))
		 {
			cleardevice();
			setcolor(RED);
			settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
			outtextxy(40,200,"High Score");
			delay(150);

			for(i=0;i<3;i++)
			{
				setcolor(LIGHTRED);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
				outtextxy(40,200,"High Score");
				delay(150);

				for(int a=500; a<=1200; a+=100)
				{
					sound(a);
					delay(25);
				}

				setcolor(RED);
				settextstyle(DEFAULT_FONT, HORIZ_DIR, 7);
				outtextxy(40,200,"High Score");
				delay(250);
			}

			delay(100);
			nosound();
			delay(1000);

		 }

		 setcolor(BLUE);
		 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		 outtextxy(20,450,"Press any key to exit to Main Menu");

		 getch();
		 cleardevice();
		 breakKey = 1;
}






//============================================================================================
// MAIN MENU FUNCTION : First screen =========================================================
void mainMenu()
{

	 int playStart = 0;

	 for(i = 0; i<5; i++)
	 {
		firstMenu[i].textX = 50;
		firstMenu[i].textY = 300 + (i*20);
	 }

	 strcpy(firstMenu[0].str,"Play");
	 strcpy(firstMenu[1].str,"Instructions");
	 strcpy(firstMenu[2].str,"Speed");
	 strcpy(firstMenu[3].str,"Level");
	 strcpy(firstMenu[4].str,"Exit");

	 setbkcolor(LIGHTBLUE);

	 setcolor(BLUE);

	 settextstyle(DEFAULT_FONT, HORIZ_DIR, 10);
	 outtextxy(130,130,"SNAKE");

	 settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
	 outtextxy(460,200,"THE GAME");

	 setcolor(DARKGRAY);

	 settextstyle(SMALL_FONT, HORIZ_DIR, 6);
	 outtextxy(470,450,"Omkar Pote 2014");



	 for(int a=200; a<=1000; a+=50)
	 {
		sound(a);
		delay(50);
	 }

	 delay(100);

	 nosound();


	 while(!(playStart))
	 {

	 setbkcolor(LIGHTBLUE);

	 setcolor(BLUE);

	 settextstyle(DEFAULT_FONT, HORIZ_DIR, 10);
	 outtextxy(130,130,"SNAKE");

	 settextstyle(SIMPLEX_FONT, HORIZ_DIR, 2);
	 outtextxy(460,200,"THE GAME");

	 setcolor(DARKGRAY);
	 if(tries)
	 {
		sprintf(highScoreStr,"High Score : %d",highScore);
		outtextxy(130,200,highScoreStr);
	 }

	 settextstyle(SMALL_FONT, HORIZ_DIR, 6);
	 outtextxy(470,450,"Omkar Pote 2014");


	 settextstyle(SMALL_FONT, HORIZ_DIR, 8);
	 menuKey = cursorMenu(firstMenu, 5) + 1;

	 switch(menuKey)
	 {
	 case 1 :
		playStart = 1;
		break;
	 case 2 :
		instruct();
		playStart = 0;
		break;
	 case 3 :
		selectSpeed();
		playStart = 0;
		break;
	 case 4 :
		selectLevel();
		playStart = 0;
		break;
	 case 5 :
		exit(1);
		break;
	 default :
		playStart = 0;
		break;
	 }

	 }

	 cleardevice();
}






//============================================================================================
// GAMEPLAY ==================================================================================
void gameplay()
{

	 // FOOD CREATION ENGINE

	 int futureX, futureY, futurePixel;

	 if(foodCount < 18)   //Adds food if no food is present, upto maximum 5oo food

	 {

		 int valid = 0;

		 int foodX;

		 int foodY;

		 while(!valid)
		 {

			 foodX = randomvalue(5,635);

			 foodY = randomvalue(5,475);

			 if((getpixel(foodX,foodY)!= BLUE)&&(getpixel(foodX,foodY)!= BROWN))

			 {

				 putpixel(foodX,foodY,RED);
				 putpixel(foodX+1,foodY,RED);
				 putpixel(foodX,foodY+1,RED);
				 putpixel(foodX+1,foodY+1,RED);

				 foodCount+=4;
			 }

				 valid = 1;

		 }

	 }


	 putpixel(5,5,RED);
	 putpixel(635,5,RED);
	 putpixel(5,475,RED);
	 putpixel(635,475,RED);

	 //FUTURE POSITION : Get future value of head in int variable futureX and futureY and calculate logic
	 futureX = snake.head_x;
	 futureY = snake.head_y;

	  if(snake.head_dir == LEFT)
		 futureX--;
	  if(snake.head_dir == RIGHT)
		 futureX++;
	  if(snake.head_dir == UP)
		 futureY--;
	  if(snake.head_dir == DOWN)
		 futureY++;

	 futurePixel = getpixel(futureX,futureY); // Gets the color of the futurePixel

	 // FOOD EATEN
	 if(futurePixel == RED)  //Food Eaten

	 {
		 // Score increase sound
		 sound(900);
		 delay(100);
		 sound(1200);
		 delay(500);
		 nosound();

		 // Wipe old score
		 setcolor(LIGHTBLUE);
		 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		 sprintf(scoreString, "Score: %d", score);
		 outtextxy(20,10, scoreString);
		 setcolor(LIGHTBLUE);
		 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		 sprintf(scoreString, "High Score: %d", highScore);
		 outtextxy(520,10, scoreString);

		 foodCount--; // Reduce food count

		 score++; // Increase score

		 if(highScore<score)
			highScore = score;

		 // Display new score
		 setcolor(DARKGRAY);
		 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		 sprintf(scoreString, "Score: %d", score);
		 outtextxy(20,10, scoreString);
		 if((tries)&&(highScore))
		 {
			sprintf(scoreString, "High Score: %d", highScore);
			outtextxy(520,10, scoreString);
		 }


		 // Increase the size of snake by 50 pixels
		 if(snake.tail_dir == UP)
		 {
			 for(i=0;i<=50;i++)
				putpixel(snake.tail_x,snake.tail_y+i,BLUE);

			 snake.tail_y +=50;
		 }
		  if(snake.tail_dir == DOWN)
		 {
			 for(i=0;i<=50;i++)
				putpixel(snake.tail_x,snake.tail_y-i,BLUE);

			 snake.tail_y -=50;
		 }
		  if(snake.tail_dir == LEFT)
		 {
			 for(i=0;i<=50;i++)
				putpixel(snake.tail_x+i,snake.tail_y,BLUE);

			 snake.tail_x +=50;
		 }
		 if(snake.tail_dir == RIGHT)
		 {
			 for(i=0;i<=50;i++)
				putpixel(snake.tail_x-i,snake.tail_y,BLUE);

			 snake.tail_x -=50;
		 }


		 if((score%10==0)||(timerBig%10==0))
		 {
			 do{

			 bonusX = randomvalue(5,635);
			 bonusY = randomvalue(5,475);

			 }while((getpixel(bonusX,bonusY)==BROWN)||(getpixel(bonusX,bonusY)==RED)||(getpixel(bonusX,bonusY)==BLUE));

			 putpixel(bonusX,bonusY,MAGENTA);
			 putpixel(bonusX+1,bonusY,MAGENTA);
			 putpixel(bonusX,bonusY+1,MAGENTA);
			 putpixel(bonusX+1,bonusY+1,MAGENTA);

		 }
		 else if(score%10!=0)
		 {
			 putpixel(bonusX,bonusY,LIGHTBLUE);
			 putpixel(bonusX+1,bonusY,LIGHTBLUE);
			 putpixel(bonusX,bonusY+1,LIGHTBLUE);
			 putpixel(bonusX+1,bonusY+1,LIGHTBLUE);

		 }


	 }

	 // SNAKE BITES ITSELF
	 if((futurePixel == BLUE)||(futurePixel == BROWN))
	 {
		gameOver();
	 }


	 if(futurePixel == MAGENTA)  //Food Eaten

	{
		 // Score increase sound

		 sound(800);
		 delay(75);

		 sound(900);
		 delay(100);

		 sound(1200);
		 delay(100);

		 sound(1000);
		 delay(50);

		 sound(1200);
		 delay(100);

		 sound(1000);
		 delay(50);

		 sound(1200);
		 delay(500);

		 nosound();

		 // Wipe old score
		 setcolor(LIGHTBLUE);
		 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		 sprintf(scoreString, "Score: %d", score);
		 outtextxy(20,10, scoreString);
		 setcolor(LIGHTBLUE);
		 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		 sprintf(scoreString, "High Score: %d", highScore);
		 outtextxy(520,10, scoreString);

		 score+=10; // Increase score

		 if(highScore<score)
			highScore = score;

		 // Display new score
		 setcolor(DARKGRAY);
		 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
		 sprintf(scoreString, "Score: %d", score);
		 outtextxy(20,10, scoreString);
		 if((tries)&&(highScore))
		{
			sprintf(scoreString, "High Score: %d", highScore);
			outtextxy(520,10, scoreString);
		}
	}

	timerBig = timer / 100;

	if((timer%100)==0)
	{

	 setcolor(LIGHTBLUE);
	 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	 sprintf(timeString, "Time : %d", (100 - (timerBig - 1)));
	 outtextxy(100,10, timeString);

	 setcolor(DARKGRAY);
	 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	 sprintf(timeString, "Time : %d", (100 - timerBig));
	 outtextxy(100,10, timeString);

	}

	if(timerBig == 100)
	{
		gameOver();
	}

}






//============================================================================================
// USER INPUT FUNCTION : this function changes the direction of the motion of snake according to input
void userInput()
{
	 // KEY IS PRESSED (in buffer)
	 if(kbhit())
	 {
		 input = getch();

		 // Change respective input according to arrow key pressed

		 if(input == 80) input = DOWN;

		 if(input == 72) input = UP;

		 if(input == 75) input = LEFT;

		 if(input == 77) input = RIGHT;



		 // Change head direction based on Logic
		 if(input==LEFT && snake.head_dir!=RIGHT && snake.head_dir!=LEFT)
		 {
			 snake.head_dir = LEFT;

			 snake.bend_x[bendNum] = snake.head_x;

			 snake.bend_y[bendNum] = snake.head_y;

			 snake.bend_dir[bendNum] = LEFT;

			 bendNum++;
		 }
		 if(input==RIGHT && snake.head_dir!=LEFT && snake.head_dir!=RIGHT)
		 {
			 snake.head_dir = RIGHT;

			 snake.bend_x[bendNum] = snake.head_x;

			 snake.bend_y[bendNum] = snake.head_y;

			 snake.bend_dir[bendNum] = RIGHT;

			 bendNum++;
		 }
		 if(input==UP && snake.head_dir!=DOWN && snake.head_dir!=UP)
		 {
			 snake.head_dir = UP;

			 snake.bend_x[bendNum] = snake.head_x;

			 snake.bend_y[bendNum] = snake.head_y;

			 snake.bend_dir[bendNum] = UP;

			 bendNum++;
		 }
		 if(input==DOWN && snake.head_dir!=UP && snake.head_dir!=DOWN)
		 {
			 snake.head_dir = DOWN;

			 snake.bend_x[bendNum] = snake.head_x;

			 snake.bend_y[bendNum] = snake.head_y;

			 snake.bend_dir[bendNum] = DOWN;

			 bendNum++;
		 }
	 }



	 // Change the y direction at respective time
	 if(snake.tail_x == snake.bend_x[bendNum2] && snake.tail_y == snake.bend_y[bendNum2])
	 {
		 snake.tail_dir = snake.bend_dir[bendNum2];
		 bendNum2++;
	 }
}






//============================================================================================
// SNAKE MOVEMENT FUNCTION ===================================================================
void moveSnake()
{
	 // Move the Head

	 if(snake.head_dir == LEFT)
		 snake.head_x--;

	 if(snake.head_dir == RIGHT)
		 snake.head_x++;

	 if(snake.head_dir == UP)
		 snake.head_y--;

	 if(snake.head_dir == DOWN)
		 snake.head_y++;

	  putpixel(snake.head_x,snake.head_y,BLUE);

	  // Move the Tail
	   putpixel(snake.tail_x,snake.tail_y,LIGHTBLUE);
	   if(snake.tail_dir == LEFT)
		   snake.tail_x--;

	   if(snake.tail_dir == RIGHT)
		   snake.tail_x++;

	   if(snake.tail_dir == UP)
		   snake.tail_y--;

	   if(snake.tail_dir == DOWN)
		   snake.tail_y++;

}






//============================================================================================
// GAME ENGINE ===============================================================================
void gameEngine()
{
	 while(1)
	 {
			 moveSnake();

			 userInput();

			 gameplay();

			 if(breakKey)
			 {
				break;
			 }

			 timer++;

			 delay(speed);
	 }
}






//============================================================================================
// INITIAL SCREEN FUNCTION : Draw initial game screen ========================================
void initScreen()
{
	 int i;
	 setbkcolor(LIGHTBLUE);


	 // Draw Boundary
	 setcolor(BROWN);
	 dotHor(0,640,0,2);
	 dotHor(2,638,2,2);
	 dotHor(0,640,480,2);
	 dotHor(2,638,478,2);

	 dotVer(0,480,0,2);
	 dotVer(2,478,2,2);
	 dotVer(0,480,640,2);
	 dotVer(2,478,638,2);


	 switch(level)
	 {
	 case 2 :
		dotVer(360,120,320,2);
		break;
	 case 3 :
		dotVer(355,125,150,2);
		dotVer(355,125,490,2);
		dotHor(205,435,360,2);
		dotHor(205,435,120,2);
		break;
	 case 4 :
		dotVer(359,120,320,2);
		dotHor(190,450,360,2);
		dotHor(190,450,120,2);
		break;
	 case 5 :
		dotVer(randomvalue(5,475),randomvalue(5,475),randomvalue(5,635),2);
		dotVer(randomvalue(5,475),randomvalue(5,475),randomvalue(5,635),2);
		dotHor(randomvalue(5,635),randomvalue(5,635),randomvalue(5,475),2);
		dotHor(randomvalue(5,635),randomvalue(5,635),randomvalue(5,475),2);
		break;
	 default :
		break;
	 }

	 // Draw initial snake Body
	 for(i=snake.length;i>0;i--)
			 putpixel(snake.head_x-i,snake.head_y,BLUE);


	 // Display initial score
	 score=0;
	 setcolor(DARKGRAY);
	 settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
	 sprintf(scoreString, "Score: %d", score);
	 outtextxy(20,10, scoreString);
	 if(tries)
		 {
			sprintf(scoreString, "High Score: %d", highScore);
			outtextxy(520,10, scoreString);
		 }

}






//============================================================================================
// INITIAL GAME DATA =========================================================================
void initGameData()
{
	 breakKey = 0;
	 foodCount = 0;
	 bendNum = 0;
	 bendNum2 = 0;

	 cursor = 0;

	 timer = 0;

	 snake.length = 100;

	 snake.head_x = 200;

	 snake.head_y = 200;

	 snake.head_dir = RIGHT;

	 snake.tail_x = snake.head_x - snake.length;

	 snake.tail_y = snake.head_y;

	 snake.tail_dir = snake.head_dir;

	 for(i=0;i<1000;i++)

	 {

			 snake.bend_x[i] = 0;   //there is no bend initially

			 snake.bend_y[i] = 0;

			 snake.bend_dir[i] = 0;

	 }

	 score = 0;


}












//============================================================================================
//                ============================================================================
// MAIN FUNCTION  ============================================================================
//                ============================================================================
//============================================================================================

void main()
{

	clrscr();

	int gdriver = DETECT, gmode;

	initgraph(&gdriver, &gmode, "C:\\TC\\BGI");


	// GRAPHICS ERROR
	int errorcode = graphresult();
	if (errorcode != grOk)
	{
	printf("Graphics error: %s\n", grapherrormsg(errorcode));
	printf("Press any key to halt:");
	getch();
	exit(1);
	}

	tries = 0;

	while(1)
	{

	cleardevice();

	mainMenu();

	initGameData();

	initScreen();

	gameEngine();

	tries++;

	}
}