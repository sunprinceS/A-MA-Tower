#pragma once
#include "ofMain.h"
//已整理
#define MAXHP 5000

class Player
{
public:
    string name;
    bool who;
    long long HP;
    ofImage photo;
	
    Player():HP(MAXHP),HP_length(150)
    {
        Font.loadFont("BRADHITC.ttf",20);
		bloodFont.loadFont("COOLSLIP.ttf",15);
    }
	
    void setPlayer(string _name,bool _who,int character)
    {
        who = _who;
        name = _name;
        if    (character == 1){photo.loadImage("image/FANG.PNG");}
        else if(character ==2){photo.loadImage("image/BEI.PNG");}
		else if(character ==3){photo.loadImage("image/CHUNG.PNG");}
		else if(character ==4){photo.loadImage("image/SHUN.PNG");}
		else if(character ==5){photo.loadImage("image/GUANG.PNG");}
		else {cout << "ERROR IN setPlayer" << endl;}

		if(who == 0)
			photo.mirror(0,1);

		photo.resize(100,100);
    }
	
    void draw()
    {
        if(who) // player1
        {
            //name
            ofSetHexColor(0xf02589);
            Font.drawString(name,110,30);
            ofSetHexColor(0x000000);
			bloodFont.drawString(ofToString(this->HP)+"/"+ofToString(MAXHP),120,100);
            //photo
            ofSetHexColor(0xffff77);
			photo.draw(5,5);
            //HP
			float pct = ofMap(HP, 0.0, MAXHP, 0.0, 1.0, true);
			ofSetHexColor(0x0000cd);
			ofRect(110,50,HP_length*pct, 20);

        }
        else //player2
        {
            //name
            ofSetHexColor(0xf02589);
            Font.drawString(name,800,30);
            ofSetHexColor(0x000000);
			bloodFont.drawString(ofToString(this->HP)+"/"+ofToString(MAXHP),ofGetWidth()/2+220,100);
            //photo
            ofSetHexColor(0xffb7dd);
			photo.draw(905,5);
            //HP
			float pct = ofMap(HP, 0.0, MAXHP, 0.0, 1.0, true);
			ofSetHexColor(0x0000cd);
			ofRect(700+(HP_length*(1-pct)),50,HP_length*pct, 20);
        }

    }
private:
    ofTrueTypeFont Font;
	ofTrueTypeFont bloodFont;
	float HP_length;
};
