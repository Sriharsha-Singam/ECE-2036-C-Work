//
//  schedule.h
//  
//
//  Created by Sriharsha Singam on 9/30/18.
//

#include <string>
#include "maps.h"
#include <iostream>

#define NUM_LOCATIONS 25

#ifndef SCHEDULE_H
#define SCHEDULE_H

class Schedule{
    public:
        void generateRoute(Map map);
        void getToDoList();
        Schedule();
        Schedule(std::string name);
        void setNumLocToVisit(int numLoc);
        int getNumLocToVisit();
        std::string getOutPut();
    private:
        float calcTotalDistance(Map map);
        void swap( int, int);
        void createInitialRoute(Map map);
        void greedyOptimization(Map map);
        void SAOptimization(Map map);
        float calcDistance(MapLocation loc1, MapLocation loc2);
        int routeList[NUM_LOCATIONS];
        int numLocToVisit;
        std::string employeeName;
        std::string output;
        void printOutput(Map map);
        MapLocation locationToGoTo[NUM_LOCATIONS];
};
#endif /* schedule_h */
