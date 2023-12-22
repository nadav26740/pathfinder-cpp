#include "PathFinder.hpp"

void printMap(std::vector<std::vector<char>> map)
{
    std::cout << "   ";
    for (int i = 0; i < map[0].size(); i++)
    {
        std::cout << std::setw(2) << i << " ";
    }
    std::cout << std::endl << "   ";
    for (int i = 0; i < map[0].size(); i++)
    {
        std::cout << "___";
    }
    std::cout << std::endl;

    for (int i = 0; i < map.size(); i++)
    {
        std::cout << std::setw(2) << i << "|";
        for (int j = 0; j < map[i].size(); j++)
        {
            std::cout << std::setw(2) << (int)map[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<cords> path_Finder(std::vector<std::vector<char>> map)
{
    std::queue<cords> to_test_queue;
    std::queue<cords> next_queue;

    std::vector<cords> path;

    cords temp_cords;

    int next_cord_value = 0;
    bool found = false;

#ifdef DEBUG_PATHFINDER
    int iterations_counter = 0;
#endif
    // finding start point
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

            // running check and increasing path on the surrounding tiles
            for (int i = -1; i <= 1; i += 2)
            {
#ifdef DEBUG_PATHFINDER
                iterations_counter += 2;
#endif // DEBUG
                if (temp_cords.y + i < map[temp_cords.x].size() && temp_cords.y + i >= 0)
                {
                    // checking if end point found
                    if (map[temp_cords.x][temp_cords.y + i] == block_Type::END_POINT)
                    {
                        found = true;
                        path.push_back(temp_cords);
                        break;
                    }

                    // making the next hop on the vertical
                    if (map[temp_cords.x][temp_cords.y + i] == block_Type::UNDENTIFED)
                    {
                        map[temp_cords.x][temp_cords.y + i] = next_cord_value;
                        next_queue.push(cords(temp_cords.x, temp_cords.y + i));
                    }
                }

                if (temp_cords.x + i < map.size() && temp_cords.x + i >= 0)
                {
                    // making the next hop on the horizontal
                    if (map[temp_cords.x + i][temp_cords.y] == block_Type::END_POINT)
                    {
                        found = true;
                        path.push_back(temp_cords);
                        break;
                    }

                    if (map[temp_cords.x + i][temp_cords.y] == block_Type::UNDENTIFED)
                    {
                        map[temp_cords.x + i][temp_cords.y] = next_cord_value;
                        next_queue.push(cords(temp_cords.x + i, temp_cords.y));
                    }
                }

            }
        }
    }

#ifdef DEBUG_PATHFINDER
    std::cout << "[DEBUG]printing map:" << std::endl;
    printMap(map);
#endif

    if (!found)
    {
        throw new std::runtime_error("Error End point hasn't found!");
    }


    temp_cords = path.back();

    // TODO: fix when the end point on corner crush
    while ((path.back().y + 1 >= map[path.back().x].size() || map[path.back().x][path.back().y + 1] != block_Type::START_POINT) &&
        (path.back().x + 1 >= map.size() || map[path.back().x + 1][path.back().y] != block_Type::START_POINT) &&
        (path.back().y - 1 < 0 || map[path.back().x][path.back().y - 1] != block_Type::START_POINT) &&
        (path.back().x - 1 < 0 || map[path.back().x - 1][path.back().y] != block_Type::START_POINT))
    {
        // this holding the next cord we will jump to in our path
        if (path.back().x + 1 < map.size() &&
            map[path.back().x + 1][path.back().y] < next_cord_value
            && map[path.back().x + 1][path.back().y] > block_Type::UNDENTIFED)
        {
            temp_cords = cords(path.back().x + 1, path.back().y);
            next_cord_value = map[temp_cords.x][temp_cords.y];

        }

        // checking on the x line
        if (path.back().x - 1 >= 0 &&
            map[path.back().x - 1][path.back().y] < next_cord_value
            && map[path.back().x - 1][path.back().y] > block_Type::UNDENTIFED)
        {
            temp_cords = cords(path.back().x - 1, path.back().y);
            next_cord_value = map[temp_cords.x][temp_cords.y];

        }

        // checking on the y line
        if (path.back().y + 1 < map[path.back().x].size() &&
            map[path.back().x][path.back().y + 1] < next_cord_value &&
            map[path.back().x][path.back().y + 1] > block_Type::UNDENTIFED)
        {
            temp_cords = cords(path.back().x, path.back().y + 1);
            next_cord_value = map[temp_cords.x][temp_cords.y];

        }
        if (path.back().y -1 >= 0 &&
            map[path.back().x][path.back().y - 1] < next_cord_value &&
            map[path.back().x][path.back().y - 1] > block_Type::UNDENTIFED)
        {
            temp_cords = cords(path.back().x, path.back().y - 1);
            next_cord_value = map[temp_cords.x][temp_cords.y];
        }

        if (path.back().x == temp_cords.x && temp_cords.y == path.back().y)
        {
            throw new std::runtime_error(std::string("Stuck in position: " + std::to_string(temp_cords.x) + ", " + std::to_string(temp_cords.y)));
        }

        // DEBUG
#ifdef DEBUG_PATHFINDER
        std::cout << "[DEBUG]next hop: " << temp_cords.x << ", " << temp_cords.y << " - val: " << next_cord_value << std::endl;
#endif

        path.push_back(temp_cords);
    }

#ifdef DEBUG_PATHFINDER

    std::cout << "[DEBUG]================================[DEBUG]" << std::endl
        << "pathfinder Stats: " << std::endl
        << "Iterations took to find end point: " << iterations_counter << std::endl
        << "Path found length: " << path.size() << std::endl
        << "[DEBUG]================================[DEBUG]" << std::endl;
#endif // DEBUG_PATHFINDER

    return path;
}