//Kunal:2203116
//Harshit Goyal:2203112
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdint.h> 
#include <time.h> 
#include "gamestate.h"
#define N 4
void printing_gamestate(int a[]){//function for printing gameboard.
    for(int i=0;i<N;i++){
        printf("Row %d: ",i+1);
        for(int j=0;j<a[i];j++){
            printf("* ");
        }
        printf("\n");
    }
}
int main(){
	
    
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
	    
    while(shared_stuff->gamestarter != 1) {//wait for game to be initialised.
        sleep(1);
        if(rand()%20 == 0){
        	printf("\nWaiting for game to start\n\n");
    	}
    }     
    int done=0;//variable to help keep track of when game has finished.
    while(done==0){
        while(shared_stuff->player_turn==2){//other players turn
            sleep(1);
            if(rand()%20 == 0){
        	    printf("\nWaiting for PLayer 2 to play his move.\n\n");
    	    }
        }
        if(shared_stuff->coins_left==0){//after player 2 move if no more coins left then you lose.
            printf("Sorry! you lost as player2 removed all coins left.\n");
            done=1;
            break;
        }
        //Ask for move till a valid move after printing gamestate.
        int valid_input=0;
        while(valid_input==0 && done==0){
            printf("Game Board:\n");//print game board 
            printing_gamestate(shared_stuff->gamerows);
            int row_num,num_coins;
            //ask for players move.
            printf("Enter the row number(starting from 1) from which you want to remove:");
            scanf("%d",&row_num);
            if(row_num<1 || row_num>N){//validate input.
                printf("Invalid move or invalid input.");
                continue;
            }
            printf("Enter number of coins you would like to remove:");
            scanf("%d",&num_coins);
            if(num_coins<=0 || shared_stuff->gamerows[row_num-1]<num_coins){//validate input.
                printf("Invalid move or invalid input.");
                continue;
            }
            valid_input=1;//if reached here then valid input and do this move.
            shared_stuff->gamerows[row_num-1]-=num_coins;
            shared_stuff->coins_left-=num_coins;
            //print gamebord
            printf("Game Board After Your Move:\n");
            printing_gamestate(shared_stuff->gamerows);
            //check if after your move 0 coins left you win and game ends.
            if(shared_stuff->coins_left==0){
                printf("Great You Won!\n");
                shared_stuff->player_turn=2;
                done=1;
                break;
            }    
            shared_stuff->player_turn=2;  //after your valid move give turn to player2. 
        }
           
    }
    
}
