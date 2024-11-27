#define SIZE 50
#define SHM_KEY 1234 // key for the shared memory segment shared among all.

int *arr; //this is the return address by shared mmemory attach function and so it can serve as the base address of array

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdint.h> 
#include <time.h> 
#include <stdbool.h>
#define N 4
struct shared_struct{
    int gamerows[N];//game board
    int gamestarter;//Flag to check if game is initialised
    int player_turn;//Flag to store whose turn it is.
    int coins_left;//Variable to store number of coins left on board.
};
