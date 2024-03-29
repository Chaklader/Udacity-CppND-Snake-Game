#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "auto_snake.h"
#include <thread>
#include <mutex>


class Game
{
public:
    Game(const std::size_t& grid_width, const std::size_t& grid_height);
    void Run(Controller const& controller, Renderer& renderer, const std::size_t& target_frame_duration);
    [[nodiscard]] int GetScore() const;
    [[nodiscard]] int GetSize() const;

private:
    Snake snake;
    Auto_snake auto_snake;
    SDL_Point food{};

    std::mutex game_mutex;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<unsigned char> random_w;
    std::uniform_int_distribution<unsigned char> random_h;

    void PlaceFood();
    void Update();
};

#endif
