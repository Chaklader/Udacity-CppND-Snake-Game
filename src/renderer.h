#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class Renderer
{
public:
    Renderer(std::size_t screen_width, std::size_t screen_height, std::size_t grid_width, std::size_t grid_height);
    ~Renderer();

    void Render(Snake const& snake, Snake const& auto_snake, SDL_Point const& food);
    void UpdateWindowTitle(int score_1, int score_2, int fps);
    void RenderSnakeBody(const std::deque<SDL_Point>& body, const SDL_Color& color);
    void RenderSnakeHead(float head_x, float head_y, bool alive, const SDL_Color& aliveColor);


private:
    SDL_Window* sdl_window;
    SDL_Renderer* sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif
