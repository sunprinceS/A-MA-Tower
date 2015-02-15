#pragma once
#include "ofMain.h"
#include "GameEvent.h"
#include "Timer.h"
#include "pearlMap.h"
#include "player.h"


class Game : public ofBaseApp{

	public:

		void setup(int& p1,int& p2,int& arena,bool first);
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
/****************USER DEFINED FUNCTION **************************/
        void reset();
        void gameEvent(GameEvent &e);
        //timer
        Timer timer;
        ofTrueTypeFont timeFont;

		//player
		Player p1;
		Player p2;
		int player1;
		int player2;
		RankData datum[5];
		string path;

        //pearlMap
        pearlMap map1;
		pearlMap map2;
		static bool shouldRemovePearl(pearl &p);

        //map&background
		ofImage background;
		ofSoundPlayer bgSound;
		bool bPlaying;

		//game
		bool bMoving;
		bool whoMove;
		float timeGameOver;
		ofTrueTypeFont title;
		vector <string> splitString;
		bool getbGameFinished(){return bGameFinished;}
		void setbGameFinished(bool y){bGameFinished = y;}
		//bool bCalculating;
		bool gameOver;
    private:
        bool bGameFinished;
};
