#include "cpuGame.h"

//----------------------------------------
bool cpuGame::shouldRemovePearl(pearl &p){
    return p.bRemove;
}

//--------------------------------------------------------------
void cpuGame::setup(int& _p1,int& _p2,int& arena,bool first) {

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

	//computer
    player2 = _p2;
    if     (_p2 == 1){p2.setPlayer("PIG-MA",0,_p2);}
	else if(_p2 == 2){p2.setPlayer("SHUANG",0,_p2);}
	else if(_p2 == 3){p2.setPlayer("SHEN",0,_p2);}
	else if(_p2 == 4){p2.setPlayer("BOSS J",0,_p2);}
	else if(_p2 == 5){p2.setPlayer("SUN",0,_p2);}
	else {cout << "ERROR IN PLAYER SETUP" << endl;}


    //timer setup
    timeFont.loadFont("JOKERMAN.ttf",30);
    title.loadFont("COOLSLIP.ttf",100,1,1);
    //cpuGame setup
    /***PRETTY IMPORTANT!!!***/
    /*若沒加此，在第二次遊戲時，程式會再創造出一個pearls(在第二次遊戲時發現cpuGameEvent顯示消掉的pearl重複出現兩次)
    可是fallDownPair只會push一個  所以在call fallDown時 會有一個pearls會漏洞(而且那個pearls好像就是當前在用的那個)*/
    if(first == true)
    {
        map1.setPlayer(1);
        map2.setPlayer(0);
    }

    whoMove = 1;
    bMoving = false;
    bcpuGameFinished = false;
    cpuGameOver = false;

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

    // listen to any of the events for the cpuGame
    ofAddListener(GameEvent::events, this, &cpuGame::gameEvent);

}

//--------------------------------------------------------------
void cpuGame::gameEvent(GameEvent& e) {

    cout << "cpuGame Event: "+e.message << endl;

	if(e.p!=NULL)//p means pearl
	{
		e.p->timePearlBombed = ofGetElapsedTimef();
		e.p->bBombing = true;
	}
}

//--------------------------------------------------------------
void cpuGame::update() {
    //update timer
    timer.update();
    //bomb the blocks
    map1.update();
    coolTime = ofGetElapsedTimef() - time;
	if(map2.bSlipped == false && map2.bCalculated == true)
    {
        if(coolTime >= COOLTIME)
        {
            map2.cpuSlip();
            time = ofGetElapsedTimef();
        }
    }

	else if(map2.bSlipped == true && map2.bCalculated == true) // slip finished
	{
		map2.moving = false;
		map2.bCalculated = false;
		if(map2.calCombo() < p1.HP)
            p1.HP -= map2.calCombo();
        else
        {
			p1.HP = 0;
            ++datum[player1-1].lose;
            //++datum[player2-1].win;
            cpuGameOver = true;
            timecpuGameOver = ofGetElapsedTimef();
        }
		map2.fallDown();
		map2.bSlipped = false;
		bMoving = false;
        timer.stopCountDown();
        whoMove = !(whoMove);
	}
    map2.update();

	ofRemove(map1.pearls, shouldRemovePearl);
	ofRemove(map2.pearls, shouldRemovePearl);

	if(this->cpuGameOver)
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

    if(ofGetElapsedTimef()-timecpuGameOver >3 && cpuGameOver){
        bcpuGameFinished = true;
    }

}

//-------------------------------------------------------------
void cpuGame::draw(){
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
    if(cpuGameOver == true && bcpuGameFinished == false){
       ofSetHexColor(0x6a5acd);
       title.drawString("Game Over",ofGetWidth()/2-360,ofGetHeight()/2-50);
    }
    /*for test*/
    //cout << "player " << whoMove << endl;
}

//--------------------------------------------------------------
void cpuGame::keyPressed(int key) {

}

//--------------------------------------------------------------
void cpuGame::keyReleased(int key) {
}

