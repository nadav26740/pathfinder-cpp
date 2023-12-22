#include <iostream>
#include <iomanip>
#include <vector>
#include <queue>
#include <string>

#define DEBUG_PATHFINDER_OFF

enum block_Type : char
{
    UNDENTIFED = 0,
    SLOW_DOWN = -1, // feature
    WALL = -2,
    START_POINT = -3,
    END_POINT = -4,
    PATH_MARKS = -5
};

struct cords
{
    int x, y;

    cords()
    {
        this->x = 0;
        this->y = 0;
    }
    cords(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

/// <summary>
/// path finder is a function based on algorithm that made by nadav .M.
/// the algorithm reading a map and finding the best path
/// 
/// === Function complexity: O(4n + 4d) === 
/// </summary>
/// <param name="map">The function getting vector of vector of char that representing the map |
/// The start point is marked as block_Type::START_POINT |
/// The end point is marked as block_Type::END_POINT |
/// The distributors marked as block_Type::WALL |
/// Currently the map can't be bigger than 90 cause of char limits</param>
/// <returns>Vector that represent path to from the end point to start point</returns>
std::vector<cords> path_Finder(std::vector<std::vector<char>> map);

/// <summary> Just printing map </summary>
/// <param name="map"></param>
void printMap(std::vector<std::vector<char>> map);