#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize.\nSDL_Error: " << SDL_GetError() << '\n';
        throw std::runtime_error("Failed to initialize SDL");
    }

    sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  static_cast<int>(screen_width), static_cast<int>(screen_height), SDL_WINDOW_SHOWN);
    if (!sdl_window)
    {
        SDL_Quit();
        std::cerr << "Window could not be created.\nSDL_Error: " << SDL_GetError() << '\n';
        throw std::runtime_error("Failed to create window");
    }

    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_SOFTWARE);
    if (!sdl_renderer)
    {
        SDL_DestroyWindow(sdl_window);
        SDL_Quit();
        std::cerr << "Renderer could not be created.\nSDL_Error: " << SDL_GetError() << '\n';
        throw std::runtime_error("Failed to create renderer");
    }
}

Renderer::~Renderer()
{
    if (sdl_renderer)
    {
        SDL_DestroyRenderer(sdl_renderer);
    }
    if (sdl_window)
    {
        SDL_DestroyWindow(sdl_window);
    }
    SDL_Quit();
}


void Renderer::Render(Snake const& snake, Snake const& auto_snake, SDL_Point const& food)
{
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
    block.x = food.x * block.w;
    block.y = food.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);

    RenderSnakeBody(snake.body, SDL_Color{0xFF, 0xFF, 0xFF, 0xFF}); // White
    RenderSnakeBody(auto_snake.body, SDL_Color{0x8F, 0xAA, 0xDC, 0xFF}); // Light Blue

    RenderSnakeHead(snake.head_x, snake.head_y, snake.alive, SDL_Color{0x92, 0xD0, 0x50, 0xFF});
    RenderSnakeHead(auto_snake.head_x, auto_snake.head_y, auto_snake.alive, SDL_Color{0x00, 0xB0, 0xF0, 0xFF});

    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score_1, int score_2, int fps)
{
    std::string title = "Player Score: " + std::to_string(score_1) + "     Computer Score: " + std::to_string(score_2) +
        "     FPS: " + std::to_string(fps);
    SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderSnakeBody(const std::deque<SDL_Point>& body, const SDL_Color& color)
{
    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;

    for (const SDL_Point& point : body)
    {
        block.x = point.x * block.w;
        block.y = point.y * block.h;
        SDL_RenderFillRect(sdl_renderer, &block);
    }
}

void Renderer::RenderSnakeHead(float head_x, float head_y, bool alive, const SDL_Color& aliveColor)
{
    SDL_Rect block;
    block.w = screen_width / grid_width;
    block.h = screen_height / grid_height;
    block.x = static_cast<int>(head_x) * block.w;
    block.y = static_cast<int>(head_y) * block.h;

    if (alive)
    {
        SDL_SetRenderDrawColor(sdl_renderer, aliveColor.r, aliveColor.g, aliveColor.b, aliveColor.a);
    }
    else
    {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF); // Red for "dead"
    }
    SDL_RenderFillRect(sdl_renderer, &block);
}
