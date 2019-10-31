#include "snake.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

snakepart::snakepart(int x,int y): x{x}, y{y}{}

snakeclass::snakeclass(): snakeChar{'X'}, borderChar{'N'}, foodChar{'*'}, food{snakepart{0, 0}},
							points{0}, del{100000}, hasFood{false}, direction{'l'}
{
	initscr();
	keypad(stdscr,true);
	nodelay(stdscr,true);		
	noecho();
	curs_set(0);
	getmaxyx(stdscr,maxheight,maxwidth);

	srand(time(NULL));
	printfood();
	// prints board 
	// top
	for(int i=0;i<maxwidth-1;i++)
	{
		move(1,i);
		addch(borderChar);
	}
	// left
	for(int i=0;i<maxheight-1;i++)
	{
		move(i,0);
		addch(borderChar);
	}
	// bottom
	for(int i=0;i<maxwidth-1;i++)
	{
		move(maxheight-1,i);
		addch(borderChar);
	}
	// right
	for(int i=0;i<maxheight-1;i++)
	{
		move(i,maxwidth-1);
		addch(borderChar);
	}

	// create snake
	for(int i=0;i<5;i++) {
		snake.push_back(snakepart(40+i,15)); 
	}

	// print snake
	for(int i=0;i<snake.size();i++)
	{
		move(snake[i].y,snake[i].x);
		addch(borderChar);
	}

	move(0,0);
	printw("points: %d",points);
	move(food.y,food.x);
	addch(foodChar);
	refresh();
}

snakeclass::~snakeclass() {
	nodelay(stdscr,false);
	getch();		
	endwin();
}

void snakeclass::printfood() {
	while(1)
        {
                int tmpx=rand()%(maxwidth-2)+1;
                int tmpy=rand()%(maxheight-3)+2;
                for(int i=0;i<snake.size();i++)
                        if(snake[i].x==tmpx && snake[i].y==tmpy)
                                continue;
                food.x=tmpx;
                food.y=tmpy;
                break;
        }
        move(food.y,food.x);
        addch(foodChar);
        refresh();
}

bool snakeclass::hasLost() {
	// collision with wall
	if(snake[0].x==0 || snake[0].x==maxwidth-1 || snake[0].y==1 || snake[0].y==maxheight-1)
		return true;
	// collision with self
	for(int i=2;i<snake.size();i++)
	{
		if(snake[0].x==snake[i].x && snake[0].y==snake[i].y)
			return true;
	}
	//collision with the food
	if(snake[0].x==food.x && snake[0].y==food.y)
	{
		hasFood = true;
		printfood();
		points+=10;
		move(0,0);
		printw("points: %d",points);
		if((points%100)==0)
			del-=20000;
	}else
		hasFood=false;
	return false;
}


void snakeclass::movesnake() {
	int tmp=getch();
	switch(tmp)
	{
		case KEY_LEFT:
			if(direction!='r')
				direction='l';
			break;
		case KEY_UP:
			if(direction!='d')
				direction='u';
			break;
		case KEY_DOWN:
			if(direction!='u')
				direction='d';
			break;
		case KEY_RIGHT:
			if(direction!='l')
				direction='r';
			break;
	}
	//if no collision with food
	if(!hasFood)
	{
		move(snake[snake.size()-1].y,snake[snake.size()-1].x);
		printw(" ");
		refresh();
		snake.pop_back();
	}
	if(direction=='l'){
		snake.insert(snake.begin(),snakepart(snake[0].x-1,snake[0].y));
	}else if(direction=='r'){
		snake.insert(snake.begin(),snakepart(snake[0].x+1,snake[0].y));

	}else if(direction=='u'){
		snake.insert(snake.begin(),snakepart(snake[0].x,snake[0].y-1));
	}else if(direction=='d'){
		snake.insert(snake.begin(),snakepart(snake[0].x,snake[0].y+1));
	}
	move(snake[0].y,snake[0].x);
	addch(snakeChar);
	refresh();
}

void snakeclass::start() {
	while(1)
	{
		if(hasLost())
		{
			move((maxheight - 2) / 2, (maxwidth / 2 - 10));
			printw("GAME OVER");
			refresh();
			break;
		}
		movesnake();
		usleep(del);
	}
}