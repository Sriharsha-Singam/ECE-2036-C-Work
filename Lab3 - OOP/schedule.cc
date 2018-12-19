//
//  schedule.cc
//  
//
//  Created by Sriharsha Singam on 9/30/18.
//
#include <iostream>
#include "maps.h"
#include "schedule.h"
#include <string>
#include <sstream>
#include <cmath>
#include <cstdlib>
#define NUM_LOCATIONS 25

using namespace std;

//Convert Float to a String Value
std::string to_string_float( float n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

//Convert Int to a String Value
std::string to_string_int( int n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

//Generates the Initial Map Route based on what the user enters
void Schedule::generateRoute(Map map){
    
    //Adds to Output for the Output File
    output += "Todo list from worker\n-----------------------------------------------\n";
    float total = 0;
    
    //Build Route List with all distances between each place on the Route
    for(int i = 1; i < NUM_LOCATIONS; i++){
        
        //Get Start and End Place for the Route
        int start = locationToGoTo[i-1].getId();
        int end = locationToGoTo[i].getId();
        
        //Stops when the list ends.
        if(end == 0){
            
            //Adds to Output for the Output File
            output += "TOTAL DISTANCE = "+to_string_float(total)+"\n";
            
            //Call function createInitialRoute for next set of outputs
            createInitialRoute(map);
            return;
        }
        
        float distance = calcDistance(map.locations[start-1],map.locations[(end-1)]);
        
        //Calculates Total Distance
        total = total+distance;
        
        //Adds to Output for the Output File
        output += ""+(map.locations[(start-1)].getName()) + "(" + to_string_int(start) + ") to " + (map.locations[(end-1)].getName()) + "(" + to_string_int(end) + ") = " + to_string_float(distance) + "\n";
    }
}

//Gets input values from user that detail the route list of locations
void Schedule::getToDoList(){
    int x = 0;
    locationToGoTo[0].setId(1);
    for(int i = 1; i < NUM_LOCATIONS; i++){
        
        //Get List Values
        std::cin >> x;
        
        //Ends when user enters 0
        if(x == 0){
            locationToGoTo[i].setId(1);
            setNumLocToVisit(i+1);
            return;
        }else{
            
            //Adds values to MapLocation Array: locationToGoTo[]
            locationToGoTo[i].setId(x);
        }
    }
}

//Returns Distance between two different locations
float Schedule::calcTotalDistance(Map map){
    float totalDistance = 0.0;
    
    //Calculates and Adds the distance between each location on the Array: routeList
    for(int i = 1; i < NUM_LOCATIONS; i++){
        if(routeList[i] == 0){
            float distance = calcDistance(map.locations[routeList[i-1]-1],map.locations[0]);
            totalDistance+=distance;
            return totalDistance;
        }else{
            float distance = calcDistance(map.locations[routeList[i-1]-1],map.locations[routeList[i]-1]);
            totalDistance+=distance;
        }
    }
    return totalDistance;
}

//Swaps two Array indices
void Schedule::swap(int one, int two){
    int swap = routeList[one];
    routeList[one] = routeList[two];
    routeList[two] = swap;
}

//Changes the routeList (list of all location the user wants to go to) to make a list
// of all locations that are closet to each other -- Not Optimized
void Schedule::createInitialRoute(Map map){
    int allVals[NUM_LOCATIONS];
    allVals[0] = 0;
    
    //Get all value inputed by user to local array variable: allVals
    for(int i = 1; i < NUM_LOCATIONS; i++){
        allVals[i] = locationToGoTo[i].getId();
    }
    
    routeList[0] = 1;
    
    //Goes through each location and finds the closest location to it and places it in the new array
    for(int i = 0; i < NUM_LOCATIONS; i++){
        int id = routeList[i];
        int lowDistance = 500;
        int lowId = 0;
        for(int j = 0; j < NUM_LOCATIONS; j++){
            int id2 = allVals[j];
            
            //Makes sure that the for loop only goes over the inputted values
            if(id2 != 0 && j != (getNumLocToVisit()-1)){
                float distance = calcDistance(map.locations[id-1],map.locations[id2-1]);
                if(distance != 0){
                    if(distance < lowDistance){
                        lowId = j;
                        lowDistance = distance;
                    }
                }
            }
        }
        
        //Adds the next value to routeList
        routeList[i+1] = allVals[lowId];
        //Sets current index in array "allVals" to 0 so that it is not used again
        allVals[lowId] = 0;
        
    }
    //Adds to Output for the Output File
    output += "\n\nCreate initial path with nearest neighbor hueristic\n-----------------------------------------------\n";
    
    //Adds to Output for the Output File
    printOutput(map);
    
    //Call function greedyOptimization for next set of outputs
    greedyOptimization(map);
}

//Adds looped route output to string variable output -- to eventually load the result to the output.txt file
void Schedule::printOutput(Map map){
    
    //Initialize total distance -- for adding
    float totalDistance = 0.0;
    
    //Looping through each route to add it to output
    for(int i = 1; i < NUM_LOCATIONS; i++){
        
        //Check for end of route indices
        if(routeList[i] == 0){
            float distance = calcDistance(map.locations[routeList[i-1]-1],map.locations[0]);
            
            //Adding to total distance
            totalDistance+=distance;
            
            //Adds to Output for the Output File
            output += ""+(map.locations[routeList[i-1]-1].getName()) + "(" + to_string_int(routeList[i-1]) + ")" + " to " + (map.locations[0].getName()) + "(1) = " +to_string_float(distance)+"\n";
            output += "TOTAL DISTANCE = " + to_string_float(totalDistance) + "\n";
            return;
        }else{
            float distance = calcDistance(map.locations[routeList[i-1]-1],map.locations[routeList[i]-1]);
            
            //Adding to total distance
            totalDistance+=distance;
            
            //Adds to Output for the Output File
            output += ""+(map.locations[routeList[i-1]-1].getName()) + "(" + to_string_int(routeList[i-1]) + ")" + " to " + (map.locations[routeList[i]-1].getName()) +"(" + to_string_int(routeList[i]) + ") = " + to_string_float(distance) +"\n";
        }
    }
}

//Get Route List for Greedy Optimization
void Schedule::greedyOptimization(Map map){
    int numLocs = 0;
    for(int i = 0; i < NUM_LOCATIONS; i++){
        if(routeList[i] == 0){
            numLocs = i;
            break;
        }
    }
    float benchMark = calcTotalDistance(map);
    
    //Swapping through random Route List indices to find a local minimum
    for(int i = 0; i < 100*numLocs; i++){
        
        //Get both positions
        int pos1 = rand()%(numLocs-1)+1;
        int pos2 = rand()%(numLocs-1)+1;
        
        //Swapping the 2 indices in a global private array: routeList
        swap(pos1,pos2);
        
        //Checking if swap created a lower total distance
        float distance = calcTotalDistance(map);
        if(distance > benchMark){
            //Swapping values back to the original array since it was NOT a lower distance -- Bad Swap
            swap(pos1,pos2);
        }else if(distance < benchMark){
            //Good swap -- making it the new bench mark
            benchMark = distance;
        }
    }
    
    //Adds to Output for the Output File
    output += "\n\nGreedy algorithm with random swapping\n-----------------------------------------------\n";
    printOutput(map);
    
    //Call function SAOptimization for next set of outputs
    SAOptimization(map);
}
void Schedule::SAOptimization(Map map){
    float prob;
    float throwDice;
    int numItemsToDo = 0;
    for(int i = 0; i < NUM_LOCATIONS; i++){
        if(routeList[i] == 0){
            numItemsToDo = i;
            break;
        }
    }
    //this is a linear ramping down of the temperature
    for (float temp = 15.0; temp >=0; temp-=0.1){
        for (int i = 0; i < numItemsToDo*100; i++) {
            //randomly pick two elements to swaps between // index 1 and numItemsToDo-1
            int pos1 = rand()%(numItemsToDo-1)+1;
            int pos2 = rand()%(numItemsToDo-1)+1;
            //I will allow pos1 and pos2 to be possibly equal for simplicity float dist1 = calcTotalDistance(RouteList);
            float dist1 = calcTotalDistance(map); // Calculating distance1
            swap(pos1, pos2);
            float dist2 = calcTotalDistance(map);
            dist2 < dist1 ? prob =1.0 : prob = exp(-(dist2 - dist1)/(0.5*temp));
            throwDice = static_cast<float>(rand())/RAND_MAX;
            if (throwDice > prob) //reject the swap .. i.e. swap back
            {swap(pos1,pos2);}
        }
    }//end temperature loop
    
    //Adds to Output for the Output File
    output += "\n\nSimulated annealing (SA) algorithm with random swapping\n-----------------------------------------------\n";
    printOutput(map);
}

//Calculate distance between 2 locations in Pawnee
float Schedule::calcDistance(MapLocation loc1, MapLocation loc2){
    float xVal = fabs(loc1.getX() - loc2.getX());
    float yVal = fabs(loc1.getY() - loc2.getY());
    return (xVal+yVal);
}

//Setter and Getter for numLocToVisit
void Schedule::setNumLocToVisit(int numLoc){numLocToVisit = numLoc;}
int Schedule::getNumLocToVisit(){return numLocToVisit;}

//Default Constructor for Class: Schedule
Schedule::Schedule(){}

//Constructor (with input for Employee name) for Class: Schedule
Schedule::Schedule(std::string name){
    employeeName = name;
    cout<< "Good Morning "<<employeeName<<"!!!\n\nPlease list the locations that you need to visit today\n( input 0 to end your list )\n\n1 (City Hall Start)" << endl;
}

//Getter for the string variable: output -- for creating output.txt
std::string Schedule::getOutPut(){
    return output;
}
