#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "maze.h"

Maze::Maze(int initX, int initY, int* maze, int Xsize, int Ysize, int Xend, int Yend){
	initLocation[0]=curLocation[0]= initX;
	initLocation[1]=curLocation[1]= initY;
	mazeX= Xsize;
	mazeY= Ysize;
	
	this->maze=(int**) malloc(sizeof(int*)* Xsize);
	for(int i=0; i<Xsize; i++){
		this->maze[i]= (int*) malloc(sizeof(int)* Ysize);
	}
	for(int i=0; i<Ysize; i++){
		for(int k=0; k<Xsize; k++){
			this->maze[i][k]= maze[i*Xsize+k];
		}
	}
	endLocation[0]= Xend;
	endLocation[1]= Yend;
};

void Maze::printMaze(){
	for(int i=0; i<mazeY; i++){
		for(int k=0; k<mazeX; k++){
			if(curLocation[0]== k && curLocation[1]== i){
				printf("£¦");
			}
			else if(maze[i][k]== 0){
				printf("¡¤");
			}
			else if(maze[i][k]== 1){
				printf("¡á");
			}
			else if(maze[i][k]== 2){
				printf("¡Þ");
			}
		}
		printf("\n");
	}
};

void Maze::GetLastLoc(int* xoutput, int* youtput, int* Path, int PathSize){
	curLocation[0]= initLocation[0];
	curLocation[1]= initLocation[1];
	for(int i=0; i< PathSize-1; i+=2){
		if(Path[i]== 0&& Path[i+1]== 0){
			maze[curLocation[1]][curLocation[0]]= 2;
			if((maze[curLocation[1]][curLocation[0]+1]== 1)|| curLocation[0]+1==mazeX){
				break;
			}
			curLocation[0]++;
		}
		else if(Path[i]== 0&& Path[i+1]== 1){
			maze[curLocation[1]][curLocation[0]]= 2;
			if(curLocation[0]-1== -1 || (maze[curLocation[1]][curLocation[0]-1]== 1)){
				break;
			}
			curLocation[0]--;
		}
		else if(Path[i]== 1&& Path[i+1]== 0){
			maze[curLocation[1]][curLocation[0]]= 2;
			if((maze[curLocation[1]+1][curLocation[0]]== 1)||curLocation[1]+1==mazeY){
				break;
			}
			curLocation[1]++;
		}
		else if(Path[i]== 1&& Path[i+1]== 1){
			maze[curLocation[1]][curLocation[0]]= 2;
			if(curLocation[1]-1== -1 || (maze[curLocation[1]-1][curLocation[0]]== 1)){
				break;
			}
			curLocation[1]--;
		}
	}
	(*xoutput)= curLocation[0];
	(*youtput)= curLocation[1];

	if(curLocation[0]== endLocation[0]&& curLocation[1]== endLocation[1]){
		printMaze();
	}
	
	for(int i=0; i< mazeX; i++){
		for(int k=0; k<mazeY; k++){
			if(maze[k][i]== 2){
				maze[k][i]= 0;
			}
		}
	}
}

int Maze::GetAdaption(int* location){
	return (int)100*(abs((float)1/(abs(endLocation[0]-location[0])+abs(endLocation[1]-location[1])+1)))+1;
}