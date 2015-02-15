#include "Game.h"
//已整理
 /***
 *2014/6/23 :
 (1)timer class->countdown
 (2)make player alternate correctly
 (3)pearlMap ->get the target pearl(using pointer)
 (4)use enum to construct pearl's attribute,also finish the whole pearl class
 (5)swap blocks OK
 (6)For convenience ,one combo means "4 pearl"!

 *2014/6/24 :
 (1)falldown finfished (but actually just only refresh)
 (2)calCombo finish,also bomb(call gameevent)
 (3)background and player setup finished
 (4)DEBUG,  prevent find_pearl can't find pearl...XD

*2014/7/10
(1)2P BATTLE finished,interface build up

*2014/7/23
(1)CPU slip finished,but still lack of"artificial intelligence"
 /********************************TO DO*******************************
 *add card(?
 *add attack effect(different pearl,different effect,maybe also add plusHP function)
 *add AI(more on this later)
 
 *2014/8/9
 --->slip有問題(左滑、右滑的限制條件太鬆只會prevent第一行和最後一行滑出界的情況)
 --->DFS的bug : 滑的順序似乎跟heuristic不太一樣
 **********************************************************************/

//----------------------------------------
bool Game::shouldRemovePearl(pearl &p){
    return p.bRemove;
}

//--------------------------------------------------------------
void Game::setup(int& _p1,int& _p2,int& arena,bool first) {

    //background setup
    if(arena == 1){background.loadImage("image/b1.jpg");}
    else if(arena == 2){background.loadImage("image/b2.jpg");}
    else if(arena == 3){background.loadImage("image/b3.jpg");}
    else if(arena == 4){background.loadImage("image/b4.jpg");}
    else if(arena == 5){background.loadImage("image/b5.jpg");}
    else {cout << "ERROR" << endl; }
    background.resize(ofGetWidth(),ofGetHeight());
    //music setup
    if(arena == 1){bgSound.loadSound("media/bgS1.mp3");}
    else if(arena == 2){bgSound.loadSound("media/bgS2.mp3");}
    else if(arena == 3){bgSound.loadSound("media/bgS3.mp3");}
    else if(arena == 4){bgSound.loadSound("media/bgS4.mp3");}
    else if(arena == 5){bgSound.loadSound("media/bgS5.mp3");}
    else {cout << "ERROR" << endl; }
    bgSound.setMultiPlay(true);
    bgSound.setLoop(true);
    bgSound.setVolume(0.75f);
    bPlaying = false;

    //player setup
    player1 = _p1;
	if     (_p1 == 1){p1.setPlayer("FANG",1,_p1);}
	else if(_p1 == 2){p1.setPlayer("BEI",1,_p1);}
	else if(_p1 == 3){p1.setPlayer("CHUNG",1,_p1);}
	else if(_p1 == 4){p1.setPlayer("SHUN",1,_p1);}
	else if(_p1 == 5){p1.setPlayer("GUANG",1,_p1);}
	else {cout << "ERROR IN PLAYER SETUP" << endl;}

    player2 = _p2;
    if     (_p2 == 1){p2.setPlayer("FANG",0,_p2);}
	else if(_p2 == 2){p2.setPlayer("BEI",0,_p2);}
	else if(_p2 == 3){p2.setPlayer("CHUNG",0,_p2);}
	else if(_p2 == 4){p2.setPlayer("SHUN",0,_p2);}
	else if(_p2 == 5){p2.setPlayer("GUANG",0,_p2);}
	else {cout << "ERROR IN PLAYER SETUP" << endl;}


    //timer setup
    timeFont.loadFont("JOKERMAN.ttf",30);
    title.loadFont("COOLSLIP.ttf",100,1,1);
    //game setup
    /***PRETTY IMPORTANT!!!***/
    /*若沒加此，在第二次遊戲時，程式會再創造出一個pearls(在第二次遊戲時發現gameEvent顯示消掉的pearl重複出現兩次)
    可是fallDownPair只會push一個  所以在call fallDown時 會有一個pearls會漏洞(而且那個pearls好像就是當前在用的那個)*/
    if(first == true)
    {
        map1.setPlayer(1);
        map2.setPlayer(0);
    }

    whoMove = 1;
    bMoving = false;
    bGameFinished = false;
    gameOver = false;

    //data
    path = "RANKDATA.txt";
    ofBuffer buffer = ofBufferFromFile(path);
    string line = buffer.getFirstLine();
    for(int i=0;i<5;++i)
    {
        if(line.empty() == false) {
            splitString = ofSplitString(line, " ");
            datum[i].playerName=splitString[0];
            datum[i].win=ofToInt(splitString[1]);
            datum[i].lose=ofToInt(splitString[2]);
        }
        if(i!=4)
        line = buffer.getNextLine();
    }

    // listen to any of the events for the game
    ofAddListener(GameEvent::events, this, &Game::gameEvent);

}

//--------------------------------------------------------------
void Game::gameEvent(GameEvent &e) {

    cout << "Game Event: "+e.message << endl;

	if(e.p!=NULL)//p means pearl
	{
		e.p->timePearlBombed = ofGetElapsedTimef();
		e.p->bBombing = true;
	}
}