//--------------------------------------------------------------
void cpuGame::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void cpuGame::mouseDragged(int x, int y, int button){
    //when dragging some pearl
    if(bMoving == true)
    {
        if(timer.getbReached() == false)//time ISN'T up
        {
            if(whoMove)//player
            {
				/*if(map2.bCalculating == false && map2.bCalculated == false)
					map2.calculate();//calculate the step of next round for cpu*/
                if(((ofGetMouseX()>50)&&(ofGetMouseX()<350))&&((ofGetMouseY()>150)&&(ofGetMouseY()<450)))
                    map1.slip();
            }

            /*else //player2
            {
                if(((ofGetMouseX()>650)&&(ofGetMouseX()<950))&&((ofGetMouseY()>150)&&(ofGetMouseY()<450)))
                    map2.cpuSlip();
            }*/

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
                    //++datum[player2-1].lose;
                    ++datum[player1-1].win;
                    cpuGameOver = true;
                    timecpuGameOver = ofGetElapsedTimef();
                }

                map1.fallDown();
				bMoving = false;
				timer.stopCountDown();
				whoMove = !(whoMove);
            }

            /*else
            {
                map2.moving = false;
                if(map2.calCombo() <=  p1.HP)
                    p1.HP -= map2.calCombo();
                else
                {
                    p1.HP = 0;
                    ++datum[player1-1].lose;
                    ++datum[player2-1].win;
                    cpuGameOver = true;
                    timecpuGameOver = ofGetElapsedTimef();
                }

                map2.fallDown();
            }*/


        }
    }

}

//--------------------------------------------------------------
void cpuGame::mousePressed(int x, int y, int button){
    // for countdown, to let player move the pearl in correct time
    if(bMoving == false)
    {
        if(whoMove)//player1 turn
        {
            if(((ofGetMouseX()>=50)&&(ofGetMouseX()<=350))&&((ofGetMouseY()>=150)&&(ofGetMouseY()<=450)))
            {
                bMoving = true;
                map1.moving = true;
                map1.getTargetPearl();
                timer.countDown();

            }
        }
        else//cpu's turn
        {
            if(((ofGetMouseX()>=650)&&(ofGetMouseX()<=950))&&((ofGetMouseY()>=150)&&(ofGetMouseY()<=450))&&map2.moving == false)
            {
                //bMoving = true;
                map2.moving = true;
				int ini_loc = map2.calculate();
                map2.getTargetPearl(ini_loc);
                timer.countDown();
            }

        }
    }
}

//--------------------------------------------------------------
void cpuGame::mouseReleased(int x, int y, int button){
    if(bMoving == true)//when dragging some pearl,then give up the remain_time
    {
        if(whoMove)
        {
            map1.moving = false;
            if(map1.calCombo() < p2.HP)
                p2.HP -= map1.calCombo();
            else
            {
                  p2.HP = 0;
                  //++datum[player2-1].lose;
                  ++datum[player1-1].win;
                  cpuGameOver = true;
                  timecpuGameOver = ofGetElapsedTimef();
            }
            map1.fallDown();
			bMoving = false;
			timer.stopCountDown();
			whoMove = !(whoMove);
        }
        /*else
        {
            map2.moving = false;
            if(map2.calCombo() <=p1.HP)
                p1.HP -= map2.calCombo();
            else
            {
                  p1.HP = 0;
                  ++datum[player1-1].lose;
                  ++datum[player2-1].win;
                  cpuGameOver = true;
                  timecpuGameOver = ofGetElapsedTimef();
            }

            map2.fallDown();
        }*/

    }
}

//--------------------------------------------------------------
void cpuGame::windowResized(int w, int h){

}

//--------------------------------------------------------------
void cpuGame::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void cpuGame::dragEvent(ofDragInfo dragInfo){

}
void cpuGame::reset(){
    p1.HP = MAXHP;
    p2.HP = MAXHP;
    bcpuGameFinished = false;
    cpuGameOver = false;
}
