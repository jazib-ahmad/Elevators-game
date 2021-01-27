#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

Person::Person(string input_string) : Person() {
    //TODO: Implement non-default constructor
    stringstream parse(input_string);
       parse >> turn;
       char currentFloorIndicator;
       parse >> currentFloorIndicator;
       parse >> currentFloor;
       char targetFloorIndicator;
       parse >> targetFloorIndicator;
       parse >> targetFloor;
       char angerLevelIndicator;
       parse >> angerLevelIndicator;
       parse >> angerLevel;
    
}

bool Person::tick(int currentTime) {
    //TODO: Implement tick
    if (currentTime % TICKS_PER_ANGER_INCREASE == 0)
        {
            angerLevel++;
        }
        if (angerLevel >= MAX_ANGER)
        {
            return true;
        }
        else
        {
            return false;
        }

        //Returning false to prevent compilation error
        return false;

    
}

void Person::print(ostream &outs) {    
    //TODO: Implement print
    outs << "f" << currentFloor << "t" << targetFloor
            << "a" << angerLevel << endl;
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}

int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {    
    return currentFloor;
}

int Person::getTargetFloor() const {    
    return targetFloor;
}

int Person::getAngerLevel() const {    
    return angerLevel;
}

ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}
