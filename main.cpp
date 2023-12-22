#include <iostream>
#include <vector>
#include <queue>

#define MAP_SIZE 20

enum block_Type : char
{
    UNDENTIFED = 0,
    SLOW_DOWN = -1, // feature
    WALL = -2,
    START_POINT = -3,
    END_POINT = -4
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

std::vector<cords> path_Finder(std::vector<std::vector<char>> map);

int main(int argc, char **argv)
{
    std::vector<cords> path;
    std::vector<std::vector<char>> map;
    
    std::srand(time(NULL));
    
    // creating map   
    std::cout << "Creating map..." << std::endl;
    for (int i = 0; i < MAP_SIZE; i++)
    {
        map.push_back(std::vector<char>());
        for(int j = 0; j < MAP_SIZE; j++)
        {
            map[i].push_back(block_Type::UNDENTIFED);
        }
    }

    std::cout << "Adding end and start points" << std::endl;
    map[std::rand() % MAP_SIZE][std::rand() % MAP_SIZE] = block_Type::START_POINT;
    map[std::rand() % MAP_SIZE][std::rand() % MAP_SIZE] = block_Type::END_POINT;
    
    std::cout << "Map: " << std::endl;

    for (int i = 0; i < MAP_SIZE; i++)
    {
        map.push_back(std::vector<char>());
        for(int j = 0; j < MAP_SIZE; j++)
        {
            std::cout << (int)map[i][j] << " ";
        }
        std::cout << std::endl;
    }    
    std::cout << "Starting the path searcher!" << std::endl;
    
    path = path_Finder(map);
    std::cout << "Found!" << std::endl;
    std::cout << "path length: " << path.size()  << std::endl;
    for (cords s : path)
    {
        std::cout << "["<< s.x << ", " << s.y << "] ";
    }
    std::cout << std::endl << " Path ! " << std::endl;
    return 0;
}

std::vector<cords> path_Finder(std::vector<std::vector<char>> map)
{
    std::queue<cords> to_test_queue;
    std::queue<cords> next_queue;

    std::vector<cords> path;

    cords temp_cords;

    int next_cord_value = 0;
    int iterations_counter = 0;
    bool found = false;

    // finiding start point
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == block_Type::START_POINT)
            {
                next_queue.push(cords(i, j));
                found = true;
                break;
            }
        }
        if (found == true)
            break;
    }

    // checking if found
    if (found == false)
    {
        throw std::runtime_error("No Starting point found");
    }
    found = false;

    next_cord_value = 0;
    while (found == false && next_queue.size() > 0)
    {
        // moving to next queue
        next_cord_value++;
        to_test_queue = next_queue;
        next_queue = std::queue<cords>();

        while (!to_test_queue.empty() && !found)
        {
            temp_cords = to_test_queue.front();
            to_test_queue.pop();
            iterations_counter++;

            for (int i = -1; i <= 1; i += 2)
            {
                if (map[temp_cords.x][temp_cords.y + i] == block_Type::END_POINT ||
                    map[temp_cords.x + i][temp_cords.y] == block_Type::END_POINT)
                {
                    found = true;
                    path.push_back(temp_cords);
                    break;
                }

                if (i < map[temp_cords.x].size() &&
                    map[temp_cords.x][temp_cords.y + i] == block_Type::UNDENTIFED)
                {
                    map[temp_cords.x][temp_cords.y + i] = next_cord_value;
                }

                if (i < map.size() &&
                    map[temp_cords.x + i][temp_cords.y] == block_Type::UNDENTIFED)
                {
                    map[temp_cords.x + i][temp_cords.y] = next_cord_value;
                }
            }
        }
    }

    temp_cords = path.back();
    while (map[path.back().x][path.back().y + 1] == block_Type::END_POINT ||
           map[path.back().x + 1][path.back().y] == block_Type::END_POINT ||
           map[path.back().x][path.back().y - 1] == block_Type::END_POINT ||
           map[path.back().x - 1][path.back().y] == block_Type::END_POINT )
    {
        // this hollding the next cord we will jump to in our path
        temp_cords = cords(path.back().x + 1, path.back().y);
        next_cord_value = map[temp_cords.x][ temp_cords.y];

        // checking on the x line
        if(map[path.back().x -1][path.back().y] < next_cord_value
            && map[path.back().x -1][path.back().y] > block_Type::UNDENTIFED) 
        {
            temp_cords = cords(path.back().x - 1, path.back().y);
            next_cord_value = map[temp_cords.x][ temp_cords.y];

        }

        // checking on the y line
        if(map[path.back().x][path.back().y + 1] < next_cord_value &&
            map[path.back().x][path.back().y + 1] > block_Type::UNDENTIFED) 
        {
            temp_cords = cords(path.back().x, path.back().y + 1);
            next_cord_value = map[temp_cords.x][ temp_cords.y];

        }
        if(map[path.back().x][path.back().y - 1] < next_cord_value &&
            map[path.back().x][path.back().y - 1] > block_Type::UNDENTIFED) 
        {
            temp_cords = cords(path.back().x, path.back().y - 1);
            next_cord_value = map[temp_cords.x][ temp_cords.y];
        }
        path.push_back(temp_cords);
    }
    return path;
}