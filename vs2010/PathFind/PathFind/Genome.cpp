#include "Genome.h"
#include "maze.h"

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

extern Maze* globMaze;

Genome::Genome(int GenLength, int GenKind){
	this->Gen= (int*)malloc(GenLength*sizeof(int));
	srand(GetTickCount());
	for(int i=0; i<GenLength; i++){
		Gen[i]= rand()%GenKind;
	}	
}

Genome::Genome(int* GenList, int GenLength){
	this->Gen= (int*)malloc(GenLength*sizeof(int));
	for(int i=0; i< GenLength; i++){
		Gen[i]= GenList[i];
	}
}

GenomePool::GenomePool(int GenLength, int GenNumb, int GenKind){
	this->GenLength= GenLength;
	this->GenNumb= GenNumb;
	this->GenKind= GenKind;

	GenList= (Genome**) malloc(sizeof(Genome*)* GenNumb);

	printf("initing genome pool: ");
	for(int i=0; i<GenNumb; i++){
		GenList[i]= new Genome(GenLength, GenKind);
		//Sleep(20);
		printf("%d ", i);
	}
	printf("\n");
}

void GenomePool::SetAdoption(int GenNumb, int Adoption){
	GenList[GenNumb]->Adoption= Adoption;
}

void GenomePool::Roulette(Genome** Gen1, Genome** Gen2){
	//printf("Start Roulette\n");
	long total= 0;
	int testtotal;
	int selectedGen1, selectedGen2;
	int select1, select2;
	for(int i=0; i<GenNumb; i++){
		total+= GenList[i]->Adoption;
	}
	select1= rand()%total;
	for(int count=0, i=0; i<GenNumb; i++){
		count+= GenList[i]->Adoption;
		if(count> select1){
			selectedGen1= i;
			break;
		}
	}
	testtotal= total;
	total= 0; 
	for(int i=0; i<GenNumb; i++){
		if(i== selectedGen1){
			continue;
		}
		total+= GenList[i]->Adoption;
	}
	select2= rand()%total;
	for(int count=0, i=0; i<GenNumb; i++){
		if(i== selectedGen1){
			continue;
		}
		count+= GenList[i]->Adoption;
		if(count> select2){
			selectedGen2= i;
			break;
		}
	}

	(*Gen1)= GenList[selectedGen1];
	(*Gen2)= GenList[selectedGen2];

	//printf("End Roulette\n");
}

void GenomePool::MakeCross(float ration){
	//printf("Start Make Cross\n");
	int ratio= ration*100;
	Genome** TempList= (Genome**) malloc(sizeof(Genome*)* GenNumb);
	int NewNumb=0;
	int* NewGen1= (int*)malloc(sizeof(int)* GenLength);
	int* NewGen2= (int*)malloc(sizeof(int)* GenLength);
	while(NewNumb<GenNumb){
		Genome* TempGen1= GenList[0],* TempGen2= GenList[1];
		Roulette(&TempGen1, &TempGen2);
		if(ratio< rand()%100){
			int CrossPoint= rand()%GenLength;
			for(int i=0; i<= CrossPoint; i++){
				NewGen1[i]= TempGen1->Gen[i];
				NewGen2[i]= TempGen2->Gen[i];
			}
			for(int i= CrossPoint+1; i<GenLength; i++){
				NewGen1[i]= TempGen2->Gen[i];
				NewGen2[i]= TempGen1->Gen[i];
			}
			TempList[NewNumb++]= new Genome(NewGen1, GenLength);
			TempList[NewNumb++]= new Genome(NewGen2, GenLength);
		}
		else{
			TempList[NewNumb++]= new Genome(TempGen1->Gen, GenLength);
			TempList[NewNumb++]= new Genome(TempGen2->Gen, GenLength);
		}
	}
	delete[] NewGen1;
	delete[] NewGen2;
	for(int i=0; i<GenNumb; i++){
		delete[] GenList[i]->Gen;
	}
	delete[] GenList;
	GenList= TempList;
	//printf("End Make Cross\n");
}

void GenomePool::MakeMutant(float ration){
	//printf("Start Make Mutant\n");
	float ratio= ration*100;
	for(int i=0; i<GenNumb; i++){
		for(int k=0; k<GenLength; k++){
			if(ratio> rand()%100){
				if(GenList[i]->Gen[k]== 0){
					GenList[i]->Gen[k]=1;
				}
				else{
					GenList[i]->Gen[k]=0;
				}
			}
		}
	}
	//printf("End Make Mutant\n");
}