//--------------------------------------------------------------
void Game::update() {
    //update timer
    timer.update();
    //bomb the blocks
    map1.update();
    map2.update();

	ofRemove(map1.pearls, shouldRemovePearl);
	ofRemove(map2.pearls, shouldRemovePearl);

	if(this->gameOver)
    {
        bgSound.stop();
        // update datum
        ofBuffer newDatum;
        for(int i=0;i<5;++i)
        {
            newDatum.append(datum[i].playerName);
            newDatum.append(" "+ofToString(datum[i].win));
            newDatum.append(" "+ofToString(datum[i].lose));
            newDatum.append("\n");
            ofBufferToFile("RANKDATA.txt",newDatum);
        }
    }

    if(ofGetElapsedTimef()-timeGameOver >3 && gameOver){
        bGameFinished = true;
    }

}

//--------------------------------------------------------------
void Game::draw(){
    ofSetHexColor(0xffffff);
    background.draw(0,0);
    //draw timer
    timer.draw();
    ofSetHexColor(0xee7700);
    timeFont.drawString("TIME",(ofGetWidth()-100)/2, 35);

    if(bPlaying == false)
    {
        bgSound.play();
        bPlaying = true;
    }

    //draw map
    map1.draw();
    map2.draw();

    //draw player
    p1.draw();
    p2.draw();
    if(gameOver == true && bGameFinished == false){
       ofSetHexColor(0x6a5acd);
       title.drawString("Game Over",ofGetWidth()/2-360,ofGetHeight()/2-50);
    }
    /*for test*/
    //cout << "player " << whoMove << endl;
}

//--------------------------------------------------------------
void Game::keyPressed(int key) {

}

//--------------------------------------------------------------
void Game::keyReleased(int key) {
}

//--------------------------------------------------------------
void Game::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void Game::mouseDragged(int x, int y, int button){
    //when dragging some pearl
    if(bMoving == true)
    {
        if(timer.getbReached() == false)//time ISN'T up
        {
            if(whoMove)//player 1
            {
                if(((ofGetMouseX()>50)&&(ofGetMouseX()<350))&&((ofGetMouseY()>150)&&(ofGetMouseY()<450)))
                    map1.slip();
            }

            else //player2
            {
                if(((ofGetMouseX()>650)&&(ofGetMouseX()<950))&&((ofGetMouseY()>150)&&(ofGetMouseY()<450)))
                    map2.slip();
            }

        }
        else//time's up
        {
            if(whoMove)
            {
                map1.moving = false;
                if(map1.calCombo() < p2.HP)
                    p2.HP -= map1.calCombo();
                else
                {
                    p2.HP = 0;
                    ++datum[player2-1].lose;
                    ++datum[player1-1].win;
                    gameOver = true;
                    timeGameOver = ofGetElapsedTimef();
                }

                map1.fallDown();
            }

            else
            {
                map2.moving = false;
                if(map2.calCombo() <  p1.HP)
                    p1.HP -= map2.calCombo();
                else
                {
                    p1.HP = 0;
                    ++datum[player1-1].lose;
                    ++datum[player2-1].win;
                    gameOver = true;
                    timeGameOver = ofGetElapsedTimef();
                }

                map2.fallDown();
            }

            bMoving = false;
            timer.stopCountDown();
            whoMove = !(whoMove);
        }
    }

}

//--------------------------------------------------------------
void Game::mousePressed(int x, int y, int button){
    // for countdown, to let player move the pearl in correct time
    if(bMoving == false)
    {
        if(whoMove)//player1's turn
        {
            if(((ofGetMouseX()>=50)&&(ofGetMouseX()<=350))&&((ofGetMouseY()>=150)&&(ofGetMouseY()<=450)))
            {
                bMoving = true;
                map1.moving = true;
                map1.getTargetPearl();
                timer.countDown();

            }
        }
        else//player2's turn
        {
            if(((ofGetMouseX()>=650)&&(ofGetMouseX()<=950))&&((ofGetMouseY()>=150)&&(ofGetMouseY()<=450)))
            {
                bMoving = true;
                map2.moving = true;
                map2.getTargetPearl();
                timer.countDown();

            }

        }
    }
}

//--------------------------------------------------------------
void Game::mouseReleased(int x, int y, int button){
    if(bMoving == true)//when dragging some pearl,then give up the remain_time
    {
        if(whoMove)
        {
            map1.moving = false;
            if(map1.calCombo() <p2.HP)
                p2.HP -= map1.calCombo();
            else
            {
                  p2.HP = 0;
                  ++datum[player2-1].lose;
                  ++datum[player1-1].win;
                  gameOver = true;
                  timeGameOver = ofGetElapsedTimef();
            }
            map1.fallDown();
        }
        else
        {
            map2.moving = false;
            if(map2.calCombo() <p1.HP)
                p1.HP -= map2.calCombo();
            else
            {
                  p1.HP = 0;
                  ++datum[player1-1].lose;
                  ++datum[player2-1].win;
                  gameOver = true;
                  timeGameOver = ofGetElapsedTimef();
            }

            map2.fallDown();
        }
        bMoving = false;
        timer.stopCountDown();
        whoMove = !(whoMove);
    }
}

//--------------------------------------------------------------
void Game::windowResized(int w, int h){

}

//--------------------------------------------------------------
void Game::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void Game::dragEvent(ofDragInfo dragInfo){

}
void Game::reset(){
    p1.HP = MAXHP;
    p2.HP = MAXHP;
    bGameFinished = false;
    gameOver = false;
}
