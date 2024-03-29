#include "snake.h"
#include "game.h"
#include <iostream>
#include <algorithm>
#include "calibration.h"

extern std::mutex mutlock;

std::vector<std::vector<bool>> Snake::grid(height, std::vector<bool>(width, false));

void Snake::Update(const Snake& other)
{
    SDL_Point prev_cell{
        static_cast<int>(head_x),
        static_cast<int>(head_y)
    };
    UpdateHead();
    SDL_Point current_cell{
        static_cast<int>(head_x),
        static_cast<int>(head_y)
    };


    moved = false;
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
    {
        moved = true;
        UpdateBody(&current_cell, prev_cell, other);
    }
}

void Snake::UpdateBody(const SDL_Point* current_head_cell, SDL_Point& prev_head_cell, const Snake& other)
{
    body.push_back(prev_head_cell);

    std::unique_lock<std::mutex> lock_obj(mutlock);
    grid[prev_head_cell.x][prev_head_cell.y] = true;
    lock_obj.unlock();

    if (growing)
    {
        growing = false;
        size++;
    }
    else
    {
        lock_obj.lock();
        grid[body[0].x][body[0].y] = false;
        lock_obj.unlock();

        body.pop_front();
    }

    if (current_head_cell->x != prev_head_cell.x || current_head_cell->y != prev_head_cell.y)
    {
        if (std::any_of(body.begin(), body.end(), [current_head_cell](const SDL_Point& point)
        {
            return point.x == current_head_cell->x && point.y == current_head_cell->y;
        }) || SnakeCell(other.head_x, other.head_y))
        {
            alive = false;
        }
    }
}

void Snake::UpdateHead()
{
    switch (direction)
    {
    case MOVE_UP:
        head_y -= speed;
        break;

    case MOVE_DOWN:
        head_y += speed;
        break;

    case MOVE_LEFT:
        head_x -= speed;
        break;

    case MOVE_RIGHT:
        head_x += speed;
        break;
    case UNKNOWN_MOVE:
        break;
    }

    if (head_x < 0.0f || head_y < 0.0f || head_x >= 32.0f || head_y >= 32.0f)
    {
        alive = false;

        if (head_x >= 32.0f)
            head_x = 31.99;
        else if (head_y >= 32.0f)
            head_y = 31.99;
    }
}

void Snake::GrowBody()
{
    growing = true;
}

bool Snake::SnakeCell(const int& x, const int& y)
{
    if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y))
    {
        return true;
    }
    return std::any_of(body.begin(), body.end(), [x, y](auto const& item)
    {
        return x == item.x && y == item.y;
    });
}

bool Snake::GetFood(SDL_Point food)
{
    bool get_food = false;
    int new_x = static_cast<int>(head_x);
    int new_y = static_cast<int>(head_y);

    if (food.x == new_x && food.y == new_y)
    {
        get_food = true;
        score++;
        GrowBody();
    }

    return get_food;
}
