#pragma once
#include "ofMain.h"
#include "basic.h"
#include <cstdlib>
//已整理
class pearl
{
public :
    pearl(bool _who):bRemove(false),bBombing(false),who(_who),size(50),bTargeted(false){};
    
	bool bRemove;
    bool bTargeted;
	bool bBombing;
	
    color attribute;
    int number;
	
	bool who;//1->player1
	
	int size;
    int posX,posY;
	
	float radius;
	float timePearlBombed;
	
	void draw()
	{
	    if(this->bRemove == false)
        {
            switch(this->attribute)
            {
                case 0:
                ofSetHexColor(0xff0000);
                break;
                case 1:
                ofSetHexColor(0xffff00);
                break;
                case 2:
                ofSetHexColor(0x00ff00);
                break;
                case 3:
                ofSetHexColor(0x00ffff);
                break;
                case 4:
                ofSetHexColor(0x9900ff);
                break;
                case 5:
                ofSetHexColor(0xff44aa);
                break;
            }
			
            if(this->bTargeted == true)
                ofDrawBox(this->posX,this->posY,5,this->size);
            else
                ofRect(this->posX,this->posY,this->size,this->size);
				
            if(this->bBombing == true)
            {
                ofSetHexColor(0xffffff);
                ofDrawBox(this->posX,this->posY,15,this->size-=0.3);
            }
        }

	}
	
	void update()
	{
		if(who)
		{
			posX = 50+(number%6)*50;
			posY = 150+(number/6)*50;
		}
		else
		{
			posX = 650+(number%6)*50;
			posY = 150+(number/6)*50;
		}

		if(bBombing)
		{
			float timeBombed = ofGetElapsedTimef() - timePearlBombed;
			if(timeBombed > 0.3)
			{
				this->bRemove = true;
			}
		}
	}
};
