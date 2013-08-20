#include "snakebody.h"
#include "food.h"
#include <iostream>

snakebodymanager::snakebodymanager(){
    bodycount = 1;          //number of body segments including head
    notlosing = true;       //true = not dead, false = yes dead
}

void snakebodymanager::bodygrow(){
    bodycount++;
    snakebody newbody(-1, -1);      //this creates a blank body space in order to prevent reading vector[-1]
    totalbody.push_back(newbody);   //add the blank body to the vector
}

int snakebodymanager::headmovedirection(int direction){
    int stat = direction % 2;       //determine whether direction is a positive x or y or a negative x or y
        for(int i = 1; i < bodycount; i++)
        {
            totalbody[bodycount-i] = totalbody[bodycount-i-1];      //set the very last segment to the second last position, then second last position to third last position, etc.
            totalbody[bodycount-i].body.setPosition(totalbody[bodycount-i-1].partposx * 24, totalbody[bodycount-i-1].partposy * 24);    //sets up the sprites
        }
    if(direction > 2)           //a direction > 2 is either left or right
        totalbody[0].partposx = totalbody[0].partposx + stat * 2 -1;    //maths
    if(direction < 3)           //a direction < 3 is either up or down.  If direction is 0, it is read as down
        totalbody[0].partposy = totalbody[0].partposy - stat * 2 +1;    //maths
    if(totalbody[0].partposx < 0 || totalbody[0].partposx > 29 || totalbody[0].partposy < 0 || totalbody[0].partposy > 24) //hit the wall loss conditions
    {
        notlosing = false;      //failed
        return 0;               //force quit function
    }
    if (gamemap [totalbody[0].partposx][totalbody[0].partposy] == 1) //hit self loss condition.  Could be added to other loss condition to conserve space, but less confusing this way,
    {
        notlosing = false;      //failed
        return 0;               //force quit function
    }
    if (gamemap [totalbody[0].partposx][totalbody[0].partposy] < 2)     //if snake has not moved onto a food space
        gamemap [totalbody[0].partposx][totalbody[0].partposy] = 1;     //snake is now on this space.  This code is necessary in order to prevent food spaces from being overwritten before being read
    if (gamemap [totalbody.back().partposx][totalbody.back().partposy] == 1)    //last segment of snake has passed
        gamemap [totalbody.back().partposx][totalbody.back().partposy] = 0;     //there is no longer a snake in this position
    return 0;
}

snakebody::snakebody(){
    partposx = 15;
    partposy = 10;
    body.setPosition(partposx*24, partposy*24);
} //default constructor. This is the starting position

snakebody::snakebody(float x, float y){
    partposx = x;
    partposy = y;
} //overload constructor. This is used to place a placeholder object offscreen
