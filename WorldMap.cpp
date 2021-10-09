#include "WorldMap.hpp"
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <fstream>
#include <iostream>

using namespace std;

void WorldMap::loadMap(std::string filename) {
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
