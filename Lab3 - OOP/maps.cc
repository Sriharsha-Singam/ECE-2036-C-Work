//
//  maps.cc
//  
//
//  Created by Sriharsha Singam on 9/30/18.
//

#include <stdio.h>
#include "maps.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//Gets Map Values from a file and puts it in MapLocation variable: locations
void Map::initializeMap(string file){
    ifstream inputObjectForFile(file.c_str(), ios::in);
    string out;
    int counter = 0;
    int counter1 = 0;
    
    //While loop do go through each map value:
    while (inputObjectForFile >> out)
    {
        //Check is the out value is a Map Id, Name, X Coordinate, or Y Coordinate
        if(counter == 0){
            stringstream geek(out);
            int x = 0;
            geek >> x;
            locations[counter1].setId(x);
        }
        if(counter == 1)
            locations[counter1].setName(out);
        if(counter == 2){
            stringstream geek(out);
            float x = 0;
            geek >> x;
            locations[counter1].setX(x);
        }
        if(counter == 3){
            stringstream geek(out);
            float x = 0;
            geek >> x;
            locations[counter1].setY(x);
            counter = -1;
            counter1++;
        }
        counter++;
    }
    inputObjectForFile.close();
}

//Setters and Getters for Private Variables:

//Variable: idNumber -- number assigned to each place in Pawnee
void MapLocation::setId(int idNum){idNumber = idNum;}
int MapLocation::getId(){return idNumber;}

//Variable: name -- name of each place in Pawnee
void MapLocation::setName(std::string nameV){name = nameV;}
std::string MapLocation::getName(){return name;}

//Variable: xCoordinate -- X Coordinate of each place in Pawnee
void MapLocation::setX(float x){xCoordinate = x;}
float MapLocation::getX(){return xCoordinate;}

//Variable: yCoordinate -- Y Coordinate of each place in Pawnee
void MapLocation::setY(float y){yCoordinate = y;}
float MapLocation::getY(){return yCoordinate;}

//Default Constructor for Class: MapLocation
MapLocation::MapLocation(){
    idNumber = 0;
    name = "";
    xCoordinate = 0.0;
    yCoordinate = 0.0;
    distance = 0.0;
}

//Constructor (to set variable values) for Class: MapLocation
MapLocation::MapLocation(int idNumberV, std::string nameV, float xCoordinateV, float yCoordinateV) : idNumber(idNumberV), name(nameV),xCoordinate(xCoordinateV), yCoordinate(yCoordinateV){}

//Default Constructor for Class: Map
Map::Map(){}

