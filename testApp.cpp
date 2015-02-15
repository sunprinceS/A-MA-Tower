#include "testApp.h"
//已整理
//--------------------------------------------------------------
void testApp::setup(){

		scene = 0;
        _Rank.PATH="RANKDATA.txt";
        _welcome.setup();
        _singleGame.setup();
		_doubleGame.setup();
        _Rank.setup();
        //_Author.setup();
}

//--------------------------------------------------------------
void testApp::update(){
    switch(scene)
    {
    case 0:
        _welcome.update(scene);break;
    case 1000:
        _singleGame.update(scene);break;
    case 2000:
        _doubleGame.update(scene);break;

    case 3000:
        _Rank.update(scene);
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    switch(scene)
    {
    case 0:
        _welcome.draw(scene);break;
    case 1000:
        _singleGame.draw(scene);break;
    case 2000:
        _doubleGame.draw(scene);break;

    case 3000:
        _Rank.draw(scene);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    switch(scene)
    {
    case 0:
        _welcome.mouseMoved(x,y,scene);break;
    case 1000:
        _singleGame.draw(scene);break;
    case 2000:
        _doubleGame.mouseMoved(x,y,scene);break;

    case 3000:
        _Rank.mouseMoved(x,y,scene);
    }
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

    switch(scene)
    {
    case 0:
        _welcome.mouseDragged(x,y,button,scene);break;
    case 1000:
        _singleGame.mouseDragged(x,y,button,scene);break;
    case 2000:
        _doubleGame.mouseDragged(x,y,button,scene);break;

    case 3000:
        _Rank.mouseDragged(x,y,button,scene);
    }
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

    switch(scene)
    {
    case 0:
        _welcome.mousePressed(x,y,button,scene);break;
    case 1000:
        _singleGame.mousePressed(x,y,button,scene);break;
    case 2000:
        _doubleGame.mousePressed(x,y,button,scene);break;

    case 3000:
        _Rank.mousePressed(x,y,button,scene);
    }
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    switch(scene)
    {
    case 0:
        _welcome.mouseReleased(x,y,button,scene);break;
    case 1000:
        _singleGame.mouseReleased(x,y,button,scene);break;
    case 2000:
        _doubleGame.mouseReleased(x,y,button,scene);break;
    case 3000:
        _Rank.mouseReleased(x,y,button,scene);
    }
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
}
