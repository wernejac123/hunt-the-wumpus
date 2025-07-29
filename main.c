#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fisher_yates.h"
#include "cave.h"

#define ROOMS 20
#define MAX_STRING 30

size_t n = ROOMS;
int *arr;
int you, wumpus, pit1, pit2, bat1, bat2;
int arrows;
int randTunnel;
enum Status {SLEEP, AWAKE};
enum Status wump;
static char input[MAX_STRING]; 

int* gen_arr(size_t n){
	int *arr = (int*)malloc(sizeof(int) * n);

	if(arr== NULL){
		fprintf(stderr, "Error:memory failed to allocate\n");
		exit(EXIT_FAILURE); 
	}

	for(size_t i= 0; i < n; i++)
		arr[i] = (int)i;

	return arr;
}

int randNum(int lower, int upper){
        return ((rand() % (upper - lower + 1)) + lower);
}

void debug_print(){
	printf("you=%d wumpus=%d pit1=%d pit2=%d bat1=%d bat2=%d\n", you, wumpus, pit1, pit2, bat1, bat2);
	if(wump == 0)
		printf("status:sleep\n");
	else
		printf("status:awake\n");

	printf("\n");
}

void instructions(void){
        //modified text to match changes I made to game
        system("clear");
        printf("Welcome to 'Hunt the Wumpus'\n");
        printf("\tThe Wumpus lives in a cave of 20 rooms. Each room\n");
        printf("has 3 tunnels leading to other rooms. (Look at a\n");
        printf("dodecahedron to see how this works-If you don't know\n");
        printf("what a dodecahedron is, ask someone).\n\n");
        printf("\tHazards:\n");
        printf("Bottomless Pits - two rooms have bottomless pits in them.\n");
        printf("\tIf you go there, you fall into the pit (& lose!)\n");
        printf("Super Bats - two other rooms have super bats. If you\n");
        printf("\tGo there, a bat grabs you and takes you to some other\n");
        printf("\troom at random. (Which might be troublesome)\n");
        printf("Wumpus:\n");
        printf("\tThe Wumpus is not bothered by the hazards (he has sucker\n");
        printf("\tfeet and is too big for a bat to lift). Usually\n");
        printf("\tHe is asleep. Only one thing wake him up: your entering\n");
        printf("\this room.\n");
        printf("\tIf the Wumpus wakes, he moves (p=.75) one room\n");
        printf("\tor stays still (p=.25). After that, if he is where you\n");
        printf("are, he eats you up (& you lose!)\n\n");
        printf("You:\n");
        printf("\tEach turn you may move or shoot a crooked arrow\n");
        printf("Moving: You can go one room (thru one tunnel)\n");
        printf("Arrows: you have 5 arrows. you lose when you run out.\n");
        printf("\tIn this version of 'Hunt the Wumpus', arrows can only go 1 room. You\n");
        printf("\taim by telling the computer the room# you want the arrow to go to.\n");
        printf("\tAlso in this version, arrows can only go into connecting rooms to you.\n");
        printf("\tYou can not shoot youreself either\n");
        printf("\tIf the arrow hits the Wumpus, you win.\n\n");
        printf("Warnings:\n");
        printf("\tWhen you are one room away from Wumpus or hazard,\n");
        printf("\tthe computer says:\n");
        printf("Wumpus-  'I smell a Wumpus'\n");
        printf("Bat   -  'Bats nearby'\n");
        printf("Pit   -  'I feel a draft'\n\n");
}


void hazards(void){
        //check for hazards
        int wumpMove; //random number between 1-4
        //1 stays sill 2-4 moves

        if((you == wumpus) && (wump == SLEEP)){
                printf("Oops! Bumped a Wumpus!\n");
                wump = AWAKE;

                //.25 chance  he stays still, .75 chance he moves
                wumpMove = randNum(1,4);
                if(wumpMove > 1){
                        randTunnel = randNum(0,2);
                        wumpus = cave[wumpus][randTunnel];
                }
        }
        else if((you == wumpus) && (wump == AWAKE)){
                printf("Tsk tsk tsk- Wumpus got you!\n");
                exit(EXIT_SUCCESS);
        }
        else if((you == pit1) || (you == pit2)){
                printf("YYYIIIIEEEE . . . fell in pit\n");
                exit(EXIT_SUCCESS);
        }
        else if((you == bat1) || (you == bat2)){
                printf("Zap--Super Bat snatch! Elsewhereville for you!\n");
                you = randNum(0,19); //bats can move you into rooms with
                //hazards
        }
}

