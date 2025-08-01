#include "Renderer/Renderer (2).h"

using namespace std;

namespace viper {
    bool Renderer::Initialize() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        if (!TTF_Init()) {
            std::cerr << "TTF_Init Error: " << SDL_GetError() << std::endl;
            return false;
        }

        return true;
    }

    void Renderer::ShutDown()
    {
        TTF_Quit();
        SDL_DestroyRenderer(this->renderer);
        SDL_DestroyWindow(this->window);
        SDL_Quit();
    }

    bool Renderer::CreateWindow(const string& name, int width, int height)
    {
        this->width = width;
        this->height = height;

        //Create Window
        window = SDL_CreateWindow(name.c_str(), width, height, 0);
        if (window == nullptr) {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            SDL_Quit();
            return false;
        }

        //Draw In Window
        renderer = SDL_CreateRenderer(window, NULL);
        if (renderer == nullptr) {
            std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(window);
            SDL_Quit();
            return false;
        }
        return false;
    }

    void Renderer::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        // a -> transparency
    }

    void Renderer::SetColor(float r, float g, float b, float a)
    {
        SDL_SetRenderDrawColorFloat(renderer, r, g, b, a);
    }

    void Renderer::Clear()
    {
        SDL_RenderClear(this->renderer);
    }

    void Renderer::Present()
    {
        SDL_RenderPresent(this->renderer);
    }

    void Renderer::DrawLine(float x1, float y1, float x2, float y2)
    {
        SDL_RenderLine(this->renderer, x1, y1, x2, y2);
        //SDL_RenderLine(this->renderer, random::getRandomInt(width), random::getRandomInt(height), random::getRandomInt(width), random::getRandomInt(height));
    }

    void Renderer::DrawPoint(float x, float y)
    {
        SDL_RenderPoint(this->renderer, x, y);
        //SDL_RenderPoint(this->renderer, random::getRandomInt(width), random::getRandomInt(height));
    }

}