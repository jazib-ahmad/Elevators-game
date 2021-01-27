#include "Floor.h"

using namespace std;

int Floor::tick(int currentTime) {
    //TODO: Implement tick
    int numExplodedPeople = 0;
    int index = 0;
    int listExplodedPeople[MAX_PEOPLE_PER_FLOOR] = {};
        for (int i = 0; i < numPeople; i++)
        {
            if (people[i].tick(currentTime) == true)
            {
                numExplodedPeople++;
                listExplodedPeople[index] = i;
                index++;
                
            }
        }
       
        removePeople(listExplodedPeople, numExplodedPeople);
        return numExplodedPeople;

    //returning 0 to prevent compilation error
    return 0;
}

void Floor::addPerson(Person p, int request) {
    //TODO: Implement addPerson
    if (numPeople < MAX_PEOPLE_PER_FLOOR)
        {
            people[numPeople] = p;
            numPeople++;
            if (request > 0)
            {
                hasUpRequest = true;
            }
            else if (request < 0)
            {
                hasDownRequest = true;
            }
        }
}

void Floor::removePeople(int indicesToRemove[MAX_PEOPLE_PER_FLOOR], int numPeopleToRemove) {
    //TODO: Implement removePeople
   
    int i;
    int j;
        for (i = 0; i < numPeopleToRemove - 1; i++)
       {
          
        // Last i elements are already in place
        for (j = 0; j < numPeopleToRemove - i -1; j++)
          {
            if (indicesToRemove[j] > indicesToRemove[j+1])
              {
                  int temp = indicesToRemove[j];
                      indicesToRemove[j] = indicesToRemove[j+1];
                      indicesToRemove[j+1] = temp;
              }
                
          }
        }
   

//    for(int a = numPeopleToRemove - 1 ; a >= 0; a--)
//    {
//        if(a != numPeople -1)
//        {
//        for(int b = indicesToRemove[a];b < numPeople - 1; b++)
//        {
//            people[b] = people[b+1];
//        }
//               }
//    }
//
    
    for(int a = 0 ; a < numPeopleToRemove;a++ )
    {
        for(int b = indicesToRemove[a] -a;b<numPeople -1;b++)
        {
            people[b] = people[b+1];
        }
        numPeople--;
    }
   // numPeople = numPeople - numPeopleToRemove;
    resetRequests();
   
}

void Floor::resetRequests() {
    //TODO: Implement resetRequests
    int numUpRequests = 0;
    int numDownRequests = 0;
    for(int c = 0 ; c < numPeople; c++)
    {
        if(people[c].getTargetFloor() - people[c].getCurrentFloor() > 0)
        {
            numUpRequests++;
        }
        if(people[c].getTargetFloor() - people[c].getCurrentFloor() < 0)
        {
            numDownRequests++;
        }
        
    }
    if(numUpRequests > 0)
    {
        hasUpRequest = true;
        
    }
    else
    {
        hasUpRequest = false;
    }
    if(numDownRequests > 0)
    {
        hasDownRequest = true;
        
    }
    else
    {
        hasDownRequest =false;
    }
    
    
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
