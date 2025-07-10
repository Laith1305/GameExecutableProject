#include <SDL3/SDL.h>
#include <iostream>
#include <vector>
#include "math.h"
#include <eTime.h>
#include "Math/Vector2.h"
#include "../Engine/Core/Random.h"
#include "../Engine/Renderer/Renderer (2).h"

int main(int argc, char* argv[]) {

    viper::Time time;
    Renderer renderer;
    renderer.Initialize();
    renderer.CreateWindow("Screen", 1280, 1024);

    //SDL_Init(SDL_INIT_VIDEO);

    

    SDL_Event e;
    bool quit = false;
    
    std::vector<viper::vec2> stars;
    for (int i = 0; i < 100; i++) {
        stars.push_back(viper::vec2{ viper::random::getRandomFloat() * 1280, viper::random::getRandomFloat() * 1024 });
       

    }
    
    // Define a rectangle
    

    while (!quit) {
        time.Tick();
        
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }
        
        
        renderer.SetColor(0, 0, 0);
        renderer.Clear();

        


        /*renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
        renderer.DrawLine(viper::random::getRandomInt(1280), viper::random::getRandomInt(1280), viper::random::getRandomInt(1280), viper::random::getRandomInt(1280));
        renderer.Present();*/


        viper::vec2 speed{ -140.0f, 0.0f };
        float length = speed.Length();

        for (auto& star : stars) {
            star += speed * time.GetDeltaTime();


            if (star[0] > 1280) star[0] = 0;
            if (star[0] < 0) star[0] = 1280;

            renderer.SetColor(viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256));
            renderer.DrawPoint(star.x, star.y);

        }
        

        renderer.Present();




    }

   



    //for (int i = 0; i < 10; i++) {

    //    SDL_SetRenderDrawColor(renderer, viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256), viper::random::getRandomInt(256)); // Set render draw color to black
    //    //SDL_RenderClear(renderer); // Clear the renderer
    //    //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Set render draw color to green
    //    SDL_RenderLine(renderer, viper::random::getRandomInt(1280), viper::random::getRandomInt(1280), viper::random::getRandomInt(1280), viper::random::getRandomInt(1280));

    //    SDL_RenderPoint(renderer, viper::random::getRandomInt(1280), viper::random::getRandomInt(1280));
    //    SDL_RenderPoint(renderer, viper::random::getRandomInt(1280), viper::random::getRandomInt(1280));

    //    SDL_RenderPresent(renderer); // Render the screen
    //}
    //

    /*SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);*/
    renderer.ShutDown();
    //SDL_Quit();

    return 0;
}