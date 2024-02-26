#include "controller.h"

#include <iostream>

#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Snake& snake, Snake::Direction input, Snake::Direction opposite)
{
    if (snake.direction != opposite || snake.size == 1)
        snake.direction = input;
}

void Controller::HandleInput(bool& running, Snake& snake)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            running = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            Sint32 sdl_keycode = e.key.keysym.sym;

            switch (sdl_keycode)
            {
            case SDLK_UP:
                ChangeDirection(snake, Snake::Direction::UP,
                                Snake::Direction::DOWN);
                break;

            case SDLK_DOWN:
                ChangeDirection(snake, Snake::Direction::DOWN,
                                Snake::Direction::UP);
                break;

            case SDLK_LEFT:
                ChangeDirection(snake, Snake::Direction::LEFT,
                                Snake::Direction::RIGHT);
                break;

            case SDLK_RIGHT:
                ChangeDirection(snake, Snake::Direction::RIGHT,
                                Snake::Direction::LEFT);
                break;

            default:
                std::cout << "This case is not intended" << "\n";
                break;
            }
        }
    }
}
