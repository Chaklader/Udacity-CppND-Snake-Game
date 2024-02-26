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
            return;
        }
        if (e.type != SDL_KEYDOWN)
        {
            continue;
        }

        Sint32 sdl_keycode = e.key.keysym.sym;

        switch (sdl_keycode)
        {
        case SDLK_UP:
            ChangeDirection(snake, Snake::Direction::MOVE_UP,
                            Snake::Direction::MOVE_DOWN);
            break;

        case SDLK_DOWN:
            ChangeDirection(snake, Snake::Direction::MOVE_DOWN,
                            Snake::Direction::MOVE_UP);
            break;

        case SDLK_LEFT:
            ChangeDirection(snake, Snake::Direction::MOVE_LEFT,
                            Snake::Direction::MOVE_RIGHT);
            break;

        case SDLK_RIGHT:
            ChangeDirection(snake, Snake::Direction::MOVE_RIGHT,
                            Snake::Direction::MOVE_LEFT);
            break;

        default:
            std::cout << "This case is not intended" << "\n";
            break;
        }
    }
}
