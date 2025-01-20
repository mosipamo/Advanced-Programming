#pragma once

#include "GameEntity.h"
#include <vector>
#include <string>

using namespace std;

class ReadMap{
public:
    ReadMap(string map_file);
    vector <Platform*>  get_platforms();
private:
    vector<Platform*> platforms;
};