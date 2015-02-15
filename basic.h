#pragma once
#include "ofMain.h"
//已整理
//pearl's attribute
enum color
{
    red = 0,
    yellow,
    green,
    blue,
    purple,
    pink
};
// used for fallDown and bomb
struct comboPearl
{
    int loc;
    bool dir;
    int number;
};

//used for RANK
struct RankData
{
    string playerName;
    int win;
    int lose;
};

//used for RANK , to express 勝率
struct Pct
{
    string n[3];
};

//used for cpuGame
enum Dir
{
	U = 0,
	D,
    L,
	R
};
