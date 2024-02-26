#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <vector>
#include "SDL.h"

class Snake
{
public:
    Snake(const int& grid_width, const int& grid_height, int num)
        : grid_width(grid_width), grid_height(grid_height),
          head_y(static_cast<float>(grid_height) * 0.75f)
    {
        double factor = (num == 0) ? 0.25 : 0.75;
        head_x = grid_width * factor;
        speed = 0.15f;
    }

    enum Direction { UP, DOWN, LEFT, RIGHT, UNKNOWN };

    Direction direction = UP;
    std::deque<SDL_Point> body;

    float speed{0.0f};
    int size{1};
    bool alive{true};
    float head_x;
    float head_y;
    bool moved{false};

    static std::vector<std::vector<bool>> grid;

    virtual void Update(const Snake& other);

    void GrowBody();
    bool SnakeCell(const int& x, const int& y);
    bool GetFood(SDL_Point food);
    [[nodiscard]] int get_score() const { return score; }

protected:
    int score{0};
    bool growing{false};
    int grid_width;
    int grid_height;

    void UpdateHead();
    void UpdateBody(const SDL_Point* current_head_cell, SDL_Point& prev_head_cell,
                    const Snake& other);
};

#endif
