
/**
 * @file snl.h
 * @author Shelton Ngwenya, R00203947
 * @brief Snakes and Ladders Game
 */

#include "snl.h"// Include the header (not strictly necessary here)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int linked_list_size, num_snakes, num_ladders;
int player_pos, player_node_index;
board_node *bn_head, *bn_tail;
path_taken_node *ptn_head, *ptn_tail;

/**
 * @brief Get '-' string
 *
 * @param size
 * @return char*
 */
void lines(int size)
{
    for (int i = 0; i < size; i++)
        printf("-");
}

/**
 * @brief Display menu and see if user wants to play
 *
 * @return int
 */

int menu()
{
    int choice;
    lines(20);
    printf("Welcome");
    lines(20);
    printf("\n[1] Play\n");
    printf("[2] Exit\n______");
    scanf("%d", &choice);
    return choice;
}

/**
 * @brief Implement slight pause between operations
 *
 */
void slight_pause()
{

    printf("\n");
    for (int i = 0; i < 1; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            printf("\rNext move%.*s   \b\b", j, "..");
            fflush(stdout); // force printing as no newline in output
            sleep(1);       // one sec pause
        }
    }
    printf("\n");
}

/**
 * @brief Create a random number between Min(32) & Max(64)
 * @param minimum number
 * @param maximum number
 * @return int
 */
int random_generator(int min, int max)
{
    return min + rand() % (max + 1 - min);
}

/**
 * @brief Create a board node object
 *
 * @param index board node
 * @return board_node*
 */
board_node *create_board_node(int index)
{
    // create a var to store new node obj
    board_node *new_node = (board_node *)malloc(sizeof(board_node));
    // assign new node obj variables
    new_node->node_pos = index;
    new_node->next = NULL;
    return new_node;
}

/**
 * @brief Create a board object
 */
void create_board()
{
    linked_list_size = random_generator(MINIMUM_BOARD_SIZE, MAXIMUM_BOARD_SIZE);
    int board_node_num = 1;
    int counter = 0;

    // create a board of size n
    while (counter < linked_list_size)
    {
        // iteratively assign a new node into the board
        board_node *new_node = create_board_node(board_node_num++);

        // if the list is empty
        if (bn_head == bn_tail && bn_tail == NULL)
        {
            // set head and tail to be new node
            bn_head = bn_tail = new_node;
        }
        else
        {
            // add newnode after tail, then point to new node
            bn_tail->next = new_node;
            // set tail to become new node
            bn_tail = new_node;
        }
        // guard to not exceed board size
        counter++;
    }
    printf("\nNew Board Created\n");
}

/**
 * @brief Print board
 *
 * @param head board node
 */
void print_board(board_node *head)
{
    int count = 0, row_counter = 1;
    int width = 10, line_width = 185;

    lines(line_width);
    printf("\n");
    // check if next node is empty
    while (head != NULL)
    {
        count++;
        // get value in that node
        printf("|%*s %d, length = %d, is_snake = %d, is_ladder = %d%*s", width, "node_", head->node_pos, head->length, head->is_snake, head->is_ladder, width / 2, "");

        // print board in rows of 3
        if (count == 3)
        {
            printf("|\n");
            count = 0;
            lines(line_width);
            printf("\n");
        }
        // go to the next node
        head = head->next;
    }
    printf("|\n");
    lines(line_width);
    printf("\n");
}

/**
 * @brief Get the num snakes ladders from user
 *
 */
void get_num_snakes_ladders()
{
    num_snakes, num_ladders;
    printf("Enter number of snakes [0-10]: ");
    scanf("%d", &num_snakes);
    printf("Enter number of ladders [0-10]: ");
    scanf("%d", &num_ladders);
}

/**
 * @brief Insert snake into board nodes
 *@param index board node
 */
void insert_snake(int index)
{
    board_node *temp = search_node(index);
    int length;
    int is_oob_snake = -1;
    do
    {
        length = random_generator(MINIMUM_SL_SIZE, MAXIMUM_SL_SIZE);
        is_oob_snake = is_oob_snake_length(length, temp->node_pos);
    } while (is_oob_snake == 1);

    temp->is_snake = 1;
    temp->length = length;
    printf("\tPos = %d, Length = %d\n", index, length);
}

/**
 * @brief Check if snake length is out of bounds
 *
 * @param length
 * @param node_pos
 * @return int
 */
