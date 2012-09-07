class Genome{

public:
	int* Gen;
	int Adoption;
	Genome(int GenLength, int GenKind);
	Genome(int* GenList, int GenLength);
};

class GenomePool{

public:
	Genome** GenList;
	int GenLength;
	int GenNumb;
	int GenKind;

	GenomePool(int GenLength, int GenNumb, int GenKind);
	void SetAdoption(int GenNumb, int Adoption);

	void Roulette(Genome** Gen1, Genome** Gen2);

	void MakeCross(float ration);
	void MakeMutant(float ration);
};