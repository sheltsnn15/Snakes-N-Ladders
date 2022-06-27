#ifndef SNL_H_ // include guard
#define SNL_H_

/**
 * @file snl.h
 * @author Shelton Ngwenya, R00203947
 * @brief Snakes and Ladders Game
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MINIMUM_BOARD_SIZE 32
#define MAXIMUM_BOARD_SIZE 64
#define MINIMUM_SL_SIZE 1
#define MAXIMUM_SL_SIZE 10
#define FILE_NAME "game_play_report.txt"

//board node object struct
typedef struct _b
{
    int node_pos; // value to be stored in node
    int length;
    int is_snake, is_ladder;
    struct _b *next; // pointer to next node
} board_node;

//visited board node object struct
typedef struct _c
{
    int number; // value to be stored in node
    int dice_roll;
    int new_node_pos;
    int old_player_pos;
    board_node bn;
    struct _c *next; // pointer to next node
} path_taken_node;

// access head and tail of linked list
// this allocated memory will remain the same throught the program

void lines(int size);
int menu();
void get_num_snakes_ladders();
int random_generator(int min, int max);
void write_2_file(path_taken_node *ptn_head);
void create_board();
board_node *create_board_node(int number);
void print_board(board_node *head);
void snake_scenario(board_node *cursor);
void ladder_scenario(board_node *cursor);
void insert_snake(int index);
void insert_ladder(int index);
int is_oob_ladder_length (int length, int node_pos);
int is_oob_snake_length (int length, int node_pos);
int has_won();
board_node *search_node(int node_input);
int is_occupied_ladder(int index);
void move_player();
void play_game();
void slight_pause();
path_taken_node *record_player_path(int dice_roll, int old_pos, int new_pos, board_node *passed_bn);
void create_player_path_list(int dice_roll, int old_pos, int new_pos, board_node *passed_bn);
void print_path_list(path_taken_node *head);

#endif
