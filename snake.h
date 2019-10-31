#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#ifndef SNAKE_H
#define SNAKE_H

// sections of the snake
struct snakepart {
	int x,y;
	snakepart(int x, int y);
	snakepart();
};

class snakeclass {
	int points;
	int del;
	// snake eats food
	bool hasFood;
	//indicates the current direction of the snake
	char direction;

	int maxwidth;
	int maxheight;
	char snakeChar;
	char borderChar;
	char foodChar;
	snakepart food;
	std::vector<snakepart> snake; // vector of snakeparts

	// prints food
	void printfood();

	// true when snake has collided and lost and false when snake eats food
	bool hasLost();

	// moves snake in direction it is facing
	void movesnake();
	
public:
	snakeclass();
	~snakeclass();
	void start();
};

#endif