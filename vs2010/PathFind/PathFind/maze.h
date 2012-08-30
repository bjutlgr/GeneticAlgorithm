class Maze{
	int initLocation[2];
	int curLocation[2];
	int** maze;
	int mazeX, mazeY;
	int endLocation[2];
public:
	Maze(int initX, int initY, int* maze, int Xsize, int Ysize, int Xend, int Yend);
	void GetLastLoc(int* xoutput, int* youtput, int* Path, int PathSize);
	int GetAdaption(int* location);
	void printMaze();
};