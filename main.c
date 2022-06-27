
/**
 * @file snl.h
 * @author Shelton Ngwenya, R00203947
 * @brief Snakes and Ladders Game
 */

#include "snl.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief
 * to compile: gcc -g main.c snl.c -lm -o main
 */

int main()
{
	//create a new number per seed
	srand(time(0));

	play_game();
	return (0);
}