void move(void){
        while(1){
                printf("Where to\n");
                fgets(input, sizeof(input), stdin);

                //check if legal move (has a tunnel to it)
                if((atoi(input) == cave[you][0]) || (atoi(input) == cave[you][1]) ||
                (atoi(input) == cave[you][2])){
                        you = atoi(input);
                        break;
                }
                else{
                        printf("Not possible\n");
                        continue;
                }
        }

        //check for hazards
        hazards();
}

void warnings(void){
        //print warnings
        int i =0;
        while(i < 3){
                if(wumpus == cave[you][i])
                        printf("I smell a Wumpus!\n");
                else if((pit1 == cave[you][i]) || (pit2 == cave[you][i]))
                        printf("I feel a draft\n");
                else if((bat1 == cave[you][i]) || (bat2 == cave[you][i]))
                        printf("Bats nearby!\n");
                i++;
        }
}

void shoot(void){
        //determine room of arrow
        int room;

        while(1){
                printf("Room # ");
                fgets(input, sizeof(input), stdin);
                room = atoi(input);

                //check if arrow has path)
                if((room != cave[you][0]) && (room != cave[you][1]) &&
                (room != cave[you][2])){
                        printf("Invalid input\n");
                        continue;
                }
                else if(room != wumpus){
                        printf("Missed\n");
                        break;
                }
                else if(room == wumpus){
                        printf("Aha! You got the Wumpus\n");
                        exit(EXIT_SUCCESS);
                }
        }

        //Decrement arrows
        arrows -= 1;

        //lose if arrows run out
        if(arrows <= 0){
                printf("Ha ha ha - you lose!\n");
                exit(EXIT_SUCCESS);
        }
}

void moveWumpus(void){
        //wumpus can only move to connecting rooms to it
        //does so randomly
        randTunnel = randNum(0,2);
        wumpus = cave[wumpus][randTunnel];

        //since wumpus is not affected by other hazards, only check
        //wumpus position against yours
        //Note: wumpus can move directly into your room, causing you
        //to loose (if hes awake)
        if((you == wumpus) && (wump == SLEEP)){
                printf("Oops! Bumped a Wumpus!\n");
                wump = AWAKE;
        }
        else if((you == wumpus) && (wump == AWAKE)){
                printf("Tsk tsk tsk- Wumpus got you!\n");
                exit(EXIT_SUCCESS);
        }
}

int main(){
	//n = ROOMS;
	arr = gen_arr(n);
	//int you, wumpus, pit1, pit2, bat1, bat2;

	randomize(arr, n);
	you = arr[0];
	wumpus = arr[1];
	pit1 = arr[2];
	pit2 = arr[3];
	bat1 = arr[4];
	bat2 = arr[5];
	wump = SLEEP;
	arrows = 5;

	free(arr);
	system("clear");

	//instructiomss?
        while(1){
                printf("Instructions (y-n)\n");
                fgets(input, sizeof(input), stdin);
                if(strcmp(input, "y\n") ==0){
                	instructions();
                        break;
		}
                else if(strcmp(input, "n\n") == 0)
                	break;
		else{
                 	printf("Invalid input\n");
                	continue;
                }
        }

        //announce WumpusII for all aficianadoa ... added by Dave
        printf("\n\tAttention all Wumpus lovers!!!\n");
        printf("There are now two additions to the Wumpus family\n");
        printf("of programs.\n\n");
        printf("\tWump2: Some different cave arrangements\n");
        printf("\tWump3: Different hazards\n\n");

        printf("Hunt the Wumpus\n\n");

	//main loop of game
        while(1){
                printf("You have %d arrows\n", arrows);
                printf("You are in room %d\n", you);
                printf("Tunnels lead to ");
                for(int i = 0; i < 3; i++)
                        printf("%d;",cave[you][i]);
                printf("\n");

                //print warnings
                warnings();

                //shoot, move, or quit
                printf("Shoot, move, or quit (s-m-q)\n");
                fgets(input, sizeof(input), stdin);
		if(strcmp(input, "s\n") == 0)
                        shoot();
		else if(strcmp(input, "m\n") == 0)
                        move();
		else if(strcmp(input, "q\n")== 0)
			exit(EXIT_SUCCESS);
                else{
                	printf("Invalid option\n");
                       	continue;
                }
		moveWumpus();
		//debug_print();
	}

	return 0;
}
