#pragma once
#include "ofMain.h"

class Timer
{
public:
    Timer():current_time(0),total_time(10)
    {
        start_time = 0;
        bReached = false;
        bCountDown = false;
    }
    void update()
    {
        if(bCountDown)
        {
            current_time = (double)ofGetElapsedTimef() - start_time;
            if(current_time >= total_time && !bReached)
            {
                bReached = true;
                //cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            }
        }
        else
        {
            current_time = 0;
        }
    }
    void draw()
    {
        float bar_width = 300;

        // the background to the progress bar
        ofSetColor(100);
        ofRect((ofGetWidth()-bar_width)/2, 50, bar_width, 30);

        // get the percantage of the timer
        float pct = ofMap(current_time, 0.0, total_time, 0.0, 1.0, true);
        ofSetHexColor(0xf02589);
        ofRect((ofGetWidth()-bar_width)/2, 50, bar_width*(1-pct), 30);
    }
    void countDown()
    {
        bReached = false;
        bCountDown = true;
        start_time = (double)ofGetElapsedTimef();
    }
    void stopCountDown()
    {
        bCountDown = false;
    }
    bool getbReached(){return bReached;}
private:
    double start_time;
    double current_time;
    double total_time;
    bool bReached;
    bool bCountDown;
};
