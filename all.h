#ifndef ALL_H_INCLUDED
#define ALL_H_INCLUDED
#include "ofMain.h"
#include "Game.h"
#include "cpuGame.h"
#include "basic.h"
//已整理
class welcome
{
    public:
        void setup();
		void update(int& scene);
		void draw(int& scene);

		void keyPressed(int key,int& scene);
		void keyReleased(int key,int& scene);
		void mouseMoved(int x, int y,int& scene);
		void mouseDragged(int x, int y, int button,int& scene);
		void mousePressed(int x, int y, int button,int& scene);
		void mouseReleased(int x, int y, int button,int& scene);
		void windowResized(int w, int h,int& scene);
		void dragEvent(ofDragInfo dragInfo,int& scene);
		void gotMessage(ofMessage msg,int& scene);

		ofImage buttonPic;
		ofImage bg;
		ofTrueTypeFont  FONTA;
		ofTrueTypeFont large;

		int buttonX,buttonY;
};


/*class HowToPlay
{
    public:
        void setup();
		void update();
		void draw(int& scene);

		void keyPressed(int key,int& scene);
		void keyReleased(int key,int& scene);
		void mouseMoved(int x, int y,int& scene);
		void mouseDragged(int x, int y, int button,int& scene);
		void mousePressed(int x, int y, int button,int& scene);
		void mouseReleased(int x, int y, int button,int& scene);
		void windowResized(int w, int h,int& scene);
		void dragEvent(ofDragInfo dragInfo,int& scene);
		void gotMessage(ofMessage msg,int& scene);
		ofTrueTypeFont text;
		ofTrueTypeFont title;
		ofTrueTypeFont button;
		bool bFirst;
};*/

class SingleGame
{
	public:
        void setup();
		void update(int& scene);
		void draw(int& scene);

		void keyPressed(int key,int& scene);
		void keyReleased(int key,int& scene);
		void mouseMoved(int x, int y,int& scene);
		void mouseDragged(int x, int y, int button,int& scene);
		void mousePressed(int x, int y, int button,int& scene);
		void mouseReleased(int x, int y, int button,int& scene);
		void windowResized(int w, int h,int& scene);
		void dragEvent(ofDragInfo dragInfo,int& scene);
		void gotMessage(ofMessage msg,int& scene);

		cpuGame _cpuGame;

		int scene;
		int arena;
		int p1,p2;

		bool b_p1Choosed;
		bool b_p2Choosed;
		bool bStageChoosed;
		bool bGameChoosed;
		bool first;

		ofImage FANG;
		ofImage BEI;
		ofImage CHUNG;
		ofImage HSUN;
		ofImage GUANG;

		ofImage b1;
		ofImage b2;
		ofImage b3;
		ofImage b4;
		ofImage b5;

		ofImage bg;

		ofTrueTypeFont text;
		ofTrueTypeFont title;
};
class DoubleGame
{
	public:
        void setup();
		void update(int& scene);
		void draw(int& scene);

		void keyPressed(int key,int& scene);
		void keyReleased(int key,int& scene);
		void mouseMoved(int x, int y,int& scene);
		void mouseDragged(int x, int y, int button,int& scene);
		void mousePressed(int x, int y, int button,int& scene);
		void mouseReleased(int x, int y, int button,int& scene);
		void windowResized(int w, int h,int& scene);
		void dragEvent(ofDragInfo dragInfo,int& scene);
		void gotMessage(ofMessage msg,int& scene);

		Game _Game;

		int scene;
		int arena;
		int p1,p2;

		bool b_p1Choosed;
		bool b_p2Choosed;
		bool bStageChoosed;
		bool bGameChoosed;
		bool first;

		ofImage FANG;
		ofImage BEI;
		ofImage CHUNG;
		ofImage HSUN;
		ofImage GUANG;

		ofImage b1;
		ofImage b2;
		ofImage b3;
		ofImage b4;
		ofImage b5;

		ofImage bg;

		ofTrueTypeFont text;
		ofTrueTypeFont title;
};

class Rank
{
	public:

		void setup();
		void update(int& scene);
		void draw(int& scene);

		void keyPressed(int key,int& scene);
		void keyReleased(int key,int& scene);
		void mouseMoved(int x, int y,int& scene);
		void mouseDragged(int x, int y, int button,int& scene);
		void mousePressed(int x, int y, int button,int& scene);
		void mouseReleased(int x, int y, int button,int& scene);
		void windowResized(int w, int h,int& scene);
		void dragEvent(ofDragInfo dragInfo,int& scene);
		void gotMessage(ofMessage msg,int& scene);

		void calculate(RankData _datum[5]);

		string PATH;
        vector <string> splitString;

		ofTrueTypeFont FONTA;
        ofTrueTypeFont text;
        ofTrueTypeFont title;
	    ofTrueTypeFont button;

		ofImage bg;
		ofImage crown;

		bool bdatumLoaded;

		double GB[4];
        RankData datum[5];
        Pct _Pct[5];



};
//rank end

/*class Author
{
    public:
        void setup();
        void update();
        void draw(int& scene);
        void mousePressed(int x, int y, int button,int& scene);
		ofTrueTypeFont text;
		ofTrueTypeFont title;
		ofTrueTypeFont button;
		bool bFirst;
};*/


#endif // ALL_H_INCLUDED


