// SimWorld.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "StillsuitSim.h"
#include "HumanSim.h"
#include <thread>
#include <atomic>
#include <time.h>
#include <math.h>
#include <random>

const int MIN_PER_DAY = 1440;
const int MIN_TEMP = 50;
const int MAX_TEMP = 100;
const int SLEEP_TIME = 100;
const double PI = 3.14159265359;


void sendToHuman(HumanSim* human, int time, int temp) {
    
    human->setWorldInfo(time,temp);

}


int main()
{
 
    srand(time(NULL));
    std::cout << "Hello World!\n";
    StillsuitSim* suit = new StillsuitSim();
    HumanSim* human = new HumanSim("Dave",suit);
    int initTemp= MIN_TEMP+rand() % 10 + 1; //within 10 degrees of min
    double width = 7.5;
    double a = -1.0/(MIN_PER_DAY*width);
    double b = MIN_PER_DAY/ (MIN_PER_DAY * width);
    double c = 0;
    //send time and temp
    for (int i = 1; i <= MIN_PER_DAY; i++) {
        //use quadratic formula to make the temp rise gradually til mid day and then
        //start decreasing again.
        double tempDiff = i*i*a + b*i+ c;
        //randomly adjust tempDiff up or down by a small amount
        double r = rand() % 4-2.0;
        int temp = tempDiff+r+initTemp;
        //create thread so human can deal with it independent of this thread
        thread tempThread(sendToHuman,human, i, temp);
        tempThread.detach();
        suit->setTime(i);
        this_thread::sleep_for(chrono::milliseconds(SLEEP_TIME));
    }

}
