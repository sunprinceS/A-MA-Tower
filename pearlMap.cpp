#pragma once
#include"ofMain.h"
#include"pearlMap.h"

    void pearlMap::slip()
    {
        if(playerWho) // player1
        {
            if(((ofGetMouseX()>=50)&&(ofGetMouseX()<=350))&&((ofGetMouseY()>=150)&&(ofGetMouseY()<=450)))
            {
                //change with up one
                if((ofGetMouseX()>=target_pearl->posX)&&(ofGetMouseX()<=(target_pearl->posX)+50) &&((ofGetMouseY()<=target_pearl->posY)&&(ofGetMouseY()>=target_pearl->posY-50)))
                {
                    if(target>5) //target -6 >=0
                    {
                        pearl_swap(target_pearl,find_pearl(target-6));
                        target -=6;
                    }
                }
                //change with down one
                else if((ofGetMouseX()>=target_pearl->posX)&&(ofGetMouseX()<=(target_pearl->posX)+50) &&((ofGetMouseY()>=(target_pearl->posY)+50)&&(ofGetMouseY()<=(target_pearl->posY)+100)))
                {
                    if(target  <30) //target +6 < 36
                    {
                        pearl_swap(target_pearl,find_pearl(target+6));
                        target +=6;
                    }
                }
                //change with left one
                else if((ofGetMouseX()>=(target_pearl->posX)-50)&&(ofGetMouseX()<=target_pearl->posX) &&((ofGetMouseY()>=target_pearl->posY)&&(ofGetMouseY()<=(target_pearl->posY)+50)))
                {
                    if(target > 0 ) //target -1 >= 0
                    {
                        pearl_swap(target_pearl,find_pearl(target-1));
                        --target;
                    }

                }
                //change with right one
                else if((ofGetMouseX()>=(target_pearl->posX)+50)&&(ofGetMouseX()<=(target_pearl->posX)+100) &&((ofGetMouseY()>=target_pearl->posY)&&(ofGetMouseY()<=(target_pearl->posY)+50)))
                {
                    if(target < 35) //target +1 <36
                    {
                        pearl_swap(target_pearl,find_pearl(target+1));
                        ++target;
                    }

                }
                else
                {
                    //cout << ">w<" << endl;
                }
            }
        }
        else //player 2
        {
            if(((ofGetMouseX()>=650)&&(ofGetMouseX()<=950))&&((ofGetMouseY()>=150)&&(ofGetMouseY()<=450)))
            {
                //change with up one
                if((ofGetMouseX()>=target_pearl->posX)&&(ofGetMouseX()<=(target_pearl->posX)+50) &&((ofGetMouseY()<=target_pearl->posY)&&(ofGetMouseY()>=target_pearl->posY-50)))
                {
                    if(target>5) //target -6 >=0
                    {
                        pearl_swap(target_pearl,find_pearl(target-6));
                        target -=6;
                    }
                }
                //change with down one
                else if((ofGetMouseX()>=target_pearl->posX)&&(ofGetMouseX()<=(target_pearl->posX)+50) &&((ofGetMouseY()>=(target_pearl->posY)+50)&&(ofGetMouseY()<=(target_pearl->posY)+100)))
                {
                    if(target  <30) //target +6 < 36
                    {
                        pearl_swap(target_pearl,find_pearl(target+6));
                        target +=6;
                    }
                }
                //change with left one
                else if((ofGetMouseX()>=(target_pearl->posX)-50)&&(ofGetMouseX()<=target_pearl->posX) &&((ofGetMouseY()>=target_pearl->posY)&&(ofGetMouseY()<=(target_pearl->posY)+50)))
                {
                    if(target > 0 ) //target -1 >= 0
                    {
                        pearl_swap(target_pearl,find_pearl(target-1));
                        --target;
                    }
                }
                //change with right one
                else if((ofGetMouseX()>=(target_pearl->posX)+50)&&(ofGetMouseX()<=(target_pearl->posX)+100) &&((ofGetMouseY()>=target_pearl->posY)&&(ofGetMouseY()<=(target_pearl->posY)+50)))
                {
                    if(target < 35) //target +1 <36
                    {
                        pearl_swap(target_pearl,find_pearl(target+1));
                        ++target;
                    }
                }
                else
                {
                    //cout << ">w<" << endl;
                }
            }
        }

    }
	void pearlMap::cpuSlip()
	{
		if(this->cpuDir_loc == STEPSIZE)  //slip finished
		{
			bSlipped = true;
			this->moving = false;
			cpuDir_loc = 0;
			//countDFS = 0;
			//max_loc=0;
			MaxDFS = -30000;
		}
		else
		{
			if(this->bCalculated)
			{
				if     (cpuDir[cpuDir_loc] == U && target >= 6)
				{
					pearl_swap(target_pearl,find_pearl(target-6));
					target -=6;
				}
				else if(cpuDir[cpuDir_loc] == D && target < 30)
				{
					pearl_swap(target_pearl,find_pearl(target+6));
					target +=6;
				}
				else if(cpuDir[cpuDir_loc] == L && target >= 1)
				{
					pearl_swap(target_pearl,find_pearl(target-1));
					--target;
				}
				else if(cpuDir[cpuDir_loc] == R && target <35)
				{
					pearl_swap(target_pearl,find_pearl(target+1));
					++target;
				}
				else
					cout << "ERROR in cpuSlip,calculation has problems" << endl;

				++cpuDir_loc;
			}
		}

	}
	void pearlMap::getTargetPearl(int _loc) //for cpu player
	{
		if(moving)
		{
			target = _loc;
			target_pearl = find_pearl(target);
			target_pearl->bTargeted = true;
		}
	}
    void pearlMap::getTargetPearl() //for human player
    {
        if(moving)
        {
            int x,y;
            //get target pearl
            if(playerWho) //player1
            {
                if(((ofGetMouseX()>=50)&&(ofGetMouseX()<=350))&&((ofGetMouseY()>=150)&&(ofGetMouseY()<=450)))
                {
                    x = (ofGetMouseX()-49)/50;
                    y = (ofGetMouseY()-149)/50;
                }
            }
            else // player2
            {
                if(((ofGetMouseX()>=650)&&(ofGetMouseX()<=950))&&((ofGetMouseY()>=150)&&(ofGetMouseY()<=450)))
                {
                     x = (ofGetMouseX()-649)/50;
                     y = (ofGetMouseY()-149)/50;
                }
            }
            target = 6*y+x;//calculate target
            //prevent target out of range
            if(target >=0 && target <36)
                target_pearl = find_pearl(target);
            else
                target_pearl = NULL;
        }
        target_pearl->bTargeted = true;
    }

    void pearlMap::fallDown()
    {
        while(fallDownPair.empty() == false)
        {
            comboPearl tmp = fallDownPair.back();//get access to the fallDOwnPair
            int loc = tmp.loc;
            for(int i=0;i<tmp.number;++i)
            {
                if(tmp.dir == 0)//horizontal bomb
                {
                    if(removeOrNot[loc] == true)
                    {
                        pearl newPearl(playerWho);
                        newPearl.number = loc;
                        switch(rand()%6)
                        {
                            case 0:
                           newPearl.attribute = red;
                            break;
                            case 1:
                            newPearl.attribute = yellow;
                            break;
                            case 2:
                            newPearl.attribute = green;
                            break;
                            case 3:
                            newPearl.attribute = blue;
                            break;
                            case 4:
                            newPearl.attribute = purple;
                            break;
                            case 5:
                            newPearl.attribute = pink;
                            break;

                        }
                        pearls.push_back(newPearl);//refresh the newPearl
                        removeOrNot[loc] = false;
                    }
                    ++loc;
                }

                else // vertical bomb
                {
                    if(removeOrNot[loc] == true)
                    {
                        pearl newPearl(playerWho);
                        newPearl.number = loc;
                        switch(rand()%6)
                        {
                            case 0:
                           newPearl.attribute = red;
                            break;
                            case 1:
                            newPearl.attribute = yellow;
                            break;
                            case 2:
                            newPearl.attribute = green;
                            break;
                            case 3:
                            newPearl.attribute = blue;
                            break;
                            case 4:
                            newPearl.attribute = purple;
                            break;
                            case 5:
                            newPearl.attribute = pink;
                            break;
                        }
                        pearls.push_back(newPearl);//refresh the newPearl
                        removeOrNot[loc] = false;
                    }
                    loc+=6;
                }
            }
            fallDownPair.pop_back();
        }
    }

	int pearlMap::calculate()
	{
		bSlipped = false;
		/*calculate begin*/
		int ini_target = rand()%36;
		int _target = ini_target;
		for(int i=0;i<MAPSIZE;++i)
        {
            pearl* tmp = find_pearl(i);
            if      (tmp->attribute == red){pearls_tmp[i] = 0;}
            else if (tmp->attribute == yellow){pearls_tmp[i] = 1;}
            else if (tmp->attribute == green){pearls_tmp[i] = 2;}
            else if (tmp->attribute == blue){pearls_tmp[i] = 3;}
            else if (tmp->attribute == purple){pearls_tmp[i] = 4;}
            else {pearls_tmp[i] = 5;}
        }
		/*Idiot*/
		//AI();
		//AI();
		/*Greedy Method*/
		//AI_1(ini_target);
		/*DFS*/
		for(int j=1;j<=10;++j)
		{
            cout << (j-1)*10 <<  " ~ " << (10*j)-1 << "@" << ofGetElapsedTimef() <<endl;
			//cout << "LALALALLALALALALALA" << endl;
			DFS(1,_target,U,j); testDir[0] = U;
			DFS(1,_target,D,j); testDir[0] = D;
			DFS(1,_target,L,j); testDir[0] = L;
			DFS(1,_target,R,j); testDir[0] = R;
			MaxDFS = -30000;
			//DFSdecide(j);
			//cout << "LALALALLAL" << endl;
			for(int i=10*(j-1);i<j*10;++i)
			{
				if     (cpuDir[i] == U && _target >= 6)
				{
					pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[_target-6]);
					_target -=6;
				}
				else if(cpuDir[i] == D && _target < 30)
				{
					pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[_target+6]);
					_target +=6;
				}
				else if(cpuDir[i] == L && _target >= 1)
				{
					pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[_target-1]);
					--_target;
				}
				else if(cpuDir[i] == R && _target <35)
				{
					pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[_target+1]);
					++_target;
				}
				else
					cout << "ERROR in cpuSlip@calculate,calculation has problems" << endl;
			}

		}
		bCalculated = true;
		/*calculate end*/
		return ini_target; // return initial target pearl location
	}
    int pearlMap::calCombo()
    {
        attack = 0;
        comboNum = 0;
        //check row
        for(int j=0;j<sqrt(MAPSIZE);++j)
        {
            int loc = 6*j;//every row's 1st element
            queue<pearl*> combo;
            combo.push(find_pearl(loc));
            for(int i=1;i<sqrt(MAPSIZE);++i)
            {
                if(combo.size()<4)
                {
                    pearl* test = find_pearl(loc+1);

                    if(test->attribute == combo.back()->attribute)
                    {
                         combo.push(test);
                         ++loc;
                    }
                    else
                    {
                        while(combo.empty() == false)
                        {
                            combo.pop(); //make it empty
                        }
                        combo.push(test);
                        ++loc;
                    }
                }
                else
                {
                    pearl* test = find_pearl(loc+1);
                    if(test->attribute == combo.back()->attribute)
                    {
                         combo.push(test);
                         ++loc;
                    }
                    else
                    {  //calculate
                        attack += 50*(combo.size());
                        ++comboNum;
                        comboPearl a;
                        a.loc = combo.front()->number;
                        a.dir = 0;
                        a.number = combo.size();
                        bomb(a);
                        fallDownPair.push_back(a);
                        break;
                    }
                }
                if(i==5&&combo.size()>=4)
                {
                    attack += 50*(combo.size());
                    ++comboNum;
                    comboPearl a;
                    a.loc = combo.front()->number;
                    a.dir = 0;
                    a.number = combo.size();
                    bomb(a);
                    fallDownPair.push_back(a);
                }
            }

        }//
        //check column
        for(int i=0;i<sqrt(MAPSIZE);++i)
        {
            int loc = i;
            queue<pearl*> combo;
            combo.push(find_pearl(loc));
            for(int j=1;j<sqrt(MAPSIZE);++j)
            {
                if(combo.size()<4)
                {
                    pearl* test = find_pearl(loc+6);

                    if(test->attribute == combo.back()->attribute)
                    {
                         combo.push(test);
                         loc +=6;
                    }
                    else
                    {
                        while(combo.empty() == false)
                        {
                            combo.pop();
                        }
                        combo.push(test);
                        loc +=6;
                    }
                }
                else
                {
                    pearl* test = find_pearl(loc+6);
                    if(test->attribute == combo.back()->attribute)
                    {
                         combo.push(test);
                         loc +=6;
                    }
                    else
                    {  //calculate
                        attack += 50*(combo.size());
                        ++comboNum;
                        comboPearl a;
						a.loc = combo.front()->number;
                        a.dir = 1;
                        a.number = combo.size();
                        fallDownPair.push_back(a);
                        bomb(a);
                        break;
                    }
                }
                if(j==5&&combo.size()>=4)
                {
                    attack += 50*(combo.size());
                    ++comboNum;
                    comboPearl a;
                    a.loc = combo.front()->number;
                    a.dir = 1;
                    a.number = combo.size();
                    fallDownPair.push_back(a);
                    bomb(a);
                }
            }
        }
        for(int i=0;i<MAPSIZE;++i)
            pearls[i].bTargeted = false;
        attack*=(1+(0.2*comboNum));
        return attack;
    }

	void pearlMap::draw()
	{
	    int currentTargetPearl;
		for(int i=0;i<MAPSIZE;++i)
		{
		    if(pearls[i].bTargeted)
               currentTargetPearl = i;
			this->pearls[i].draw();
		}
		if(this->moving == true&&currentTargetPearl<=35&&currentTargetPearl>=0)
            this->pearls[currentTargetPearl].draw();
	}

	void pearlMap::pearl_swap(pearl* a,pearl* b)//CANNOT change the attribute
	{
		pearl tmp(playerWho);
		tmp.number = a->number;//because I let posX,posY are number-dependent,so we just need to swap the number
		//tmp.bTargeted = a->bTargeted;
		//tmp.attribute = a->attribute;

		a->number = b->number;
		//a->bTargeted = b->bTargeted;
		//a->attribute = b->attribute;

		b->number = tmp.number;
		//b->bTargeted = tmp.bTargeted;
		//b->attribute = tmp.attribute;

	}

	void pearlMap::pearl_swap_cpu(int* a,int* b)
	{
	    int tmp;
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
	void pearlMap::update()
	{
		for(int i=0;i<MAPSIZE;++i)
        {
            pearls[i].update();
        }
	}

    void pearlMap::setPlayer(bool _p)
    {
        playerWho = _p;
        for(int i=0;i<MAPSIZE;++i)
        {
            pearl _pearl(playerWho);
            _pearl.number = i;
            if(playerWho) //player1
            {
                _pearl.posX = 50+(i%6)*50;
                _pearl.posY = 150+(i/6)*50;
            }
            else
            {
                _pearl.posX = 650+(i%6)*50;
                _pearl.posY = 150+(i/6)*50;
            }
            //produce the initial pearlMap
            switch(rand()%6)
            {
                case 0:
                _pearl.attribute = red;
                break;
                case 1:
                _pearl.attribute = yellow;
                break;
                case 2:
                _pearl.attribute = green;
                break;
                case 3:
                _pearl.attribute = blue;
                break;
                case 4:
                _pearl.attribute = purple;
                break;
                case 5:
                _pearl.attribute = pink;
                break;
            }
            /*for test*/

            /*switch((i+1)%6)
            {
                case 0:
                _pearl.attribute = red;
                break;
                case 1:
                _pearl.attribute = yellow;
                break;
                case 2:
                _pearl.attribute = green;
                break;
                case 3:
                _pearl.attribute = blue;
                break;
                case 4:
                _pearl.attribute = purple;
                break;
                case 5:
                _pearl.attribute = pink;
                break;

            }*/
            this->pearls.push_back(_pearl);
        }
    }

    void pearlMap::bomb(comboPearl _p) //_dir shows whether it is horizontal or vertical,horizontal->0,vertical->1  corner->leftest,uppest
	{
		if(_p.dir == 0)//horizontal bomb
		{
			int loc = _p.loc;

			for(int i=0;i<_p.number&&loc <36;++i)
			{
				pearl* a = find_pearl(loc);
				a->bBombing = true;
				removeOrNot[a->number] = true;
				++loc;
				pearlBombing.play();
				//call gameEvent
				static GameEvent newEvent;
				newEvent.message = "pearl "+ofToString(a->number,1)+"\n";
				newEvent.p  = a;
				ofNotifyEvent(GameEvent::events, newEvent);
			}
		}
		else //vertical bomb
		{
            int loc = _p.loc;

			for(int i=0;i<_p.number&&loc<36;++i)
			{
				pearl* a = find_pearl(loc);
				a->bBombing = true;
				removeOrNot[a->number] = true;
				loc+=6;
				pearlBombing.play();
				//call gameEvent
				static GameEvent newEvent;
				newEvent.message = "pearl "+ofToString(a->number,1)+"\n";
				newEvent.p  = a;
				ofNotifyEvent(GameEvent::events, newEvent);
			}
		}
	}

	//just idiot...lol
	void pearlMap::AI()
	{
		for(int i=0;i<STEPSIZE;++i)
		{
			bool ok = false;
			do{
                switch(rand()%4)
                {
                    case 0:
                    cpuDir[i] = U;
                    if(cpuDir[i-1]!=D) ok = true;
                    break;
                    case 1:
                    cpuDir[i] = D;
                    if(cpuDir[i-1]!=U) ok = true;
                    break;
                    case 2:
                    cpuDir[i] = L;
                    if(cpuDir[i-1]!=R) ok = true;
                    break;
                    case 3:
                    cpuDir[i] = R;
                    if(cpuDir[i-1]!=L) ok = true;
                    break;
                    }
            }while(!ok);
		}
	}

	//implemented by Greedy Method
	void pearlMap::AI_1(int _target)
	{
		for(int i=0;i<STEPSIZE;++i)
		{
			if(_target >=6 ) //U
			{
				pearl_swap_cpu(&pearls_tmp[_target],&pearls_tmp[_target-6]);
				scores[0] = heuristic(pearls_tmp);
				cout << "U scores:" << scores[0] << endl;
				pearl_swap_cpu(&pearls_tmp[_target],&pearls_tmp[_target-6]);//recover
			}
			else
				scores[0] = -30000;

			if(_target < 30 ) //D
			{
				pearl_swap_cpu(&pearls_tmp[_target],&pearls_tmp[_target+6]);
				scores[1] = heuristic(pearls_tmp);
				cout << "D scores:" << scores[1] << endl;
				pearl_swap_cpu(&pearls_tmp[_target],&pearls_tmp[_target+6]);//recover
			}
			else
				scores[1] = -30000;

			if(_target >0 ) //L
			{
				pearl_swap_cpu(&pearls_tmp[_target],&pearls_tmp[_target-1]);
				scores[2] = heuristic(pearls_tmp);
				cout << "L scores:" << scores[2] << endl;
				pearl_swap_cpu(&pearls_tmp[_target],&pearls_tmp[_target-1]);//recover
			}
			else
				scores[2] = -30000;

			if(_target<35 ) //R
			{
				pearl_swap_cpu(&pearls_tmp[_target],&pearls_tmp[_target+1]);
				scores[3] = heuristic(pearls_tmp);
				cout << "R scores:" << scores[3] << endl;
				pearl_swap_cpu(&pearls_tmp[_target],&pearls_tmp[_target+1]);//recover
			}
			else
				scores[3] = -30000;

			//excute the best step
			if(findScoreMax(cpuDir[i-1]) == 0)
			{
				pearl_swap_cpu(&pearls_tmp[_target],&pearls_tmp[_target-6]);
				_target-=6;
				cpuDir[i] = U;
				cout << "U" << endl;
			}
			else if(findScoreMax(cpuDir[i-1]) == 1)
			{
				pearl_swap_cpu(&pearls_tmp[_target],&pearls_tmp[_target+6]);
				_target+=6;
				cpuDir[i] = D;
				cout << "D" << endl;
			}
			else if(findScoreMax(cpuDir[i-1]) == 2)
			{
				pearl_swap_cpu(&pearls_tmp[_target],&pearls_tmp[_target-1]);
				--_target;
				cpuDir[i] = L;
				cout << "L" << endl;
			}
			else
			{
				pearl_swap_cpu(&pearls_tmp[_target],&pearls_tmp[_target+1]);
				++_target;
				cpuDir[i] = R;
				cout << "R" << endl;
			}
		}

	}

	short pearlMap::heuristic(int currentTable[])
	{
		short score = 0;
		//check row
		for(int j=0;j<sqrt(MAPSIZE);++j)
		{
			int loc= 6*j;
			queue<int>combo;
			int t = currentTable[loc];
			combo.push(t);
			for(int i=1;i<sqrt(MAPSIZE);++i)
			{
				int test = currentTable[loc+1];
				if(test == combo.back())
				{
					combo.push(test);
					++loc;
				}
				else
				{
					//exception process
					if(i==3 && combo.size()==3)
						score +=3;
					while(combo.empty() == false)
                    {
                        combo.pop(); //make it empty
                    }
					combo.push(test);
					++loc;
					if(i >= sqrt(MAPSIZE)-2) //no more good heuristic score
						break;
				}
			}
			if 	   (combo.size() == 3)	{score+= 3;}
			else if(combo.size() == 4)  {score+=30;}
			else if(combo.size() == 5)	{score+=32;}
			else if(combo.size() == 6)	{score+=35;}
			else if(combo.size()>6) {cout << "ERROR IN HEURISTIC" << endl;}

			while(combo.empty() == false)
            {
                combo.pop(); //make it empty
            }
		}
		//check column
		for(int i=0;i<sqrt(MAPSIZE);++i)
		{
			int loc = i;
			queue<int>combo;
			combo.push(currentTable[loc]);
			for(int j=1;j<sqrt(MAPSIZE);++j)
			{
				int test = currentTable[loc+6];

				if(test == combo.back())
				{
					combo.push(test);
					loc+=6;
				}
				else
				{
					//exception process
					if(j==3 &&combo.size()==3)
						score+=3;
					while(combo.empty() == false)
                    {
                        combo.pop(); //make it empty
                    }
					combo.push(test);
					loc+=6;
					if(j >= sqrt(MAPSIZE)-1)
						break;
				}
			}
			if 	   (combo.size() == 3)	{score+= 3;}
			else if(combo.size() == 4)  {score+=30;}
			else if(combo.size() == 5)	{score+=32;}
			else if(combo.size() == 6)	{score+=35;}
			else if(combo.size()>6) {cout << "ERROR IN HEURISTIC" << endl;}

			while(combo.empty() == false)
            {
                combo.pop(); //make it empty
            }
		}
		return score;
	}
	void pearlMap::DFS(int round,int target,Dir preDir,int j)
	{
	    //cout << "countDFS:" << countDFS << endl;

		if(round < MAXROUND) //1st preDir在前方calculate已做處理
		{
			//U
			if(target >=6 && preDir!=D)
			{
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target-6]);
				testDir[round] = U;
				DFS(round+1,target-6,U,j);
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target-6]);
			}
			//D
			if(target <30&& preDir!=U)
			{
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target+6]);
				testDir[round] = D;
				DFS(round+1,target+6,D,j);
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target+6]);
			}
			//L
			if(target>=1&& preDir!=R)
			{
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target-1]);
				testDir[round] = L;
				DFS(round+1,target-1,L,j);
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target-1]);
			}
			//R
			if(target<36&& preDir!=L)
			{
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target+1]);
				testDir[round] = R;
				DFS(round+1,target+1,R,j);
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target+1]);
			}
		}
		else //round reaches MAXROUND
		{//j:1~10
			short score= DFS_cal(0,target,preDir);
			if(score > MaxDFS)
			{
				MaxDFS = score;
				for(int i=0;i<10;++i){
					cpuDir[(j-1)+i] = testDir[i];
				}
			}
		}
	}

	int pearlMap::DFS_cal(int round,int target,Dir preDir)
	{
		if(round < MAXSEARCHROUND)
		{
			if(target >=6 && preDir!=D)
			{
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target-6]);
				DFS_cal(round+1,target-6,U);
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target-6]);
			}
			//D
			if(target <30 && preDir!=U)
			{
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target+6]);
				DFS_cal(round+1,target+6,D);
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target+6]);
			}
			//L
			if(target>=1 && preDir!=R)
			{
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target-1]);
				DFS_cal(round+1,target-1,L);
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target-1]);
			}
			//R
			if(target<36&& preDir!=L)
			{
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target+1]);
				DFS_cal(round+1,target+1,R);
				pearl_swap_cpu(&pearls_tmp[target],&pearls_tmp[target+1]);
			}
		}
		else
			return heuristic(pearls_tmp);

	}
	/*void pearlMap::DFSdecide(int j)
	{//j:1~10
		//short maxScore = scores[max_loc];
		for(int i=1;i<=10;++i)
		{
			if	   (maxScore%4==0){cpuDir[10*j-i] = U;}
			else if(maxScore%4==1){cpuDir[10*j-i] = D;}
			else if(maxScore%4==2){cpuDir[10*j-i] = L;}
			else 				  {cpuDir[10*j-i] = R;}
			maxScore/=4;
		}
		if(maxScore!=0) cout <<"ERROR IN DFS_decide" << endl;
	}*/
	int pearlMap::findScoreMax(Dir preDir)
	{
		int loc=0;
		bool choose = false;
		for(int i=1;i<4;++i)
		{
			if(scores[loc] < scores[i])
			{
				if(((i==1) && (preDir == U))||((i==2)&&(preDir == R))||((i==3)&&(preDir == L)))
					continue;
				loc = i;
				choose = true;
			}
		}
		if(choose)
			return loc;
		else
		{
			do{
				loc = rand()%4;
			}while(scores[loc]==-30000);
			return loc;
		}
	}

    pearl* pearlMap::find_pearl(int num)
    {
        for(int i=0;i<MAPSIZE;++i)
        {
            if(this->pearls[i].number == num)
                return &this->pearls[i];
        }
        cout << "CANNOT FIND: " << num << endl;
    }
