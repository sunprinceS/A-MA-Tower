#include "all.h"
#include "Game.h"

//updated at 2014/7/10
//已整理
//--------------------------------------------------------------
void DoubleGame::setup(){

	scene = 2000;
	bg.loadImage("image/welcome.jpg");
    bg.resize(ofGetWindowWidth(),ofGetWindowHeight());

	// choose player
	FANG.loadImage("image/FANG.PNG");
	FANG.resize(150,150);
	BEI.loadImage("image/BEI.PNG");
	BEI.resize(150,150);
	CHUNG.loadImage("image/CHUNG.PNG");
	CHUNG.resize(150,150);
	HSUN.loadImage("image/SHUN.PNG");
	HSUN.resize(150,150);
	GUANG.loadImage("image/GUANG.PNG");
	GUANG.resize(150,150);

	//choose arena
	b1.loadImage("image/b1.jpg");
	b1.resize(150,150);
	b2.loadImage("image/b2.jpg");
	b2.resize(150,150);
	b3.loadImage("image/b3.jpg");
	b3.resize(150,150);
	b4.loadImage("image/b4.jpg");
	b4.resize(150,150);
	b5.loadImage("image/b5.jpg");
    b5.resize(150,150);

	//initialize
	p1 = 0,p2 = 0,arena = 0;
	bGameChoosed = false;
	b_p1Choosed = false;
	b_p2Choosed = false;
	bStageChoosed = false;
	first = true;  //used for the game setup
	/*如果說，沒有做這個動作，在game內就會重複用一個pearlMap，就會出現那個bomb時消了兩個，fallDown卻只用一個的bug*/

	//setup font
    ofTrueTypeFont::setGlobalDpi(72);
    title.loadFont("COOLSLIP.ttf",50,1,1);
    title.setLineHeight(18.0f);
	title.setLetterSpacing(1.037);
    text.loadFont("COOLSLIP.ttf",35,1,1);
}

//--------------------------------------------------------------
void DoubleGame::update(int& scene){

	if(b_p1Choosed == true && b_p2Choosed == true && bStageChoosed == true) //game前置動作已完成
	{
		if(bGameChoosed == false)//尚未進入遊戲
		{	//game start
			bGameChoosed = true;
			_Game.setup(p1,p2,arena,first);
		}
		else
        {
             _Game.update();
             if(_Game.getbGameFinished()){ //若遊戲結束...
				//reset
                p1 = 0,p2 = 0,arena = 0;
                bGameChoosed = false;
                b_p1Choosed = false;
                b_p2Choosed = false;
                bStageChoosed = false;
                _Game.reset();//game 的reset
                first = false;//代表至少已經進過遊戲一次了
                scene = 0; //return to welcome
             }
        }

	}
}

//--------------------------------------------------------------
void DoubleGame::draw(int& scene){

	if(b_p1Choosed == false || b_p2Choosed == false || bStageChoosed == false) //option
	{
		//background
		ofSetHexColor(0xffffff);
		bg.draw(0,0);
		ofSetHexColor(0xffff00);
		//
		title.drawString("* Choose player :",80,80);
		title.drawString("* Choose arena :",80,400);


		/*for choose player*/
		ofSetHexColor(0x0000ff);
		ofRect(50,140,150,200);
		ofRect(250,140,150,200);
		ofRect(450,140,150,200);
		ofRect(650,140,150,200);
		ofRect(850,140,150,200);

		//being choosed
		ofSetHexColor(0xff3333);
		if(p1 == 1 || p2 == 1){ofRect(50,140,150,200);}
		if(p1 == 2 || p2 == 2){ofRect(250,140,150,200);}
		if(p1 == 3 || p2 == 3){ofRect(450,140,150,200);}
		if(p1 == 4 || p2 == 4){ofRect(650,140,150,200);}
		if(p1 == 5 || p2 == 5){ofRect(850,140,150,200);}

		//photo
        ofSetHexColor(0xffffff);
		FANG.draw(50,140);
		BEI.draw(250,140);
		CHUNG.draw(450,140);
		HSUN.draw(650,140);
		GUANG.draw(850,140);

		//name
		ofSetHexColor(0xffff00);
		text.drawString("FANG",63,330);
		text.drawString("BEI",283,330);
		text.drawString("CHUNG",450,330);
		text.drawString("SHUN",663,330);
		text.drawString("GUANG",850,330);

		/*for choose arena*/
		ofSetHexColor(0x0066ff);
		ofRect(50,450,150,200);
		ofRect(250,450,150,200);
		ofRect(450,450,150,200);
		ofRect(650,450,150,200);
		ofRect(850,450,150,200);

		//being choosed
		ofSetHexColor(0xff3333);
		if(arena == 1){ofRect(50,450,150,200);}
		if(arena == 2){ofRect(250,450,150,200);}
		if(arena == 3){ofRect(450,450,150,200);}
		if(arena == 4){ofRect(650,450,150,200);}
		if(arena == 5){ofRect(850,450,150,200);}

		//photo
        ofSetHexColor(0xffffff);
		b1.draw(50,450);
		b2.draw(250,450);
		b3.draw(450,450);
		b4.draw(650,450);
		b5.draw(850,450);
	}
	else {_Game.draw();}
}
//--------------------------------------------------------------
void DoubleGame::keyPressed(int key,int& scene){
	if(b_p1Choosed == true && b_p2Choosed == true && bStageChoosed ==true)
		_Game.keyPressed(key);
}

