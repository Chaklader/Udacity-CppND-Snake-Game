#include "game.h"
#include "SDL.h"
#include <future>

std::mutex mutlock;

Game::Game(const std::size_t& grid_width, const std::size_t& grid_height)
    : auto_snake(static_cast<int>(grid_width), static_cast<int>(grid_height), 0U),
      snake(static_cast<int>(grid_width), static_cast<int>(grid_height), 1U),
      engine(dev()),

      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1))
{
    PlaceFood();
}

void Game::Run(Controller const& controller, Renderer& renderer, const std::size_t& target_frame_duration)
{
    Uint32 title_timestamp = SDL_GetTicks();
    Uint32 frame_start;
    Uint32 frame_end;
    Uint32 frame_duration;
    int frame_count = 0;
    bool running = true;

    while (running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        frame_start = SDL_GetTicks();

        Controller::HandleInput(running, snake);

        Update();

        renderer.Render(snake, auto_snake, food);

        frame_end = SDL_GetTicks();

        frame_count++;
        frame_duration = frame_end - frame_start;

        if (frame_end - title_timestamp >= 1000)
        {
            renderer.UpdateWindowTitle(snake.get_score(), auto_snake.get_score(), frame_count);
            frame_count = 0;
            title_timestamp = frame_end;
        }

        if (frame_duration < target_frame_duration)
        {
            SDL_Delay(target_frame_duration - frame_duration);
        }
    }
}

void Game::Update()
{
    if (auto_snake.alive == false || snake.alive == false)
    {
        return;
    }

    std::future<void> update_snake = std::async(&Snake::Update, &snake, auto_snake);
    update_snake.wait();

    auto_snake.record_food(food);
    auto_snake.Update(snake);

    if (auto_snake.GetFood(food) == true)
    {
        auto_snake.require_new_path();
        PlaceFood();
    }
    else if (snake.GetFood(food) == true)
    {
        PlaceFood();
    }
}

void Game::PlaceFood()
{
    int x, y;
    while (true)
    {
        x = random_w(engine);
        y = random_h(engine);

        if (!auto_snake.SnakeCell(x, y) && !snake.SnakeCell(x, y))
        {
            food.x = x;
            food.y = y;
            return;
        }
    }
}

int Game::GetScore() const
{
    return snake.get_score();
}

int Game::GetSize() const { return snake.size; }
