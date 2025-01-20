// #pragma once
#include "read_map.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

vector<string> split(string str)
{
    vector<string> result;
    string word;

    stringstream input(str);

    while (getline(input, word, ' '))
        result.push_back(word);

    return result;
}

ReadMap::ReadMap(string map_file)
{
    ifstream input(map_file);
    string line;
    getline(input, line);

    vector<string> fields;
    while (getline(input, line))
    {
        if (!line.empty())
        {
            fields = split(line);
            string image = fields[0];
             Vector2f size = {400.0, 200.0};
            Vector2f position = {stof(fields[1]), stof(fields[2])};
            IntRect int_rect = {stoi(fields[3]), stoi(fields[4]), stoi(fields[5]), stoi(fields[6])};
            Texture *texture = new Texture;
            texture->loadFromFile(image, int_rect);
            platforms.push_back(new Platform(texture, size, position));
        }
    }
}
vector<Platform *> ReadMap::get_platforms()
{
    return platforms;
}