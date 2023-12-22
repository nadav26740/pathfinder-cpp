#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <string>
#include "PathFinder.hpp"

// the main is for demo only!
#define MAP_SIZE 20
#define MAP_DISTRUBTORS 40

std::vector<std::vector<char>> Generate_RandomMap(unsigned int seed = time(NULL))
{
    std::vector<std::vector<char>> map;
    std::srand(seed);
    int x, y;
    // creating map   
    std::cout << "Generating random map [seed: " << seed << " ]" << std::endl;
    for (int i = 0; i < MAP_SIZE; i++)
    {
        map.push_back(std::vector<char>());
        for (int j = 0; j < MAP_SIZE; j++)
        {
            map[i].push_back(block_Type::UNDENTIFED);
        }
    }

    // adding distrubtions!
    for (int i = 0; i < MAP_DISTRUBTORS; i++)
    {
        map[std::rand() % MAP_SIZE][std::rand() % MAP_SIZE] = block_Type::WALL;
    }

    std::cout << "Adding end and start points" << std::endl;

    x = std::rand() % MAP_SIZE;
    y = std::rand() % MAP_SIZE;
    std::cout << "[Map Generator]start point: [" << x << ", " << "]" << std::endl;
    map[x][y] = block_Type::START_POINT;
    x = std::rand() % MAP_SIZE;
    y = std::rand() % MAP_SIZE;
    std::cout << "[Map Generator]End point: [" << x << ", " << "]" << std::endl;
    map[x][y] = block_Type::END_POINT;

    return map;
}

int main(int argc, char** argv)
{
    std::vector<cords> path;
    std::vector<std::vector<char>> map;

    map = Generate_RandomMap();

    std::cout << "Map: " << std::endl;
    printMap(map);

    std::cout << "Starting the path searcher!" << std::endl;

    path = path_Finder(map);
    std::cout << "Found!" << std::endl
        << "path length: " << path.size() << std::endl;

    for (cords s : path)
    {
        // marking path
        std::cout << "[" << s.x << ", " << s.y << "] ";
        // marking the path on the map!
        map[s.x][s.y] = block_Type::PATH_MARKS;
    }
    std::cout << std::endl << " Path ! " << std::endl;
    printMap(map);

    return 0;
}