#include "all.h"
#include<algorithm>
//已整理
//--------------------------------------------------------------

void Rank::setup(){

    bg.loadImage("image/welcome.jpg");
    bg.resize(ofGetWindowWidth(),ofGetWindowHeight());

    ofTrueTypeFont::setGlobalDpi(72);
    text.loadFont("COOLSLIP.ttf",35,1,1);
    text.setLineHeight(18.0f);
	text.setLetterSpacing(1.037);
    FONTA.loadFont("BIG.ttf",50,1,1);
    FONTA.setLineHeight(18.0f);
	FONTA.setLetterSpacing(1.037);
	title.loadFont("2.ttf", 80, true, true);
	title.setLineHeight(84.0f);
	title.setLetterSpacing(1.035);
	button.loadFont("BIG.ttf",25,true,true);
	
	//for loading daat from RANKDATA
    ofBuffer buffer = ofBufferFromFile(PATH);//setup path
	string line = buffer.getFirstLine();//自第一行開始讀起
	

    for(int i=0;i<5;++i)//loading data
    {
        if(line.empty() == false) {
            splitString = ofSplitString(line, " ");//這是個超好用的function阿!!!
            datum[i].playerName=splitString[0];
            datum[i].win=ofToInt(splitString[1]);
            datum[i].lose=ofToInt(splitString[2]);
        }
        if(i!=4)//prevent read out of range
			line = buffer.getNextLine();
    }
    bdatumLoaded = true;
}

//--------------------------------------------------------------
void Rank::update(int& scene){
	
    if(bdatumLoaded == true){
		calculate(datum);
    }
	else 
	{
		ofBuffer buffer = ofBufferFromFile(PATH);//setup path
		string line = buffer.getFirstLine();//自第一行開始讀起
		
		for(int i=0;i<5;++i)//loading data
		{
			if(line.empty() == false) {
				splitString = ofSplitString(line, " ");//這是個超好用的function阿!!!
				datum[i].playerName=splitString[0];
				datum[i].win=ofToInt(splitString[1]);
				datum[i].lose=ofToInt(splitString[2]);
			}
			if(i!=4)//prevent read out of range
				line = buffer.getNextLine();
		}
		bdatumLoaded = true;
	}
}

//--------------------------------------------------------------
void Rank::draw(int& scene){

    ofSetHexColor(0xffffff);
    bg.draw(0,0);
	
    ofSetHexColor(0x0000ff);
    FONTA.drawString("Name",20,120);
	FONTA.drawString("W",220,120);
	FONTA.drawString("L",420,120);
	FONTA.drawString("PCT",620,120);
	FONTA.drawString("GB",860,120);


    ofSetHexColor(0xFFFF51);
    title.drawString("RANK", ofGetWidth()/2-160, 75);
   
	for(int i=0;i<5;++i)
	{
        ofSetHexColor(0xff8800);
		text.drawString(datum[i].playerName,20,200+75*i);
		text.drawString(ofToString(datum[i].win),220,200+75*i);
		text.drawString(ofToString(datum[i].lose),420,200+75*i);
		text.drawString(".",620,200+75*i);
		text.drawString(_Pct[i].n[0]+_Pct[i].n[1]+_Pct[i].n[2],630,200+75*i);

		if(i==0)
			text.drawString("  --",820,200+75*i);
		else
			text.drawString(ofToString(GB[i-1]),860,200+75*i);
	}


    ofSetHexColor(0x33ffff);
    button.drawString("Return",ofGetWidth()-170,ofGetHeight()-75);

    ofSetHexColor(0xffff00);
    if(ofGetMouseX()<ofGetWidth()-90 && ofGetMouseX()>ofGetWidth()-180 && ofGetMouseY()>ofGetHeight()-100 && ofGetMouseY()<ofGetHeight()-60)
        button.drawString("*",ofGetWidth()/2+330,ofGetHeight()-75);

}

//--------------------------------------------------------------
void Rank::keyPressed(int key,int& scene){

}

//--------------------------------------------------------------
void Rank::keyReleased(int key,int& scene){

}

//--------------------------------------------------------------
void Rank::mouseMoved(int x, int y,int& scene){



}

//--------------------------------------------------------------
void Rank::mouseDragged(int x, int y, int button,int& scene){

}

//--------------------------------------------------------------
void Rank::mousePressed(int x, int y, int button,int& scene){
    if(ofGetMouseX()<ofGetWidth()-90 && ofGetMouseX()>ofGetWidth()-180 && ofGetMouseY()>ofGetHeight()-100 && ofGetMouseY()<ofGetHeight()-60 && button ==0){
        scene = 0;
        bdatumLoaded = false;
    }
}

//--------------------------------------------------------------
void Rank::mouseReleased(int x, int y, int button,int& scene){

}

//--------------------------------------------------------------
void Rank::windowResized(int w, int h,int& scene){

}

//--------------------------------------------------------------
void Rank::gotMessage(ofMessage msg,int& scene){

}

//--------------------------------------------------------------
void Rank::dragEvent(ofDragInfo dragInfo,int& scene){

}
void Rank::calculate(RankData _datum[5])
{
	double pctTmp[5];
	
	for(int i=0;i<5;++i){
		pctTmp[i] = (double)datum[i].win/(datum[i].win+datum[i].lose);
	}

	//sorting
	int _loc;
	for(int i=0;i<5;++i)
	{
		_loc = i;
		for(int j=i+1;j<5;++j)
		{
			if(pctTmp[_loc] < pctTmp[j])
				_loc = j;
		}
		swap(datum[_loc],datum[i]);
		swap(pctTmp[_loc],pctTmp[i]);
	}
	//calculate GB
	for(int i=0;i<4;++i)
	{
		double t=(datum[0].win - datum[i+1].win)*(0.5) + (datum[i+1].lose - datum[0].lose)*(0.5);
		GB[i] = t;
	}
	//calculate PCT
	for(int i=0;i<5;++i)
    {
        pctTmp[i]*=10;
        for(int j=0;j<3;++j)
        {
            char tmp = '0'+((int)pctTmp[i]%10);//int turn to char
            _Pct[i].n[j] = tmp;
            pctTmp[i]*=10;
        }
    }
}
