//Harshit Goyal: 2203112
//Kunal: 2203116
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdint.h> 
#include <time.h> 
#include "gamestate.h"
#define N 4 //number of rows.

int main(){
	
	srand(time(NULL));
	printf("PID: %d\n", (int)getpid());
	
    int shmid = shmget((key_t)1234, sizeof(struct shared_struct), 0666 | IPC_CREAT);

    if (shmid == -1) {//check if shmid is done
        fprintf(stderr, "shmget failed\n");
        fprintf(stderr, "Error: %s\n", strerror(errno)); 
        exit(EXIT_FAILURE);
    }

	//attach
    void *shared_memory=shmat(shmid, (void *)0, 0);
    
    if (shared_memory==(void *)-1) {
        fprintf(stderr, "shm attach failed\n");
        fprintf(stderr, "Error: %s\n", strerror(errno)); 
        exit(EXIT_FAILURE);
    }
    
    
    struct shared_struct *shared_stuff = (struct shared_struct *)shared_memory;
    //initialize the game board.
    shared_stuff->coins_left=0;
    int c=1;//variable for coins in next row.
    for(int i=0;i<N;i++){
        shared_stuff->gamerows[i]=c;
        shared_stuff->coins_left+=c;
        c=c+2;
    }
    shared_stuff->player_turn=1;//set turn =1 for player 1 move.
    shared_stuff->gamestarter=1;//Game is now initialised.
    while(shared_stuff->coins_left!=0);//Wait till all coins are off the board.
    printf("Game has Ended.\n");

	
    // Delete
    if (shmctl(shmid, IPC_RMID, 0) == -1) { //Assuming shmid is the shared memeroy identifier
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        fprintf(stderr, "Error: %s\n", strerror(errno)); // Print error using strerror
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
