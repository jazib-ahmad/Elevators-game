#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"

using namespace std;

Move::Move(string commandString) : Move() {
    //TODO: Implement non-default constructor
    stringstream parse(commandString);
        char c1;
        char c2;
        int floorNum;
        int eID;
        parse >> c1;
        if (c1 == 'e' || c1 == 'E')
        {
            parse >> eID;
            elevatorId = eID;
            parse >> c2;
            if (c2 == 'f'|| c2 == 'F')
            {
                parse >> floorNum;
                targetFloor = floorNum;

            }
            else if (c2 == 'p' || c2 == 'P')
            {
                isPickup = true;
//                isSave = false;
//                isQuit = false;
//                isPass = false;
            }
        }
        else if (c1 == 'S'|| c1 == 's')
        {
            isSave = true;
//            isQuit = false;
//            isPass = false;
//            isPickup = false;

        }
        else if (c1 == 'Q'|| c1 == 'q')
        {
            isQuit = true;
//            isPass = false;
//            isPickup = false;
//            isSave = false;
            
        }
        else
        {
            isPass = true;
//            isPickup = false;
//            isSave = false;
//            isQuit = false;
            
        }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    //TODO: Implement isValidMove
    if(isPass == true)
    {
        return true;
    }
    else if(isQuit == true)
    {
        return true;
    }
    else if(isSave == true)
    {
        return true;
    }
    else if(isPickup == true)
    {
        if (elevatorId >= 0 && elevatorId < NUM_ELEVATORS && elevators[elevatorId].isServicing() == false)
                   {
                       return true;
                   }
    }
    else if(targetFloor >= 0 && targetFloor < NUM_FLOORS && elevators[elevatorId].getCurrentFloor()!= targetFloor && elevatorId >= 0 && elevatorId < NUM_ELEVATORS && elevators[elevatorId].isServicing() == false)
    {
        return true;
    }
    else
    {
        return false;
    }
    
    
    
//    if (isPass == true ||isQuit == true ||isSave == true)
//       {
//           return true;
//       }
//       if ((isPickup == true) || (targetFloor != -1))
//       {
//           if ((elevatorId >= 0) && (elevatorId < NUM_ELEVATORS) && (elevators[elevatorId].isServicing() == false))
//           {
//               return true;
//           }
//       }
//       if (targetFloor != -1)
//       {
//           if ((targetFloor >= 0) && (targetFloor < NUM_FLOORS) && (targetFloor != elevators[elevatorId].getCurrentFloor()))
//           {
//               return true;
//           }
//
//       }
//
       //Returning false to prevent compilation error
       return false;
    
    
    
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, const Floor& pickupFloor) {
    //TODO: Implement setPeopleToPickup
    
    
//    While it does this, it also tracks a few other things:
//
//    As it adds indices, it increments numPeopleToPickup to maintain accurate sizing information for peopleToPickup. This starts at 0 and increments for each index in the string.
//    As it adds indices, it uses them to lookup the corresponding Person’s angerLevel. This information can be found from the argument pickupFloor, which contains the array of all people on this floor. Once the angerLevel is found, totalSatisfaction (which also is initialized to 0) is incremented by MAX_ANGER - angerLevel.
//    Finally, the targetFloor is also calculated using the following rule. The targetFloor is equal to the targetFloor of the Person who has to travel the furthest from the currentFloor to reach their destination.
//    For example, if currentFloor were 5 and we were picking up 3 people, with targetFloors 6, 7, and 8, our Move’s targetFloor would be set to 8.
//    Similarly, if currentFloor were 5 and we were picking up 3 people, with targetFloors 1, 2, and 3, our Move’s targetFloor would be set to 1.
    
    int furthestDistance = 0;
    
    
    for(int i =0; i < pickupList.length();i++)
    {
        char c = pickupList.at(i);
        int x = c - '0';
        peopleToPickup[i] = x;
        numPeopleToPickup++;
        int anger = pickupFloor.getPersonByIndex(x).getAngerLevel();
        totalSatisfaction = totalSatisfaction + (MAX_ANGER - anger);
        int targetForPerson = pickupFloor.getPersonByIndex(x).getTargetFloor();
        int absTarget = abs(currentFloor - targetForPerson);
        if(absTarget > furthestDistance)
        {
            furthestDistance = absTarget;
        }
    }
    for(int i =0; i < numPeopleToPickup;i++)
    {
        
        int targetForPerson = pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor();
        int absTarget = abs(currentFloor - targetForPerson);
        if(absTarget == furthestDistance)
        {
            targetFloor = targetForPerson;
        }
    }

    
    
    
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
