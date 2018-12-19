//
//  maps.h
//  
//
//  Created by Sriharsha Singam on 9/30/18.
//

#ifndef MAPS_H
#define MAPS_H
#include <string>

#define NUM_LOCATIONS 25

class MapLocation{
    private:
        int idNumber;
        std::string name;
        float xCoordinate;
        float yCoordinate;
        float distance;
    public:
        void setId(int idNum);
        int getId();
        void setName(std::string nameV);
        std::string getName();
        void setX(float x);
        float getX();
        void setY(float y);
        float getY();
        void setDistance(float distance);
        float getDistance();
        MapLocation();
        MapLocation(int idNumber, std::string name, float xCoordinate, float yCoordinate);
};
class Map{
    
    public:
    MapLocation locations[NUM_LOCATIONS];
    Map();
    void initializeMap(std::string name);
};
#endif /* maps_h */