int is_oob_snake_length(int length, int node_pos)
{
    int result = node_pos - length;
    if (result < 1) // printf("Failure at pos %d length %d", node_pos, length);
        return 1;
    else
        return 0;
    // printf("Success at pos %d length %d", node_pos, length);
}

/**
 * @brief Decrease player position if they are in snake containing node
 *
 * @param node_pos
 */
void snake_scenario(board_node *cursor)
{
    if (cursor->is_snake == 1)
    {
        printf("\nSnake Scenario, Player Position Decline = %d", cursor->length);
        player_pos -= cursor->length;
        printf("\nNew Player Position: %d", player_pos);
    }
}

/**
 * @brief Method to check if node is not occupied
 *
 * @param index
 * @return int
 */
int is_occupied_ladder(int index)
{
    // search node and return
    board_node *temp = search_node(index);
    if (temp->is_ladder == 1)
    {
        printf("Is Occupied at pos %d", index);
        return 1;
    }
    else
        return 0;
}

/**
 * @brief insert ladder into board node object
 *
 * @param index
 *
 */
void insert_ladder(int index)
{
    // search for the board node object
    board_node *temp = search_node(index);
    int length;
    int is_oob_ladder = -1;
    do
    {
        length = random_generator(MINIMUM_SL_SIZE, MAXIMUM_SL_SIZE);
        is_oob_ladder = is_oob_ladder_length(length, temp->node_pos);
    } while (is_oob_ladder == 1);

    temp->is_ladder = 1;
    temp->length = length;
    printf("\tPos = %d, Length = %d\n", index, length);
}

/**
 * @brief Check if ladder leads to out of bounds
 *
 * @param length
 * @param node_pos
 * @return int
 */
int is_oob_ladder_length(int length, int node_pos)
{
    int result = node_pos + length;
    if (result > linked_list_size) // printf("Failure at pos %d length %d", node_pos, length);
        return 1;
    else
        return 0;
    // printf("Success at pos %d length %d", node_pos, length);
}

/**
 * @brief increase player position if reached ladder containing node
 *
 * @param node_pos
 */
void ladder_scenario(board_node *cursor)
{
    if (cursor->is_ladder == 1)
    {
        printf("\nLadder Scenario, Player Position Boost = %d", cursor->length);
        player_pos += cursor->length;
        printf("\nNew Player Position: %d", player_pos);
    }
}

/**
 * @brief Move player on each dice roll
 */
void move_player()
{
    // simlate a dice roll
    int dice_roll = random_generator(1, 6);
    // store our player move
    int temp_player_pos = player_pos + dice_roll;
    // check if move is valid
    if (temp_player_pos > linked_list_size)
    {
        printf("\nDice Roll: %d Move Invalid", dice_roll);
    }
    else
    {
        printf("\nDice Roll: %d", dice_roll);
        int old_player_pos = player_pos;
        player_pos += dice_roll;

        printf("\nOld Player Position: %d", old_player_pos);
        printf("\nNew Player Position: %d", player_pos);

        // search for the node that is equal to the player move
        board_node *cursor = search_node(player_pos);
        // check if we either have a ladder or snake scenario
        ladder_scenario(cursor);
        snake_scenario(cursor);
        // add the move to the linklist of player moves
        create_player_path_list(dice_roll, old_player_pos, player_pos, cursor);
    }
}

/**
 * @brief Search board node
 *
 * @param index node
 * @return board_node*
 */
board_node *search_node(int index)
{
    // check if the list is not empty
    if (bn_head != NULL)
    {
        // set the cursor to point to the head of the linklist
        board_node *cursor = bn_head;
        // iterate throught the linklist while valid
        while (cursor != NULL && cursor->node_pos != index)
            // set the cursor to next node
            cursor = cursor->next;
        return cursor;
    }
    else
        return NULL;
}

/**
 * @brief
 *
 * @param index
 * @param dice_roll
 * @param new_pos
 * @param passed_bn
 * @return path_taken_node*
 */
path_taken_node *record_player_path(int dice_roll, int old_pos, int new_pos, board_node *passed_bn)
{
    // allocate memory by the size of our data structure
    path_taken_node *new_node = (path_taken_node *)malloc(sizeof(path_taken_node));
    new_node->number = player_node_index++;
    new_node->dice_roll = dice_roll;
    new_node->old_player_pos = old_pos;
    new_node->new_node_pos = new_pos;
    new_node->bn = *passed_bn;
    new_node->next = NULL;
    return new_node;
}