//--------------------------------------------------------------
void DoubleGame::keyReleased(int key,int& scene){
	if(b_p1Choosed == true && b_p2Choosed == true && bStageChoosed==true)
		_Game.keyReleased(key);
}

//--------------------------------------------------------------
void DoubleGame::mouseMoved(int x, int y,int& scene){
	if(b_p1Choosed == true && b_p2Choosed == true && bStageChoosed==true)
		_Game.mouseMoved( x, y);
}

//--------------------------------------------------------------
void DoubleGame::mouseDragged(int x, int y, int button,int& scene){
	if(b_p1Choosed == true && b_p2Choosed == true && bStageChoosed==true)
		_Game.mouseDragged(x, y, button);

}

//--------------------------------------------------------------
void DoubleGame::mousePressed(int x, int y, int button,int& scene){
	if(b_p1Choosed == false || b_p2Choosed == false || bStageChoosed == false) //option
	{
		if(b_p1Choosed == false) //choose player1
		{
			if(button == 0)
			{
				if(ofGetMouseX()>= 50&&ofGetMouseX()<= 200&& ofGetMouseY() >= 140&&ofGetMouseY()<=340){
					b_p1Choosed = true;
					p1 = 1;
				}
				if(ofGetMouseX()>= 250&&ofGetMouseX()<= 400&& ofGetMouseY() >= 140&&ofGetMouseY()<=340){
					b_p1Choosed = true;
					p1 = 2;
				}
				if(ofGetMouseX()>= 450&&ofGetMouseX()<= 600&& ofGetMouseY() >= 140&&ofGetMouseY()<=340){
					b_p1Choosed = true;
					p1 = 3;
				}
				if(ofGetMouseX()>= 650&&ofGetMouseX()<= 800&& ofGetMouseY() >= 140&&ofGetMouseY()<=340){
					b_p1Choosed = true;
					p1 = 4;
				}
				if(ofGetMouseX()>= 850&&ofGetMouseX()<= 1000&& ofGetMouseY() >= 140&&ofGetMouseY()<=340){
					b_p1Choosed = true;
					p1 = 5;
				}
			}
		}
		else
		{
			if(b_p2Choosed == false)//choose player2
			{
				if(button == 0)
				{
					if(ofGetMouseX()>= 50&&ofGetMouseX()<= 200&& ofGetMouseY() >= 140&&ofGetMouseY()<=340){
						b_p2Choosed = true;
						p2 = 1;
					}
					if(ofGetMouseX()>= 250&&ofGetMouseX()<= 400&& ofGetMouseY() >= 140&&ofGetMouseY()<=340){
						b_p2Choosed = true;
						p2 = 2;
					}
					if(ofGetMouseX()>= 450&&ofGetMouseX()<= 600&& ofGetMouseY() >= 140&&ofGetMouseY()<=340){
						b_p2Choosed = true;
						p2 = 3;
					}
					if(ofGetMouseX()>= 650&&ofGetMouseX()<= 800&& ofGetMouseY() >= 140&&ofGetMouseY()<=340){
						b_p2Choosed = true;
						p2 = 4;
					}
					if(ofGetMouseX()>= 850&&ofGetMouseX()<= 1000&& ofGetMouseY() >= 140&&ofGetMouseY()<=340){
						b_p2Choosed = true;
						p2 = 5;
					}
				}
			}
			if(bStageChoosed == false)//choose arena
			{
				if(button == 0)
				{
					if(ofGetMouseX()>= 50&&ofGetMouseX()<= 200&& ofGetMouseY() >= 450&&ofGetMouseY()<=600){
						bStageChoosed = true;
						arena = 1;
					}
					if(ofGetMouseX()>= 250&&ofGetMouseX()<= 400&&ofGetMouseY() >= 450&&ofGetMouseY()<=600){
						bStageChoosed = true;
						arena = 2;
					}
					if(ofGetMouseX()>= 450&&ofGetMouseX()<= 600&&ofGetMouseY() >= 450&&ofGetMouseY()<=600){
						bStageChoosed = true;
						arena = 3;
					}
					if(ofGetMouseX()>= 650&&ofGetMouseX()<= 800&& ofGetMouseY() >= 450&&ofGetMouseY()<=600){
					 bStageChoosed = true;
						arena = 4;
					}
					if(ofGetMouseX()>= 850&&ofGetMouseX()<= 1000&&ofGetMouseY() >= 450&&ofGetMouseY()<=600){
						bStageChoosed = true;
						arena = 5;
					}
				}
			}
		}
	}
	if(bGameChoosed == true)
		_Game.mousePressed(x,y,button);
}
//--------------------------------------------------------------
void DoubleGame::mouseReleased(int x, int y, int button,int& scene){
	if(b_p1Choosed == true && b_p2Choosed == true && bStageChoosed==true)
		_Game.mouseReleased(x,y, button);
}

//--------------------------------------------------------------
void DoubleGame::windowResized(int w, int h,int& scene){
	if(b_p1Choosed == true && b_p2Choosed == true && bStageChoosed==true)
		_Game.windowResized(w, h);
}

//--------------------------------------------------------------
void DoubleGame::gotMessage(ofMessage msg,int& scene){
	if(b_p1Choosed == true && b_p2Choosed == true && bStageChoosed==true)
		_Game.gotMessage( msg);
}

//--------------------------------------------------------------
void DoubleGame::dragEvent(ofDragInfo dragInfo,int& scene){
	if(b_p1Choosed == true && b_p2Choosed == true && bStageChoosed==true)
		_Game.dragEvent(dragInfo);
}


