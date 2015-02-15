#include "all.h"
//已整理

//--------------------------------------------------------------
void welcome::setup(){

	bg.loadImage("image/welcome.jpg");
    bg.resize(ofGetWindowWidth(),ofGetWindowHeight());

    ofTrueTypeFont::setGlobalDpi(72);
    FONTA.loadFont("COOLSLIP.ttf",50,1,1);
    FONTA.setLineHeight(18.0f);
	FONTA.setLetterSpacing(1.037);

    large.loadFont("BIG.ttf",80,1,1);
    large.setLineHeight(18.0f);
	large.setLetterSpacing(1.037);

}

//--------------------------------------------------------------
void welcome::update(int& scene){
}

//--------------------------------------------------------------
void welcome::draw(int& scene){
	//background
	ofSetHexColor(0xffffff);
    bg.draw(0,0);

	//title
    ofSetHexColor(0xffff00);
    large.drawString("A",250,80);
    large.drawString("-",300,80);
    large.drawString("M",320,80);
    large.drawString("A",385,80);
    large.drawString("T",515,80);
    large.drawString("O",560,80);
    large.drawString("W",620,80);
    large.drawString("E",690,80);
    large.drawString("R",740,80);


//buttonPic
    //1P
    if( ofGetMouseX()>85 && ofGetMouseX()<ofGetWidth()/2 && ofGetMouseY()>180 && ofGetMouseY()<280){
		FONTA.drawString("*",50,230);
    }
    //2P
    if( ofGetMouseX()>85 && ofGetMouseX()<ofGetWidth()/2 && ofGetMouseY()>360 && ofGetMouseY()<460){
        FONTA.drawString("*",50,410);
    }
    // Rank
    if( ofGetMouseX()>85 && ofGetMouseX()<ofGetWidth()/2 && ofGetMouseY()>540 && ofGetMouseY()<640){
        FONTA.drawString("*",50,590);
    }
    //quit
    if( ofGetMouseX()>ofGetWidth()/2 && ofGetMouseX()<ofGetWidth()/2+400 && ofGetMouseY()>ofGetHeight()/2+240 && ofGetMouseY()<ofGetHeight()/2+300){
        FONTA.drawString("*",ofGetWidth()/2+20,ofGetHeight()/2+290);
    }

    ofSetColor(64, 238, 234);
    FONTA.drawString("1P BATTLE",85,230);
    FONTA.drawString("2P BATTLE",85,410);
    FONTA.drawString("RANK",85,590);
    //small.drawString("ABOUT THE AUTHORS",ofGetWidth()/2+18,430);
    FONTA.drawString("GAME QUIT",ofGetWidth()/2+50,670);
}

//--------------------------------------------------------------
void welcome::keyPressed(int key,int& scene){

}

//--------------------------------------------------------------
void welcome::keyReleased(int key,int& scene){

}

//--------------------------------------------------------------
void welcome::mouseMoved(int x, int y,int& scene){


}

//--------------------------------------------------------------
void welcome::mouseDragged(int x, int y, int button,int& scene){

}

//--------------------------------------------------------------
void welcome::mousePressed(int x, int y, int button,int& scene){

    if(button ==0 && ofGetMouseX()>85 && ofGetMouseX()<ofGetWidth()/2 )
    {
		//1P BATTLE
        if(ofGetMouseY()>180 && ofGetMouseY()<280)
            scene = 1000;
        //2P BATTLE
		if(ofGetMouseY()>360 && ofGetMouseY()<460)
            scene = 2000;
        //RANK
		if(ofGetMouseY()>540 && ofGetMouseY()<640)
            scene = 3000;
    }
	if(button ==0 && ofGetMouseX()>ofGetWidth()/2 && ofGetMouseX()<ofGetWidth()/2+400 && ofGetMouseY()>ofGetHeight()/2+240 && ofGetMouseY()<ofGetHeight()/2+300)
		ofExit();

}

//--------------------------------------------------------------
void welcome::mouseReleased(int x, int y, int button,int& scene){

}

//--------------------------------------------------------------
void welcome::windowResized(int w, int h,int& scene){

}

//--------------------------------------------------------------
void welcome::gotMessage(ofMessage msg,int& scene){

}

//--------------------------------------------------------------
void welcome::dragEvent(ofDragInfo dragInfo,int& scene){

}