void create_player_path_list(int dice_roll, int old_pos, int new_pos, board_node *passed_bn)
{
    int board_node_num = 1;
    int counter = 0;

    path_taken_node *new_node = record_player_path(dice_roll, old_pos, new_pos, passed_bn);

    // if the list is empty
    if (ptn_head == ptn_tail && ptn_tail == NULL)
    {
        // set head and tail to be new node
        ptn_head = ptn_tail = new_node;
    }
    else
    {
        // add newnode after tail, then point to new node
        ptn_tail->next = new_node;
        // set tail to become new node
        ptn_tail = new_node;
    }
}

/**
 * @brief Method to 
 * 
 * @param head 
 */
void print_path_list(path_taken_node *head)
{
    int count = 0, row_counter = 1;
    int width = 8, line_width = 195;

    lines(line_width);
    printf("\n");
    // check if next node is empty
    while (head != NULL)
    {
        count++;
        // get value in that node
        printf("|%*s %d, node_%d, length = %d, is_snake = %d, is_ladder = %d%*s",
               width, "path_", head->number, head->bn.node_pos, head->bn.length, head->bn.is_snake, head->bn.is_ladder, width / 2, "");
        //%*d %d\n\n
        if (count == 3)
        {
            printf("|\n");
            count = 0;
            lines(line_width);
            printf("\n");
        }
        // go to the next node
        head = head->next;
    }
    printf("|\n");
    lines(line_width);
    printf("\n");
}

/**
 * @brief Method to play game
 *
 */
void play_game()
{
    srand(time(NULL));
    int try_again = 0;
    int menu_pick = 0;

    do
    {
        menu_pick = menu();
        switch (menu_pick)
        {
        case 1:
            create_board();
            printf("\nBoard Size: %d\n", linked_list_size);
            get_num_snakes_ladders();

            printf("\nSnakes inserted\n");
            for (int i = 0; i < num_ladders; i++)
            {
                int rand_ladder_insert = random_generator(2, linked_list_size - 1);
                insert_ladder(rand_ladder_insert);
            }
            printf("\nLadders inserted\n");

            for (int i = 0; i < num_snakes; i++)
            {
                int rand_snake_insert;
                int is_occupied = -1;
                do
                {
                    rand_snake_insert = random_generator(2, linked_list_size - 1);
                    insert_snake(rand_snake_insert);
                    is_occupied = is_occupied_ladder(rand_snake_insert);
                } while (is_occupied == 1);
            }
            printf("\nNew Board\n\n");
            print_board(bn_head);

            do
            {
                move_player();
                slight_pause();
            } while (has_won() == 0);
            //print_path_list(ptn_head);
            write_2_file(ptn_head);
            break;
        case 2:
            exit(0);

        default:
            try_again = 1;
            printf("\nInput incorrect, try again\n");
        }
    } while (try_again == 1);
    // printf("\nyep %d", search_node(16));
}

/**
 * @brief Method to check if player has won
 *
 * @return int
 */
int has_won()
{
    // check if player move is at the last node in the board
    if (player_pos == linked_list_size)
    {
        printf("Player has won\n");
        return 1;
    }
    else
        return 0;
}

/**
 * @brief
 *
 */
void write_2_file(path_taken_node *ptn_head)
{
    FILE *file = fopen(FILE_NAME, "w");
    // check if file was created
    if (file == NULL)
    {
        printf("File Creation Unsuccessful");
        return;
    }
    else
    {
        // create a new cursor of type path taken link list
        path_taken_node *cursor = ptn_head;
        fprintf(file, "Board Size: %d\n\nPlayer Path:\n", linked_list_size);
        // loop the link list
        while (cursor->next != NULL)
        {
            // use cursor to access info i the path taken node link list and print to file
            fprintf(file, "\nPath No.: %d\nPrev Node Pos: %d\nDice Roll: %d\nNew Node Pos: %d\nLength: %d\nIs Ladder: %d\nIs Snake: %d\n\n",
                    cursor->number, cursor->old_player_pos, cursor->dice_roll, cursor->new_node_pos, cursor->bn.length, cursor->bn.is_ladder, cursor->bn.is_snake);

            // move cursor to next node
            cursor = cursor->next;
        }
    }
    fclose(file);

    printf("\nFile created\nPlayer Moves saved successfully. :) \n");
}
