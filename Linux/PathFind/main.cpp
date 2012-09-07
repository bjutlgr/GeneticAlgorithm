#include "maze.h"
#include "Genome.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <conio.h>

#define PATH_LENGTH 100
#define PATH_NUMB 150

Maze* globMaze;

int maze[13][16]={
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
	{1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,1,0,0,0,0,1,0,0,1,0,0,0,1,1},
	{1,0,1,0,0,0,1,0,1,0,1,0,0,1,0,1},
	{1,0,1,1,1,0,0,0,1,0,0,0,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,0,1,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1}
};

int main(){

	int Xend= 6;
	int Yend= 12;

	GenomePool* GenPool= new GenomePool(PATH_LENGTH, PATH_NUMB, 2);
	Maze* myMaze= new Maze(15, 3, (int*)maze, 16, 13, Xend, Yend);
	globMaze= myMaze;
	myMaze->printMaze();
	getch();
	printf("Start Path Find\n");
	for(int loop= 0; ; loop++){
		int lastLoc[2];
		for(int i=0; i<PATH_NUMB; i++){
			myMaze->GetLastLoc(&lastLoc[0], &lastLoc[1], GenPool->GenList[i]->Gen, PATH_LENGTH);
			int Adoption= myMaze->GetAdaption(lastLoc);
			GenPool->SetAdoption(i, Adoption);
			//마지막에 도달 했을시 종료
			if(lastLoc[0]== Xend&& lastLoc[1]== Yend){
				for(int length=0; length< PATH_LENGTH; length++){
					printf("%d", GenPool->GenList[i]->Gen[length]);
				}
				printf("\n generation: %d\n", loop);
				return 0;
			}

			//마지막에 도달 못했으면 다음 세대를 생산한다.
		}
		GenPool->MakeCross(0.7); //파라미터는 교차가 일어날 확률
		GenPool->MakeMutant(0.02); //파라미터는 돌연변이가 일어날 확률

	}
	return 0;
}