#pragma once
#include"ofMain.h"
#include"pearl.h"
#include <cstdlib>
#include "GameEvent.h"
#include <ctime>
#include <cmath>
#include <queue>
#include "basic.h"
#define MAPSIZE 36
#define STEPSIZE 100

#define MAXROUND 10
#define MAXSEARCHROUND 5
#define MAXSCORESIZE   1048576 //pow(4,10)

class pearlMap
{
public :

    bool moving;
    vector<pearl>pearls;
	int pearls_tmp[MAPSIZE];
	bool bCalculated;
	bool bSlipped;
	short scores[4];//for Greedy Method,0->U; 1->D; 2->L; 3->R
	Dir testDir[10];
	//short scoresDFS[MAXSCORESIZE];

    pearlMap():moving(false),target_pearl(NULL),target(0),attack(0),comboNum(0),bCalculated(false),bSlipped(false),cpuDir_loc(0),MaxDFS(-30000)
    {
        srand(time(0));
        for(int i=0;i<MAPSIZE;++i)
        {
            removeOrNot[i] = false;
            fallDownPair.clear();//reset
        }
        pearlBombing.loadSound("media/pearlBomb.mp3");
		pearlBombing.setMultiPlay(true);
    }
    void slip();
    void getTargetPearl();
    void getTargetPearl(int ini_loc);
    void fallDown();
    int calCombo();
	void draw();
	void pearl_swap(pearl* a,pearl* b);
	void pearl_swap_cpu(int* a,int *b);
	void update();
    void setPlayer(bool _p);
	void cpuSlip();
	int calculate(); //return targetPearl(random give)

private:
    bool playerWho;
    bool removeOrNot[MAPSIZE];
    bool first;

    pearl* target_pearl;

	vector<comboPearl> fallDownPair;
	Dir cpuDir[STEPSIZE];

    int attack,comboNum;
    int target;
	int cpuDir_loc;

    void bomb(comboPearl _p); //_dir shows whether it is horizontal or vertical,horizontal->0,vertical->1  corner->leftest,uppest
    pearl* find_pearl(int num);
	//AI
	void AI();
	void AI_1(int ini_traget);
	void DFS(int round,int traget,Dir preDir,int j);
	int DFS_cal(int round,int traget,Dir preDir);
	//void DFSdecide(int j);
	short heuristic(int currentTable[]);
	int findScoreMax(Dir dir);
	int findScoreMaxDFS();
	//int countDFS;
	//int max_loc;
	short MaxDFS;

	ofSoundPlayer pearlBombing;
};
