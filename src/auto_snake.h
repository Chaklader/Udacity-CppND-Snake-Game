#ifndef AUTO_SNAKE_H
#define AUTO_SNAKE_H

#include "snake.h"
#include <iostream>
#include <vector>
#include <thread>


class Auto_snake : public Snake
{
public:
    Auto_snake(const int& grid_width, const int& grid_height, int&& num) : Snake(
        grid_width, grid_height, num)
    {
        std::cout << "autonomous snake built" << std::endl;
        speed = 0.12f;
    }

    void Update(const Snake& other) override;
    void record_food(const SDL_Point& position);
    void require_new_path() { update_path = true; }

private:
    bool update_path{false};
    SDL_Point _food{0, 0};
    Direction _last_direction_state{UNKNOWN_MOVE};

    struct Delta
    {
        int x;
        int y;
        Direction action;
    };

    struct Search_Pt
    {
    public:
        Search_Pt() : x(-1), y(-1)
        {
        };

        Search_Pt(int current_x, int current_y) : x(current_x), y(current_y)
        {
        };

        int x;
        int y;
        int cost{0};
        bool visited{false};
        Direction action{UNKNOWN_MOVE};
        SDL_Point parent{-1, -1};
        /* member function */
        bool operator<(Search_Pt const& a) const
        {
            return (cost > a.cost) ? true : false;
        }
    };

    bool path_search(std::vector<std::vector<Direction>>& direction_arr, const SDL_Point& food, const SDL_Point& head,
                     int&& grid_width, int&& grid_height);

    std::vector<Delta> delta_list = {{0, -1, MOVE_UP}, {0, 1, MOVE_DOWN}, {-1, 0, MOVE_LEFT}, {1, 0, MOVE_RIGHT}};
    /*move: up, down, left, right */
};

#endif
