#include "WorldMap.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>

using namespace std;

void WorldMap::loadMap(std::string filename) {
    //values.push_back( { 0, 0, 0,0} ); // -------> x   sample map of size 4 by 4
    //values.push_back( { 0,-1,-1,2} ); // |            inner vector define tiles in the x axis
    //values.push_back( { 0,-1,-1,9} ); // |            outer vector define tiles in the z axis
    //values.push_back( { 0, 0, 0,0} ); // v z          (lect4 slides for json)

    using namespace rapidjson;
    ifstream fis(filename);
    IStreamWrapper isw(fis);
    Document d;
    d.ParseStream(isw);

    for (size_t i = 0; i < d["tileMap"].GetArray().Size(); i++)
    {
        vector<int> newRow;
        for (size_t j = 0; j < d["tileMap"][i].GetArray().Size(); j++)
        {
            newRow.push_back(d["tileMap"][i][j].GetInt());
        }
        values.push_back(newRow);
        newRow.clear();
    }
    
    startingPosition.x = d["spawn"]["x"].GetDouble();
    startingPosition.y = d["spawn"]["y"].GetDouble();
    startingRotation = d["spawn"]["angle"].GetDouble();

    floorColor[0] = d["floorColor"][0].GetDouble();
    floorColor[1] = d["floorColor"][1].GetDouble();
    floorColor[2] = d["floorColor"][2].GetDouble();
    floorColor[3] = d["floorColor"][3].GetDouble();

    ceilColor[0] = d["ceilColor"][0].GetDouble();
    ceilColor[1] = d["ceilColor"][1].GetDouble();
    ceilColor[2] = d["ceilColor"][2].GetDouble();
    ceilColor[3] = d["ceilColor"][3].GetDouble();

    /*std::cout << startingPosition.x << " " << startingPosition.y << " " << startingRotation << "\n";
    std::cout << floorColor[0] << " " << floorColor[1] << " " << floorColor[2] << " " << floorColor[3] << "\n";
    std::cout << ceilColor[0] << " " << ceilColor[1] << " " << ceilColor[2] << " " << ceilColor[3] << "\n";

    for (size_t i = 0; i < values.size(); i++)
    {
        for (size_t j = 0; j < values[i].size(); j++)
        {
            std::cout << values[i][j] << ", ";
        }
        std::cout << "\n";
    }*/
}

int WorldMap::getTile(int x, int y) {
    return values.at(y).at(x);
}

int WorldMap::getWidth() {
    return values[0].size();
}

int WorldMap::getHeight() {
    return values.size();
}

glm::vec2 WorldMap::getStartingPosition() {
    return startingPosition;
}

float WorldMap::getStartingRotation() {
    return startingRotation;
}

glm::vec4 WorldMap::getFloorColor() {
    return floorColor;
}

glm::vec4 WorldMap::getCeilColor() {
    return ceilColor;
}
